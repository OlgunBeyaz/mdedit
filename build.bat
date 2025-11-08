@echo off
REM Windows Build Script für mdedit

echo Building mdedit with MSVC...

REM Check if Qt6 is available
where moc >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: Qt6 MOC not found in PATH.
    echo Please install Qt6 and add to PATH or use Qt Creator.
    echo Download from: https://www.qt.io/download
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build
cd build

echo Running MOC ^(Meta-Object Compiler^)...
REM Generate MOC files for Qt6
moc ..\src\MainWindow.h -o moc_MainWindow.cpp
moc ..\src\SplashScreen.h -o moc_SplashScreen.cpp
moc ..\src\MarkdownHighlighter.h -o moc_MarkdownHighlighter.cpp

echo Compiling with cl.exe...
REM Compile with Visual Studio compiler
cl /std:c++17 /EHsc /O2 ^
   /I"%QTDIR%\include" /I"%QTDIR%\include\QtWidgets" /I"%QTDIR%\include\QtCore" /I"%QTDIR%\include\QtGui" ^
   ..\src\main.cpp ..\src\MainWindow.cpp ..\src\SplashScreen.cpp ..\src\MarkdownHighlighter.cpp ^
   moc_MainWindow.cpp moc_SplashScreen.cpp moc_MarkdownHighlighter.cpp ^
   /link /LIBPATH:"%QTDIR%\lib" Qt6Widgets.lib Qt6Core.lib Qt6Gui.lib ^
   /OUT:mdedit.exe

if %errorlevel% equ 0 (
    echo Build successful! Run with: .\build\mdedit.exe
) else (
    echo Build failed!
    pause
    exit /b 1
)

cd ..
pause