#!/bin/sh
set -e  # Abort on any command failure

echo "Vector : An experimental directional fuzzing frawework"
echo "With <3 by Siddharth Mishra"

DEPSDIR=$PWD/thirdparty
ROOTDIR=$PWD
BUILDDIR=$PWD/build
SRCDIR=$PWD/src

# Put a CPP14 supporting compiler here
CXX=g++
CC=gcc

rm -rf $BUILDDIR
mkdir -pv $BUILDDIR

echo "building tracer..."
if ! $CC -shared -fPIC $SRCDIR/tracer.c $SRCDIR/shared_trace.c -o$BUILDDIR/libtracer.so \
    -I$DEPSDIR/dynamorio/include \
    -I$DEPSDIR/dynamorio/ext/include \
    -L$DEPSDIR/dynamorio/lib64 \
    -L$DEPSDIR/dynamorio/ext/lib64 \
    -L$DEPSDIR/dynamorio/ext/lib64/release \
    -ldl -lm -ldrcontainers \
    -DLINUX -DX86_64; then
    echo "ERROR: Failed to build tracer" >&2
    exit 1
fi
echo "building tracer... DONE"

echo "building fuzzer..."
if ! $CXX -std=c++14 \
  $SRCDIR/main.cc \
  $SRCDIR/fuzzer.cc \
  $SRCDIR/settings.cc \
  $SRCDIR/knowledge.cc \
  $SRCDIR/crash.cc \
  $SRCDIR/loss.cc \
  $SRCDIR/graph.cc \
  $SRCDIR/tui.cc \
  $SRCDIR/shared_trace.c \
  -o$BUILDDIR/main \
  -I$SRCDIR \
  -I$DEPSDIR/CLI11 \
  -I$DEPSDIR/finalcut/install/include \
  -L$DEPSDIR/finalcut/install/lib \
  -Wl,-rpath,$DEPSDIR/finalcut/install/lib \
  -lfinal \
  -lpthread \
  -Wall -Werror; then
    echo "ERROR: Failed to build fuzzer" >&2
    exit 1
fi
echo "building fuzzer... DONE"

echo "building test programs..."
if ! mkdir -pv $BUILDDIR/testprograms; then
    echo "ERROR: Failed to create testprograms directory" >&2
    exit 1
fi
if ! $CC -O0 -g -o$BUILDDIR/testprograms/vulnerable \
    $ROOTDIR/testprograms/vulnerable.c \
    -Wall -Wextra; then
    echo "ERROR: Failed to build test programs" >&2
    exit 1
fi
echo "building test programs... DONE"
