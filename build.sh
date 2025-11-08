#!/bin/bash
# Einfaches Build-Script für mdedit ohne CMake

set -e

echo "Building mdedit with g++..."

# Check if qt6 pkg-config files are available
if ! pkg-config --exists Qt6Widgets; then
    echo "Error: Qt6Widgets not found via pkg-config."
    echo "Please install Qt6 development packages:"
    echo "  Ubuntu/Debian: sudo apt install qt6-base-dev"
    echo "  Fedora/RedHat: sudo dnf install qt6-qtbase-devel"
    echo "  Arch: sudo pacman -S qt6-base"
    exit 1
fi

# Create build directory
mkdir -p build
cd build

echo "Running MOC (Meta-Object Compiler)..."
# Generate MOC files for Qt6
/usr/lib/qt6/libexec/moc ../src/MainWindow.h -o moc_MainWindow.cpp
/usr/lib/qt6/libexec/moc ../src/SplashScreen.h -o moc_SplashScreen.cpp
/usr/lib/qt6/libexec/moc ../src/MarkdownHighlighter.h -o moc_MarkdownHighlighter.cpp

echo "Compiling with g++..."
# Compile with g++ including MOC files
g++ -std=c++17 -O2 \
    $(pkg-config --cflags Qt6Widgets) \
    ../src/main.cpp ../src/MainWindow.cpp ../src/SplashScreen.cpp ../src/MarkdownHighlighter.cpp \
    moc_MainWindow.cpp moc_SplashScreen.cpp moc_MarkdownHighlighter.cpp \
    $(pkg-config --libs Qt6Widgets) \
    -o mdedit

echo "Build successful! Run with: ./build/mdedit"