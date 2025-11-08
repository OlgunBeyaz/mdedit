@echo off
REM Simple Qt Creator project generator

echo Generating mdedit.pro for Qt Creator...

> mdedit.pro (
echo QT += core widgets
echo CONFIG += c++17
echo TARGET = mdedit
echo TEMPLATE = app
echo.
echo # Source files
echo SOURCES += \
echo     src/main.cpp \
echo     src/MainWindow.cpp \
echo     src/SplashScreen.cpp \
echo     src/MarkdownHighlighter.cpp
echo.
echo # Header files
echo HEADERS += \
echo     src/MainWindow.h \
echo     src/SplashScreen.h \
echo     src/MarkdownHighlighter.h
echo.
echo # Include path
echo INCLUDEPATH += src
echo.
echo # Output directory
echo DESTDIR = build
echo OBJECTS_DIR = build/obj
echo MOC_DIR = build/moc
echo.
echo # Windows specific
echo win32 {
echo     RC_ICONS = mdedit.ico
echo     VERSION = 1.1.0.0
echo }
echo.
echo # macOS specific  
echo macx {
echo     ICON = mdedit.icns
echo     QMAKE_INFO_PLIST = Info.plist
echo }
)

echo mdedit.pro created successfully!
echo Open with Qt Creator or run: qmake && nmake
pause