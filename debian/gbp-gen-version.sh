#!/bin/sh

VERSION=$(cd "$GBP_GIT_DIR/.." && ./git-version-gen .tarball-version)

echo "$VERSION" > debian/gbp.version
