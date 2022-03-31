import asyncio
import os
import pathlib
import signal
import subprocess

import oeqa.core.target.ssh

class OEFVPTarget(oeqa.core.target.ssh.OESSHTarget):

    # meta-arm/scripts isn't on PATH, so work out where it is
    metaarm = pathlib.Path(__file__).parents[4]

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
        cmd = [OEFVPTarget.metaarm / "scripts" / "runfvp", "--console", "--verbose", self.fvpconf]
        # Python 3.7 needs the command items to be str
        cmd = [str(c) for c in cmd]
        self.logger.debug(f"Starting {cmd}")

        # TODO: refactor runfvp so this can import it and directly hook to the
        # console callback, then use telnetlib directly to access the console.

        # As we're using --console, telnet expects stdin to be readable too.
        self.fvp = await asyncio.create_subprocess_exec(*cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, stdin=subprocess.PIPE)
        self.logger.debug(f"Started runfvp PID {self.fvp.pid}")

        async def wait_for_login(bootlog):
            while True:
                line = await self.fvp.stdout.read(1024)
                if not line:
                    self.logger.debug("runfvp terminated")
                    return False

                self.logger.debug(f"Read line [{line}]")

                bootlog += line
                if self.logfile:
                    self.logfile.write(line)

                if b" login:" in bootlog:
                    self.logger.debug("Found login prompt")
                    return True

        bootlog = bytearray()
        try:
            found = await asyncio.wait_for(wait_for_login(bootlog), self.boot_timeout)
            if found:
                return
        except asyncio.TimeoutError:
            self.logger.info("Timed out waiting for login prompt.")
        self.logger.info("Boot log follows:")
        self.logger.info(b"\n".join(bootlog.splitlines()[-200:]).decode("utf-8", errors="replace"))
        raise RuntimeError("Failed to start FVP.")

    def start(self, **kwargs):
        # When we can assume Py3.7+, this can simply be asyncio.run()
        loop = asyncio.get_event_loop()
        loop.run_until_complete(asyncio.gather(self.boot_fvp()))

    def stop(self, **kwargs):
        loop = asyncio.get_event_loop()

        try:
            # Kill the process group so that the telnet and FVP die too
            gid = os.getpgid(self.fvp.pid)
            self.logger.debug(f"Sending SIGTERM to {gid}")
            os.killpg(gid, signal.SIGTERM)
            loop.run_until_complete(asyncio.wait_for(self.fvp.wait(), 10))
        except TimeoutError:
            self.logger.debug(f"Timed out, sending SIGKILL to {gid}")
            os.killpg(gid, signal.SIGKILL)
        except ProcessLookupError:
            return
