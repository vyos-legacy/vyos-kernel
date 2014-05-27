#!/bin/sh -e

# $1: kernel flavour to build
FLAV=$1
BARCH=$(dpkg-architecture -qDEB_BUILD_ARCH)
DEB_ARCH_DIR=$(pwd)/debian/arch/$BARCH

if [ ! -f "$DEB_ARCH_DIR/defines.$FLAV" ]; then
  echo "Invalid kernel flavour \"$FLAV\""
  exit 1
fi

cp -f "$DEB_ARCH_DIR/defines.$FLAV" "$DEB_ARCH_DIR/defines"

rm -f debian/{control,control.md5sum}
make -f debian/rules debian/control || true

