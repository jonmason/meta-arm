import os
import pathlib
import subprocess

from oeqa.selftest.case import OESelftestTestCase

runfvp = pathlib.Path(__file__).parents[5] / "scripts" / "runfvp"
testdir = pathlib.Path(__file__).parent / "tests"

class RunFVPTests(OESelftestTestCase):
    def setUpLocal(self):
        self.assertTrue(runfvp.exists())

    def run_fvp(self, *args, should_succeed=True):
        """
        Call runfvp passing any arguments. If check is True verify return stdout
        on exit code 0 or fail the test, otherwise return the CompletedProcess
        instance.
        """
        # Put the test directory in PATH so that any mock FVPs are found first
        newenv = {"PATH": str(testdir) + ":" + os.environ["PATH"]}
        cli = [runfvp,] + list(args)
        print(f"Calling {cli}")
        ret = subprocess.run(cli, env=newenv, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
        if should_succeed:
            self.assertEqual(ret.returncode, 0, f"runfvp exit {ret.returncode}, output: {ret.stdout}")
            return ret.stdout
        else:
            self.assertNotEqual(ret.returncode, 0, f"runfvp exit {ret.returncode}, output: {ret.stdout}")
            return ret.stdout

    def test_help(self):
        output = self.run_fvp("--help")
        self.assertIn("Run images in a FVP", output)

    def test_bad_options(self):
        self.run_fvp("--this-is-an-invalid-option", should_succeed=False)

    def test_run_auto_tests(self):
        newenv = {"PATH": str(testdir) + ":" + os.environ["PATH"]}

        cases = list(testdir.glob("auto-*.json"))
        if not cases:
            self.fail("No tests found")
        for case in cases:
            with self.subTest(case=case.stem):
                self.run_fvp(case)

    def test_fvp_options(self):
        # test-parameter sets one argument, add another manually
        self.run_fvp(testdir / "test-parameter.json", "--", "--parameter", "board.dog=woof")
