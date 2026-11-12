# Trusted Firmware-M tests on MPS2 AN521

`ci/mps2-an521.yml` builds the normal TF-M firmware. Add `ci/tfm-tests.yml` to
also build the secure and non-secure regression suites from TF-M's `tf-m-tests`
repository. The separate test recipe runs `do_testimage` in QEMU. The task
requires both suites to finish, at least one passing test, and no reported
failures. It saves the serial output in
`tmp/work/*/trusted-firmware-m-tests/*/testimage/qemu.log`.

To run the same test outside CI:

```sh
kas build ci/mps2-an521.yml:ci/tfm-tests.yml
```

For a second run in an existing kas build directory:

```sh
bitbake trusted-firmware-m-tests -c testimage -f
```
