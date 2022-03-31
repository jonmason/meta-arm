# SPDX-License-Identifier: MIT

from oeqa.runtime.case import OERuntimeTestCase

class NoopTest(OERuntimeTestCase):
    """
    This is a test case which does nothing.  Useful when you want to use
    testimage to verify that an image boots, but you don't have networking so
    none of the existing test cases are suitable.
    """
    def test_no_op(self):
        return
