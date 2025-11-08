# Simple Makefile for mdedit (Qt Markdown Editor)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
QT_CFLAGS = $(shell pkg-config --cflags Qt6Widgets)
QT_LIBS = $(shell pkg-config --libs Qt6Widgets)

SRC_DIR = src
BUILD_DIR = build
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/MainWindow.cpp $(SRC_DIR)/SplashScreen.cpp $(SRC_DIR)/MarkdownHighlighter.cpp
TARGET = $(BUILD_DIR)/mdedit

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

MOC_HEADERS = $(SRC_DIR)/MainWindow.h $(SRC_DIR)/SplashScreen.h $(SRC_DIR)/MarkdownHighlighter.h
MOC_SOURCES = $(BUILD_DIR)/moc_MainWindow.cpp $(BUILD_DIR)/moc_SplashScreen.cpp $(BUILD_DIR)/moc_MarkdownHighlighter.cpp

$(BUILD_DIR)/moc_%.cpp: $(SRC_DIR)/%.h | $(BUILD_DIR)
	/usr/lib/qt6/libexec/moc $< -o $@

$(TARGET): $(SOURCES) $(MOC_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(QT_CFLAGS) $(SOURCES) $(MOC_SOURCES) $(QT_LIBS) -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean install check-deps

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/mdedit

# Check if Qt6 is available
check-deps:
	@pkg-config --exists Qt6Widgets || (echo "Qt6Widgets not found. Install with:" && \
	 echo "  Ubuntu/Debian: sudo apt install qt6-base-dev" && \
	 echo "  Fedora/RedHat: sudo dnf install qt6-qtbase-devel" && \
	 echo "  Arch: sudo pacman -S qt6-base" && false)