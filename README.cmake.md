# Building matiec with CMake

CMake builds both `iec2c` and `iec2iec` without Autotools or shell scripts.
The existing Autotools build remains available; see `README.build`.
Generated parser sources and configuration headers stay in the build directory.

## Requirements

- CMake 3.24 or newer.
- A C++17 compiler and its standard filesystem library.
- Bison 2.4 or newer and Flex. The port was tested with Bison 3.8.2 and Flex 2.6.4.
- Ninja for the `native` and `mingw` presets.
- A C compiler for generated PLC C syntax checks. GCC and Clang are supported by
  the test runner; building matiec with MSVC does not port the generated C runtime
  to MSVC.

## Linux

For Debian/Ubuntu, install the build tools:

```sh
sudo apt-get install build-essential cmake ninja-build bison flex
cmake --preset native
cmake --build --preset native --parallel
ctest --preset native
cmake --install build-native
```

The compiler can be selected on the initial configuration, for example:

```sh
cmake --preset native -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
```

Without Ninja, use a separate build directory:

```sh
cmake -S . -B build-make -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build-make --parallel
ctest --test-dir build-make --output-on-failure
```

## Windows: MinGW-w64

Install MinGW-w64, CMake, Ninja, and
[WinFlexBison](https://github.com/lexxmark/winflexbison).
Put the MinGW-w64 `bin` directory and the generator tools on `PATH`.
These commands run in PowerShell; WSL and a Unix shell are not required.

```powershell
cmake --preset mingw
cmake --build --preset mingw --parallel
ctest --preset mingw
cmake --install build-mingw
```

If the generators are not on `PATH`, pass their paths explicitly:

```powershell
cmake --preset mingw `
  -DBISON_EXECUTABLE=C:/Tools/winflexbison/win_bison.exe `
  -DFLEX_EXECUTABLE=C:/Tools/winflexbison/win_flex.exe
```

The executables are in `build-mingw/bin`. A deployed MinGW build also needs the
runtime DLLs required by the selected toolchain, unless static linking is selected
with that toolchain's linker flags.

## Windows: MSVC

Install Visual Studio 2022 with the Desktop development with C++ workload,
CMake, and WinFlexBison. The Visual Studio generator locates the compiler;
running a developer shell is not required for these commands.

```powershell
cmake --preset msvc `
  -DBISON_EXECUTABLE=C:/Tools/winflexbison/win_bison.exe `
  -DFLEX_EXECUTABLE=C:/Tools/winflexbison/win_flex.exe
cmake --build --preset msvc --parallel
ctest --preset msvc
cmake --install build-msvc --config Release
```

The executables are in `build-msvc/bin/Release`. By default this build uses the
Visual C++ runtime selected by CMake. CTest checks matiec's behavior but skips
generated C syntax checks unless a GCC/Clang-compatible compiler is provided:

```powershell
cmake --preset msvc -DMATIEC_TEST_C_COMPILER=C:/mingw64/bin/gcc.exe
ctest --preset msvc
```

Command-line options precede the input file. Clustered flags, attached option
values, and `--` to terminate options are supported by the MSVC argument parser.

## macOS and other systems

For macOS, install the command-line developer tools and the CMake, Ninja, Bison,
and Flex packages. Select the installed generators explicitly when necessary:

```sh
cmake --preset native \
  -DBISON_EXECUTABLE="$(brew --prefix bison)/bin/bison" \
  -DFLEX_EXECUTABLE="$(brew --prefix flex)/bin/flex"
cmake --build --preset native --parallel
ctest --preset native
```

The macOS path handling is implemented but has not been tested on macOS.
Other systems can use a suitable CMake generator/compiler or a toolchain file.
Flex and Bison always run on the build host, including in cross builds.
Cross-built binaries must be tested on their target; configure with
`-DBUILD_TESTING=OFF` if they cannot execute on the build host.

## Installation and library lookup

The presets install into `build-<preset>/install`. A different prefix can be
selected with `-DCMAKE_INSTALL_PREFIX=...` or `cmake --install ... --prefix ...`.
The default layout is:

```text
<prefix>/bin/iec2c[.exe]
<prefix>/bin/iec2iec[.exe]
<prefix>/share/matiec/lib/*.txt
<prefix>/share/matiec/lib/C/*
```

Library lookup uses the explicit `-I` argument first. Otherwise, the CMake build
looks relative to the running executable, then at the configured absolute install
path, then in the source tree. Relative executable lookup is implemented for
Windows, Linux, macOS, and FreeBSD with procfs available. On other systems, use
the configured install path or `-I`.

An installed directory can be moved as a whole while preserving the layout.
The output directory supplied with `-T` must already exist. For example:

```powershell
New-Item -ItemType Directory -Force output | Out-Null
./build-msvc/install/bin/iec2c.exe -T output tests/initialization/ok_array_scalar.st
```

To compile the resulting PLC C code, use the installed `lib/C` directory as an
include directory and provide the target runtime separately. Building matiec
itself does not build or link a PLC executable.

## Tests and build settings

CTest covers the existing positive/negative array and structure initialization
examples, C syntax checks where enabled, IEC regeneration, argument handling,
large LREAL literals, and installation relocation through paths with spaces.
The relocation test adds a function to its private installed library to verify
that lookup uses that library rather than the source tree.

- `BUILD_TESTING=OFF`: omit tests.
- `MATIEC_TEST_C_COMPILER=<path>`: GCC/Clang-compatible compiler for generated C.
- `MATIEC_REVISION=<text>`: override the revision reported by `-v`, including for
  source archives without Git metadata.
- `CMAKE_INSTALL_BINDIR` and `CMAKE_INSTALL_DATADIR`: customize installation
  directories. The relocation test requires relative directories.

Verified locally: Windows x64 with MinGW-w64/GCC 15.2 and MSVC 19.44, and Ubuntu
24.04 with GCC 13.3 under WSL. MSVC-generated PLC C was syntax-checked with
MinGW GCC, not with MSVC. Existing warnings in the compiler sources remain.
