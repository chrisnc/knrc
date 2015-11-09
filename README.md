# K&R C

Exercises and examples from [_The C Programming Language_](https://en.wikipedia.org/wiki/The_C_Programming_Language)
by Kernighan and Ritchie.

### Building

The examples have been built successfully on Linux, OS X, and Windows.

To build them yourself, first make sure you have the standard compiler for your
platform: `gcc` for Linux, `clang` for OS X, and MSVC for Windows.

Then, install [`scons`](http://www.scons.org) (often available from a package
manager).

Finally, run `scons` from the base directory of this repository. This will
build all the object files and executables and place them in `knrc/build`.
