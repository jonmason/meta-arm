#!/usr/bin/env python3
"""Package RDV3 boot images using the RD-INFRA-2025.07.03 flash layout."""

import argparse
import gzip
import os
from pathlib import Path
import shutil
import subprocess
import sys


def assemble(output, images):
    with output.open("wb") as dest:
        for offset, source in images:
            dest.seek(offset)
            dest.write(source.read_bytes())


def sign(wrapper, mcuboot_scripts, key, source, output, load_addr, slot_size):
    layout = output.with_suffix(".layout")
    layout.write_text(
        "enum image_attributes {\n"
        f"  RE_IMAGE_LOAD_ADDRESS = 0x{load_addr:x},\n"
        f"  RE_SIGN_BIN_SIZE = 0x{slot_size:x},\n"
        "};\n"
    )
    env = os.environ.copy()
    env["PYTHONPATH"] = os.pathsep.join((str(mcuboot_scripts), env.get("PYTHONPATH", "")))
    subprocess.run(
        [sys.executable, str(wrapper), "-v", "0.0.7", "--layout", str(layout),
         "-k", str(key), "--public-key-format", "full", "--align", "1",
         "--pad", "--pad-header", "-H", "0x400", "-s", "1",
         str(source), str(output)],
        cwd=mcuboot_scripts,
        env=env,
        check=True,
    )
    layout.unlink()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--deploy-dir", type=Path, required=True)
    parser.add_argument("--tfm-scripts", type=Path, required=True)
    parser.add_argument("--mcuboot-scripts", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()

    deploy = args.deploy_dir
    tfm = deploy / "trusted-firmware-m"
    scp = deploy / "scp-firmware"
    tfa = deploy / "trusted-firmware-a"
    output = args.output_dir

    wrapper = args.tfm_scripts / "wrapper" / "wrapper.py"
    key = args.tfm_scripts.parent / "root-EC-P256.pem"
    signed = {}
    for name, source, load, slot in (
        ("scp", scp / "scp_ramfw.bin", 0x70001C00, 0x80000),
        ("mcp", scp / "mcp_ramfw.bin", 0x70083C00, 0x80000),
        ("lcp", scp / "lcp_ramfw.bin", 0x70105C00, 0x10000),
        ("bl1", tfa / "bl1.bin", 0x70117C00, 0x80000),
    ):
        signed[name] = output / f"signed_{name}.bin"
        sign(wrapper, args.mcuboot_scripts, key, source, signed[name], load, slot)

    assemble(output / "tf_m_flash.bin", (
        (0x000000, tfm / "bl2_signed.bin"),
        (0x020000, tfm / "bl2_signed.bin"),
        (0x040000, tfm / "tfm_s_signed.bin"),
        (0x100000, tfm / "tfm_s_signed.bin"),
        (0x1C0000, signed["scp"]),
        (0x240000, signed["scp"]),
        (0x2C0000, signed["mcp"]),
        (0x340000, signed["mcp"]),
        (0x3C0000, signed["lcp"]),
        (0x3D0000, signed["lcp"]),
        (0x3E0000, signed["bl1"]),
        (0x460000, signed["bl1"]),
    ))
    shutil.copyfile(tfm / "bl1_1.bin", output / "tf_m_rom.bin")
    shutil.copyfile(tfm / "encrypted_cm_provisioning_bundle_0.bin", output / "tf_m_vm0_0.bin")
    shutil.copyfile(tfm / "encrypted_dm_provisioning_bundle_0.bin", output / "tf_m_vm1_0.bin")
    shutil.copyfile(tfa / "fip.bin", output / "fip-rdv3.bin")
    for chip in (1, 2):
        with (output / f"nor{chip}_flash.img").open("wb") as raw:
            with gzip.GzipFile(fileobj=raw, mode="wb", mtime=0) as compressed:
                chunk = bytes(256 * 1024)
                for _ in range(256):
                    compressed.write(chunk)


if __name__ == "__main__":
    main()
