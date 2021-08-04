FILESEXTRAPATHS:prepend := "${THISDIR}/linux-yocto-5.3:"

SRC_URI:append = " file://0001-perf-cs-etm-Move-definition-of-traceid_list-global-v.patch \
                   file://0002-perf-tests-bp_account-Make-global-variable-static.patch \
                   file://0003-perf-bench-Share-some-global-variables-to-fix-build-.patch \
                   file://0004-libtraceevent-Fix-build-with-binutils-2.35.patch \
                   file://0005-perf-Make-perf-able-to-build-with-latest-libbfd.patch \
                   "
