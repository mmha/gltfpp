#!/bin/sh
for x in $(find test/ gltfpp/ -name '*.cpp' -o -name '*.h'); do clang-format -style=file -i $x; done
