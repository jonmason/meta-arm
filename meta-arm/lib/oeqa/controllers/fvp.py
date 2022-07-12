import asyncio
import pathlib
import pexpect

import oeqa.core.target.ssh
from fvp import conffile, runner

class OEFVPTarget(oeqa.core.target.ssh.OESSHTarget):
    def __init__(self, logger, target_ip, server_ip, timeout=300, user='root',
                 port=None, server_port=0, dir_image=None, rootfs=None, bootlog=None,
                 **kwargs):
        super().__init__(logger, target_ip, server_ip, timeout, user, port)
        image_dir = pathlib.Path(dir_image)
        # rootfs may have multiple extensions so we need to strip *all* suffixes
        basename = pathlib.Path(rootfs)
        basename = basename.name.replace("".join(basename.suffixes), "")
        self.fvpconf = image_dir / (basename + ".fvpconf")

        if not self.fvpconf.exists():
            raise FileNotFoundError(f"Cannot find {self.fvpconf}")
        # FVPs boot slowly, so allow ten minutes
        self.boot_timeout = 10 * 60

        self.logfile = bootlog and open(bootlog, "wb") or None

    async def boot_fvp(self):
        config = conffile.load(self.fvpconf)
        self.fvp = runner.FVPRunner(self.logger)
        await self.fvp.start(config)
        self.logger.debug(f"Started FVP PID {self.fvp.pid()}")
        console = await self.fvp.create_pexpect(config["console"])
        try:
            console.expect("login\:", timeout=self.boot_timeout)
            self.logger.debug("Found login prompt")
        except pexpect.TIMEOUT:
            self.logger.info("Timed out waiting for login prompt.")
            self.logger.info("Boot log follows:")
            self.logger.info(b"\n".join(console.before.splitlines()[-200:]).decode("utf-8", errors="replace"))
            raise RuntimeError("Failed to start FVP.")

    async def stop_fvp(self):
        returncode = await self.fvp.stop()

        self.logger.debug(f"Stopped FVP with return code {returncode}")

    def start(self, **kwargs):
        # When we can assume Py3.7+, this can simply be asyncio.run()
        loop = asyncio.get_event_loop()
        loop.run_until_complete(asyncio.gather(self.boot_fvp()))

    def stop(self, **kwargs):
        loop = asyncio.get_event_loop()
        loop.run_until_complete(asyncio.gather(self.stop_fvp()))
