#!/bin/sh

ROOTDIR=$PWD
DEPSDIR=$PWD/thirdparty

rm -rf $DEPSDIR
mkdir -v $DEPSDIR

echo "Vector : An experimental directional fuzzing framework"
echo "With <3 by Siddharth Mishra"

echo "Installing dynamorio for dynamic binary intrumentation support"

# install dynamorio locally
wget https://github.com/DynamoRIO/dynamorio/releases/download/release_11.3.0-1/DynamoRIO-Linux-11.3.0.tar.gz && \
  tar -xvf DynamoRIO-Linux-11.3.0.tar.gz && \
  mv DynamoRIO-Linux-11.3.0-1 $DEPSDIR/dynamorio && \
  rm DynamoRIO-Linux-11.3.0.tar.gz*

echo "Installing zydis for x86_64 disassembly support"

# install Zydis locally
wget https://github.com/zyantific/zydis/archive/refs/tags/v4.1.1.tar.gz && \
  tar -xvf v4.1.1.tar.gz && \
  mv zydis-4.1.1 $DEPSDIR/zydis && \
  rm v4.1.1.tar.gz* && \
  cd $DEPSDIR/zydis && \
  meson setup build && \
  meson configure --prefix=$DEPSDIR/zydis/install build
  meson compile -C build && \
  ninja -C build install && \
  cd $ROOTDIR

echo "Installing finalcut for TUI support"

wget https://github.com/gansm/finalcut/archive/refs/tags/0.9.1.tar.gz && \
  tar -xvf 0.9.1.tar.gz && \
  mv finalcut-0.9.1 $DEPSDIR/finalcut && \
  rm 0.9.1.tar.gz* && \
  cd $DEPSDIR/finalcut && \
  ./autogen.sh && \
  mkdir -pv install && \
  ./configure --prefix=$DEPSDIR/finalcut/install && \
  make && make install && \
  cd $ROOTDIR

echo "Installing CLI11 for command line support"

mkdir $DEPSDIR/CLI11 && \
  wget https://github.com/CLIUtils/CLI11/releases/download/v2.6.1/CLI11.hpp && 
  mv CLI11.hpp $DEPSDIR/CLI11

echo "All deps installed"
