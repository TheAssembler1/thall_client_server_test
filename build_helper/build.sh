#!/bin/bash

cd ..

if [ -d build ]
then
	echo "found build dir"
else
	echo "creating build dir"
	mkdir build
fi

cmake -DFUSE3_LIB=/home/theassembler1/src/copper/external/fuse3/install/lib/x86_64-linux-gnu             \
      -DFUSE3_INCLUDE=/home/theassembler1/src/copper/external/fuse3/install/include/fuse3     \
      -DCMAKE_VERBOSE_MAKEFILE=ON        \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      -Bbuild || { echo "Failed to create compile commands"; exit 1; }
cp build/compile_commands.json . || { echo "Failed to copy compile commands"; exit 1; }


cd build || { echo "Failed to move to build dir"; exit 1; }
make || { echo "Failed to build mongo_fuse_fs"; exit 1; }

