#!/usr/bin/env sh

set -e

# parse arguments
# default: build incrementally
CLEAN=0
while [ $# -gt 0 ]; do
  case "$1" in
    -c|--clean) CLEAN=1 ;;
    -h|--help) echo "Usage: $0 [--clean] [--test] [--debug].
        '--clean' will perform a clean build."; exit 0 ;;
    *) echo "Unknown option: $1"; exit 1 ;;
  esac
  shift
done

# remove build folder if clean build is requested
if [ "$CLEAN" -eq 1 ]; then
  echo "Cleaning previous build..."
  rm -rf build
fi

echo "Running cmake..."
cmake -B build -G Ninja
echo
echo "Making main target..."
cmake --build build

