gltfpp
======
[![Build Status](https://travis-ci.org/mmha/gltfpp.svg?branch=master)](https://travis-ci.org/mmha/gltfpp)

gltfpp is a glTF 2.0 loader written in C++14 targeting desktop platforms and WebAssembly with a focus on ease of use, type safety and extensibility.

**WORK IN PROGRESS!** This library is not finished yet.

Requirements
------------
- gcc >= 6 or clang >= 3.6
- CMake >= 3.2
- Boost >= 1.61

Building
--------
```
mkdir build && cd build
cmake .. [-GNinja]
make # Or ninja
```
### Clang Modules
When using clang, modules can by enabled by passing `-DGLTFPP_ENABLE_MODULES=1` to CMake. This should speed up the compilation, however this is experimental and has only been tested with clang 5.0 snapshots so far.

### Targeting the Web
Install emscripten, then invoke CMake via emconfigure:
```
emconfigure cmake .. [-GNinja] [-DGLTFPP_WEBASSEMBLY=1] # Default is wasm instead of asm.js
```
Compiling to WebAssembly requires binaryen. Note that this library does not export anything, so you can't use it in the browser yet.

Finished tasks
------
- Parsing infrastructure (trivial properties can be parsed simply by declaring their fields)
- Finished properties: `Asset`, `Buffer` (only data uris)
- Build system support for Emscripten

TODO
----
- generalized (and type safe) enum parsing
- deserialization of buffer data (embedded base64, GLB)
- Networking (HTTP on desktop, XHR on WebAssembly), asynchronous loading
- Proper documentation
- out of tree extensions?
- a small viewer based on the loader
- Export functions to the web browser
