#!/bin/sh
tar c 3rdparty .clang-format .clang-tidy cmake CMakeLists.txt format.sh .git .gitignore pack.sh README.md gltfpp test | zstd --ultra -22 > gltfpp.tar.zst
