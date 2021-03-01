#!/bin/sh
# This script is to reload kea dhcp4 server when guest interface will be ready

# include locking functions
. /etc/xen/scripts/locking.sh
set +u

# $1 is vif name, e.g. "vif/15/0"
# returns 0 on success,
# 1 otherwize
#

check_if_vif_is_ready() {
    ret=$(xl network-list "${guestname:?}" | grep  "${1}" \
        | tr -s ' ' | cut -d' ' -f5)
    # ${ret} is network interface status value
    # 1 means vif is not ready
    # 4 means vif is ready
    [ "${ret}" = "4" ] && return 0
    return 1
}

case "${XENGUEST_NETWORK_TYPE:-}" in
    nat)
        vif_name="$(xl network-list "${guestname:?}" | grep -o "vif.*")"

        for try in $(seq 20)
        do
            if check_if_vif_is_ready "${vif_name}"; then
                claim_lock "vif-nat-kea"
                keactrl reload
                release_lock "vif-nat-kea"
                exit 0
            fi
            log info "Waiting for ${vif_name} - network interface is not ready..."
            log info "try #${try}"
            sleep 1
        done
        log error "Failed to get ${vif_name}. network interface ready!"
        exit 1
        ;;
    *)
        log verbose "No action needed"
        ;;
esac
