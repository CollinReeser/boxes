# README

## Dependencies

- GCC 14.2.0+ or another >=C++23 compiler with e.g. `<print>` support required.
- SDL3 required (https://github.com/libsdl-org/SDL).
- SDL3_net required (https://github.com/libsdl-org/SDL_net).
- An implementation that satisfies `<mdspan>` is required.

## MSYS2

### Dependencies

#### Via `pacman`

    pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-make \
              mingw-w64-x86_64-cmake mingw-w64-x86_64-autotools

#### SDL

To build SDL3 on MSYS2, see:

    git clone https://github.com/libsdl-org/SDL.git
    git checkout release-3.2.4
    git branch 3.2.4
    https://wiki.libsdl.org/SDL3/README/windows

#### SDL_net

Assuming MSYS2 installed under `C:/msys64`, and SDL3 has been built within
a `build` dir:

    git clone https://github.com/libsdl-org/SDL_net
    git checkout d076a0d
    cd SDL_net
    mkdir build
    cd build
    cmake .. -DSDL3_DIR=C:/msys64/<path>/<to>/SDL/build
    cmake --build .

#### `<mdspan>`

If not available from your compiler, consider sourcing a reference
implementation, such as:

    https://raw.githubusercontent.com/ORNL/cpp-proposals-pub/refs/heads/master/P0009/reference-implementation/include/experimental/bits/mdspan.hpp

#### DLLs

Find and copy these DLLs into the project root directory:

    libgcc_s_seh-1.dll
    libstdc++-6.dll
    libwinpthread-1.dll
    SDL3.dll
    SDL3_net.dll

The SDL DLL should be located in the `build` dir of your built SDL tree.

The SDL_net DLL should be located in the `build` dir of your built SDL_net tree.

The other DLLs can be found in MSYS2 with a sufficient GCC installed, at:

    cp /mingw64/bin/libgcc_s_seh-1.dll  .
    cp /mingw64/bin/libstdc++-6.dll     .
    cp /mingw64/bin/libwinpthread-1.dll .

### Build

To build (assuming MSYS2 installed under `C:/msys64`), where:

- `SDL_DIR`: Path to the root of the built SDL tree, containing `include`  
and `build`.
- `MDSPAN_DIR`: Path directly to a parent directory containing an `mdspan.hpp`  
implementation suitable for `#include "mdspan.hpp"` such that the spec for  
`<mdspan>` is met.
- `CXX` may need to be specified if otherwise an unable compiler is selected
by default.

Then:

    ./configure \
            SDL_DIR=C:/msys64/<path>/<to>/SDL \
            MDSPAN_DIR=C:/msys64/<path>/<to>/<mdspan_containing_dir> \
            CXX=C:/msys64/<path>/<to>/bin/g++
    make

#### Building `configure`

This should be unnecessary; the existing `configure` should be sufficient.

If not, first:

    pacman -S autotools autoconf-archive

then:

    autoconf

should regenerate an approximately equivalent `configure`.