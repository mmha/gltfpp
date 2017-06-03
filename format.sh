#!/bin/sh
for x in $(find test/ gltfpp/ -name '*.cpp' -o -name '*.h'); do clang-format -style=file -i $x; done
for x in $(find test/ gltfpp/ -name '*.gltf'); do
	tmp=$(python -m json.tool $x)
	echo "$tmp" > $x
done
