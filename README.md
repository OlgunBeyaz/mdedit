# mdedit - Professional Markdown Editor

[![License: Freeware](https://img.shields.io/badge/License-Freeware-green.svg)](https://opensource.org/licenses/MIT)
[![Qt6](https://img.shields.io/badge/Qt-6.2+-blue.svg)](https://www.qt.io/)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)

**Professioneller Markdown-Editor mit Live-Preview, entwickelt von Kemal Akçocuk**

Ein moderner, VSCode-ähnlicher Markdown-Editor mit GitHub-Style Preview, Syntax-Highlighting und vollständiger Toolbar.

![mdedit Screenshot](screenshot.png)

## ✨ Features

### 🎨 **Professionelle Benutzeroberfläche**
- **VSCode-ähnlicher dunkler Editor** mit Syntax-Highlighting
- **GitHub-Style Preview** mit professionellem CSS-Styling
- **Geteiltes Fenster** mit anpassbarer Größe
- **Splash Screen** beim Start mit Autoreninfo

### 🛠️ **Toolbar & Texteditor-Funktionen**
- **Emoji-Toolbar** mit allen wichtigen Funktionen
- **Undo/Redo** (Rückgängig/Wiederholen)
- **Copy/Cut/Paste** (Kopieren/Ausschneiden/Einfügen)
- **Suchen & Ersetzen** mit Dialog-Boxen
- **Zoom-Funktionen** (Vergrößern/Verkleinern/Reset)
- **Zeilenumbruch** ein/ausschalten

### 📝 **Editor-Features**
- **Markdown Syntax-Highlighting** (Headers, Bold, Italic, Code, Links, Listen, etc.)
- **VSCode-ähnlicher dunkler Editor** mit professionellem Look
- **Monospace-Font** für bessere Code-Darstellung
- **Tab-Unterstützung** (4-Leerzeichen)
- **Professionelle Scrollbalken**
- **Tastenkürzel** für alle Standardfunktionen

## 🚀 Installation

### Linux (Ubuntu/Debian)

```bash
# Dependencies installieren
sudo apt update
sudo apt install -y git build-essential qt6-base-dev imagemagick

# Repository klonen
git clone https://github.com/OlgunBeyaz/mdedit.git
cd mdedit

# Icons erstellen und bauen
chmod +x build.sh install.sh
./build.sh

# System-Installation (optional)
./install.sh
```

### Windows

```bash
# Dependencies (Qt6 von https://www.qt.io/download installieren)
# Git for Windows installieren
# Visual Studio Build Tools installieren

# Repository klonen
git clone https://github.com/OlgunBeyaz/mdedit.git
cd mdedit

# Mit Qt Creator öffnen oder:
cmake -B build
cmake --build build --config Release
```

### macOS

```bash
# Dependencies installieren
brew install qt6 imagemagick

# Repository klonen
git clone https://github.com/OlgunBeyaz/mdedit.git
cd mdedit

# Bauen
chmod +x build.sh
./build.sh
```

## 👨‍💻 Entwickler
**Kemal Akçocuk** - Vollständige Entwicklung in C++ mit Qt6
- **Freeware** - Kostenlos für private und kommerzielle Nutzung
- **Open Source Ansatz** - Einfache Build-Scripts ohne komplexe Dependencies

## 📄 Lizenz

Diese Software ist **Freeware** und kostenlos für private und kommerzielle Nutzung.

© 2025 Kemal Akçocuk - Freie Software für alle