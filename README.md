# isnp-emu-lib
ISNP facility modeling library based on [Geant4](http://geant4.web.cern.ch/) toolkit.

## Requirements

* C++14 compiler or higher
* CMake 3.1 or higher
* Geant4 10.4 or higher
* Google Test 1.7 or higher

## Content

* `lib` - library itself.
* `basic` - a very basic executable that invokes library.

## Prerequisites

* Geant4 installed and configured

## Building

1. Go to your working directory, for example `~/workspace` (all directory names are arbitrary).

2. Create `isnp-emu-lib` subdirectory within the working directory.

3. Download content of `isnp-emu-lib` repository into `~/workspace/isnp-emu-lib`.

4. Create `isnp-emu-lib-build` subdirectory within the working directory.

5. Enter `~/workspace/isnp-emu-lib-build` directory.

6. Run `cmake`:

```bash
cmake ~/workspace/isnp-emu-lib
```

6.1. If you need to install the library into your profile-specific directory rather than system directory, then set `CMAKE_INSTALL_PREFIX` system property for `cmake` as follows:

```bash
cmake -DCMAKE_INSTALL_PREFIX=~ ~/workspace/isnp-emu-lib
```

7. Build and install library and executables:

```bash
make && make install
```

8. Run example

```bash
cd ~/workspace/isnp-emu-lib
isnp-basic examples/basic.mac
```

