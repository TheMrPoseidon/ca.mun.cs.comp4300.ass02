# ca.mun.cs.comp4300.ass02
My Solution for the Assigment 02 of the following YT Series: https://www.youtube.com/watch?v=V6DwM8GUlLw
Without the special weapon system

## Prerequisite
- C++ Compiler (VC++, Clang, GCC)
- CMake
- Ninja
- Conan ([Website](https://conan.io/))
- Libraries
  - SFML ([Website](https://www.sfml-dev.org/))

### Windows
1. C++/Cmake: Install Visual Studio Community ([Link](https://visualstudio.microsoft.com/de/vs/community/)) and install the 'Desktop Development with C++' Workload. 
2. Conan: Download Conan Package Manager ([Link](https://conan.io/downloads.html)) and installing it
3. Download SFML 2.5.1 (Current State: 26.01.2022) for [Visual C++ 15 (2017) - 32-bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip) or [Visual C++ 15 (2017) - 64-bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip)
4. Extract downloaded zip file into separate folder like ````C:\Dev\Library\SFML-2.5.1``` (avoid whitespaces in the path)
5. Add/update environment variables
  - SFML_DIR: Set to Absolute path (e.g. ```C:\Dev\Library\SFML-2.5.1```) until ```bin\```, ```lib\``` and ```include\``` folders are present
  - Path: Append with %SFML_DIR%\bin
6. Reboot or a restart of running IDEs might be required

### Mac

```bash
# Can be skipped if already installed
xcode-select --install
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install Conan Packagemanager and SFML
brew install sfml conan ninja
```

### Linux
Note: Not completly tested yet.

For ```Fedora``` try to use:
```
dnf install git c++ cmake conan sfml ninja
```

For ```Debian``` and ```Ubuntu``` try to use:
```
apt-get install git c++ cmake conan sfml ninja
```

## Build
```
git clone https://github.com/TheMrPoseidon/ca.mun.cs.comp4300.ass02.git ass02
cd ass02
mkdir build
cd build
cmake -G Ninja ..
cmake --build . --target ass02_app -j 10
```

### Visual Studio Code
Install the [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
