#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${ROOT}/build/morningstar-arm64"
OUTPUT="${BUILD_DIR}/tycmd"

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

cmake -DCONFIG_VARIANT=morningstar \
      -DCONFIG_TYCMD_BUILD=ON \
      -DCONFIG_TYUPDATER_BUILD=OFF \
      -DCONFIG_TYCOMMANDER_BUILD=OFF \
      -DCMAKE_OSX_ARCHITECTURES=arm64 \
      "${ROOT}"

make tycmd

echo
echo "Built: ${OUTPUT}"
file "${OUTPUT}"
