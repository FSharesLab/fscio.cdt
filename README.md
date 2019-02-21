# FSCIO.CDT (Contract Development Toolkit)
## Version : 1.5.0

FSCIO.CDT is a toolchain for WebAssembly (WASM) and set of tools to facilitate contract writing for the FSCIO platform.  In addition to being a general purpose WebAssembly toolchain, [FSCIO](https://github.com/fscio/fsc) specific optimizations are available to support building FSCIO smart contracts.  This new toolchain is built around [Clang 7](https://github.com/fscio/llvm), which means that FSCIO.CDT has the most currently available optimizations and analyses from LLVM, but as the WASM target is still considered experimental, some optimizations are not available or incomplete.

## Important!
FSCIO.CDT Version 1.3.x introduced quite a few breaking changes.  To have binary releases we needed to remove the concept of a core symbol from FSCIO.CDT. This meant drastic changes to symbol, asset and other types/functions that were connected to them. Since these changes would be disruptive, we decided to add as many disruptive changes needed for future contract writing, so that disruption should only occur once. Please read the **_Differences between Version 1.2.x and Version 1.3.x_** section of this readme.

### Binary Releases
FSCIO.CDT currently supports Mac OS X brew, Linux x86_64 Debian packages, and Linux x86_64 RPM packages.

**If you have previously installed FSCIO.CDT, please run the `uninstall` script (it is in the directory where you cloned FSCIO.CDT) before downloading and using the binary releases.**

#### Mac OS X Brew Install
```sh
$ brew tap fscio/fscio.cdt
$ brew install fscio.cdt
```
#### Mac OS X Brew Uninstall
```sh
$ brew remove fscio.cdt
```
#### Debian Package Install
```sh
$ wget https://github.com/FutureSharesCloud/fscio.cdt/releases/download/v1.5.0/fscio.cdt-1.5.0-1_amd64.deb
$ sudo apt install ./fscio.cdt-1.5.0-1_amd64.deb
```
#### Debian Package Uninstall
```sh
$ sudo apt remove fscio.cdt
```

#### Fedora RPM Package Install
```sh
$ wget https://github.com/FutureSharesCloud/fscio.cdt/releases/download/v1.5.0/fscio.cdt-1.5.0-1.fc27.x86_64.rpm
$ sudo yum install ./fscio.cdt-1.5.0-1.fc27.x86_64.rpm
```

#### Fedora RPM Package Uninstall
```sh
$ sudo yum remove fscio.cdt
```

#### Centos RPM Package Install
```sh
$ wget https://github.com/FutureSharesCloud/fscio.cdt/releases/download/v1.5.0/fscio.cdt-1.5.0-1.el7.x86_64.rpm
$ sudo yum install ./fscio.cdt-1.5.0-1.el7.x86_64.rpm
```

#### Centos RPM Package Uninstall
```sh
$ sudo yum remove fscio.cdt
```

### Guided Installation (Building from Scratch)
```sh
$ git clone --recursive https://github.com/FutureSharesCloud/fscio.cdt
$ cd fscio.cdt
$ ./build.sh
$ sudo ./install.sh
```

### Installed Tools
---
* fscio-cpp
* fscio-cc
* fscio-ld
* fscio-init
* fscio-abigen
* fscio-abidiff
* fscio-pp (post processing pass for WASM, automatically runs with fscio-cpp and fscio-ld)
* fscio-wasm2wast
* fscio-wast2wasm
* fscio-ranlib
* fscio-ar
* fscio-objdump
* fscio-readelf
