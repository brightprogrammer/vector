#!/bin/sh

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
$CC -shared -fPIC $SRCDIR/tracer.c $SRCDIR/shared_trace.c -o$BUILDDIR/libtracer.so \
    -I$DEPSDIR/dynamorio/include \
    -I$DEPSDIR/dynamorio/ext/include \
    -L$DEPSDIR/dynamorio/lib64 \
    -L$DEPSDIR/dynamorio/ext/lib64 \
    -L$DEPSDIR/dynamorio/ext/lib64/release \
    -ldl -lm -ldrcontainers \
    -DLINUX -DX86_64
echo "building tracer... DONE"

echo "building fuzzer..."
$CXX -std=c++14 \
  $SRCDIR/main.cc \
  $SRCDIR/fuzzer.cc \
  $SRCDIR/settings.cc \
  $SRCDIR/knowledge.cc \
  $SRCDIR/crash.cc \
  $SRCDIR/loss.cc \
  $SRCDIR/graph.cc \
  $SRCDIR/shared_trace.c \
  -o$BUILDDIR/main \
  -I$SRCDIR \
  -I$DEPSDIR/finalcut/install/include \
  -I$DEPSDIR/CLI11 \
  -L$DEPSDIR/finalcut/install/lib \
  -Wl,-rpath,$DEPSDIR/finalcut/install/lib \
  -lfinal -lpthread \
  -Wall -Werror
echo "building fuzzer... DONE"

echo "building test programs..."
mkdir -pv $BUILDDIR/testprograms
$CC -O0 -g -o$BUILDDIR/testprograms/vulnerable \
    $ROOTDIR/testprograms/vulnerable.c \
    -Wall -Wextra
echo "building test programs... DONE"
