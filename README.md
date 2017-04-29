gltfpp
======
gltfpp is a glTF 2.0 loader written in C++14 targeting desktop platforms and WebAssembly with a focus on ease of use, type safety and extensibility.

**WORK IN PROGRESS!** This library is not finished yet.

Requirements
------------
- gcc >= 6 or clang >= 3.5
- CMake >= 3.8

When using clang, modules are used to decrease build time.

Finished tasks
------
- Parsing infrastructure (trivial properties can be parsed simply by declaring their fields)
- Finished properties: `Asset`

TODO
----
- generalized (and type safe) enum parsing
- deserialization of buffer data (embedded base64, GLB)
- Networking (HTTP on desktop, XHR on WebAssembly), asynchronous loading
- CMake support for Emscripten
- Proper documentation
- out of tree extensions?
- a small viewer based on the loader
