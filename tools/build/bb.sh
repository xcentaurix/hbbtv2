#!/bin/bash
# usage: bb.sh <bitbake args...>   (runs in the dm900 build dir of the OpenViX environment)
set -uo pipefail
TOP=/home/alpha/openvix/build-enviroment/builds/openvix/developer/dm900
cd "$TOP"
export BB_NO_NETWORK="${BB_NO_NETWORK:-0}"
# shellcheck disable=SC1091
. ./env.source
bitbake "$@"
echo "bitbake exit: $?"
