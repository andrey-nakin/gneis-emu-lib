# gneis-emu-lib
GNEIS facility emulation library based on geant4 toolkit.

## Requirements

* C++11 compiler or higher
* CMake 3.1 or higher
* Geant4 10.4 or higher

## Prerequisites

* Geant4 installed and configured

## Building

1. Go to your working directory, for example `~/workspace`.

2. Create `gneis-emu-lib` subdirectory within the working directory.

3. Download content of `gneis-emu-lib` repository into `~/workspace/gneis-emu-lib`:

4. Create `gneis-emu-lib-build` subdirectory within the working directory.

5. Enter `~/workspace/gneis-emu-lib-build` directory.

6. Run `cmake`:

```bash
cmake ~/workspace/gneis-emu-lib
```

6.1. If you need to install the library into your profile-specific directory rather than system directory, then set `CMAKE_INSTALL_PREFIX` system property for `cmake` as follows:

```bash
cmake -DCMAKE_INSTALL_PREFIX=~ ~/workspace/gneis-emu-lib
```

7. Build and install library:

```bash
make && make install
```

