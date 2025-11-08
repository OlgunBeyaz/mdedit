# Cross-Platform Build Instructions

## Windows Build

### Method 1: Qt Creator (Recommended)
1. Install Qt6 from https://www.qt.io/download
2. Run `generate_pro.bat` to create mdedit.pro
3. Open mdedit.pro in Qt Creator
4. Build & Run (Ctrl+R)

### Method 2: Command Line (MSVC)
1. Install Qt6 and Visual Studio Build Tools
2. Set QTDIR environment variable to Qt installation
3. Run `build.bat` from Developer Command Prompt

### Method 3: CMake + Visual Studio
```cmd
cmake -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
```

## Linux Build

### Ubuntu/Debian
```bash
sudo apt install qt6-base-dev build-essential
./build.sh
```

### Fedora/RedHat
```bash
sudo dnf install qt6-qtbase-devel gcc-c++
./build.sh
```

### Arch Linux
```bash
sudo pacman -S qt6-base base-devel
./build.sh
```

## macOS Build

### Homebrew
```bash
brew install qt6
./build.sh
```

### MacPorts
```bash
sudo port install qt6
export PATH=/opt/local/libexec/qt6/bin:$PATH
./build.sh
```

## Dependencies

- **Qt 6.2+** (Core, Widgets, Gui)
- **C++17** compatible compiler
- **CMake 3.16+** (for CMake builds)

## Supported Compilers

- **Windows**: MSVC 2019+, MinGW 8.1+
- **Linux**: GCC 7+, Clang 8+
- **macOS**: Clang 10+ (Xcode 10+)

## Build Outputs

- **Linux**: `build/mdedit`
- **Windows**: `build/mdedit.exe` 
- **macOS**: `build/mdedit.app`