# gneis-geant4

[![Project Stats](https://www.openhub.net/p/gneis-geant4/widgets/project_thin_badge?format=gif)](https://www.openhub.net/p/gneis-geant4)

An [GNEIS](http://accelconf.web.cern.ch/AccelConf/rupac2016/talks/wezmh01_talk.pdf) facility modeling library based on [Geant4](http://geant4.web.cern.ch/) toolkit.

## Requirements

* GCC 4.9.2 or higher
* CMake 3.1 or higher
* Geant4 10.4 or higher
* Google Test 1.7 or higher

## Content

* `lib` - library itself.
* `basic` - a very basic executable that invokes library.
* `examples` - macro files with GNEIS-related examples.

## Prerequisites

* Geant4 installed and configured

## Building

1. Go to your working directory, for example `~/workspace` (all directory names are arbitrary).

2. Create `gneis-geant4` subdirectory within the working directory.

3. Download content of `gneis-geant4` repository into `~/workspace/gneis-geant4`.

4. Create `gneis-geant4-build` subdirectory within the working directory.

5. Enter `~/workspace/gneis-geant4-build` directory.

6. Run `cmake`:

```bash
cmake ~/workspace/gneis-geant4
```

6.1. If you need to install the library into your profile-specific directory rather than system directory, then set `CMAKE_INSTALL_PREFIX` system property for `cmake` as follows:

```bash
cmake -DCMAKE_INSTALL_PREFIX=~ ~/workspace/gneis-geant4
```

7. Build and install library and executables:

```bash
make && make install
```

8. Run example

```bash
cd ~/workspace/gneis-geant4
gg-basic examples/basic.mac
```

