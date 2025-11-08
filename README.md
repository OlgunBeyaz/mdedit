# mdedit — einfacher Markdown-Editor (C++ / Qt)

Kleines, schlankes Qt-Programm zum Erstellen, Öffnen, Bearbeiten und Speichern von Markdown-Dateien mit Live-Preview.

## Features

### 🎨 **Professionelle Benutzeroberfläche**
- **VSCode-ähnlicher dunkler Editor** mit Syntax-Highlighting
- **GitHub-Style Preview** mit professionellem CSS-Styling
- **Geteiltes Fenster** mit anpassbarer Größe
- **Splash Screen** beim Start mit Autoreninfo

### �️ **Toolbar & Texteditor-Funktionen**
- **Emoji-Toolbar** mit allen wichtigen Funktionen
- **Undo/Redo** (Rückgängig/Wiederholen)
- **Copy/Cut/Paste** (Kopieren/Ausschneiden/Einfügen)
- **Suchen & Ersetzen** mit Dialog-Boxen
- **Zoom-Funktionen** (Vergrößern/Verkleinern/Reset)
- **Zeilenumbruch** ein/ausschalten

### �📝 **Editor-Features**
- **Markdown Syntax-Highlighting** (Headers, Bold, Italic, Code, Links, Listen, etc.)
- **VSCode-ähnlicher dunkler Editor** mit professionellem Look
- **Monospace-Font** für bessere Code-Darstellung
- **Tab-Unterstützung** (4-Leerzeichen)
- **Professionelle Scrollbalken**
- **Tastenkürzel** für alle Standardfunktionen

### 👁️ **Live-Preview**
- **GitHub-ähnliche Darstellung**
- **Professionelle Typografie** (System-Fonts)
- **Syntax-Highlighting** für Code-Blöcke
- **Responsive Tables** und Listen
- **Styled Headers** mit Unterstrichen

### 💾 **Datei-Management**
- Neues Dokument erstellen
- Öffnen (Import) von Markdown-Dateien (*.md, *.markdown)
- Speichern / Speichern als
- **Smart Save** mit Bestätigungsdialogen

### ⚡ **Tastenkürzel**
- `Ctrl+N` - Neue Datei
- `Ctrl+O` - Öffnen
- `Ctrl+S` - Speichern
- `Ctrl+Z` - Rückgängig
- `Ctrl+Y` - Wiederholen  
- `Ctrl+X/C/V` - Ausschneiden/Kopieren/Einfügen
- `Ctrl+F` - Suchen
- `Ctrl+H` - Ersetzen
- `Ctrl+Plus/Minus` - Zoom ein/aus

### ℹ️ **Weitere Features**
- **Info-Menü** (Hilfe → Über mdedit) mit Entwicklerinfo
- **Freeware-Status** prominent angezeigt
- **Desktop-Integration** mit eigenem Icon

## Voraussetzungen
- Linux (auch macOS/Windows möglich)
- Qt 6.2 oder neuer (Qt Widgets)
- Ein C++17-kompatibler Compiler (g++)
- pkg-config
- ImageMagick (für Icon-Konvertierung)

Build (ohne CMake)

**Option 1: Mit build.sh**
```bash
# im Projekt-Root
chmod +x build.sh
./build.sh
./build/mdedit
```

**Option 2: Mit Makefile**
```bash
# Dependencies prüfen
make check-deps

# Bauen
make

# Ausführen
./build/mdedit
```

**Qt6 installieren (falls noch nicht vorhanden):**
```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev

# Fedora/RedHat
sudo dnf install qt6-qtbase-devel

# Arch Linux
sudo pacman -S qt6-base
```

## 🎯 Technische Highlights

### Qt6 Vorteile
- **Native Markdown-Rendering** mit Qt6s verbesserter Engine
- **Moderne C++17 APIs** für bessere Performance
- **Erweiterte CSS-Unterstützung** für professionelles Styling
- **Robuste Desktop-Integration**

### Code-Qualität
- **Modulare Architektur** (MainWindow, SplashScreen, MarkdownHighlighter)
- **Qt MOC System** für Signal/Slot-Verbindungen
- **Professionelles Error-Handling**
- **Memory-Management** mit Qt Parent-Child System

### Styling-System
- **VSCode-inspirierte Farbschemas**
- **GitHub-kompatible Markdown-Darstellung**
- **Responsive Design** mit anpassbaren Splitter
- **System-Font Integration**

## 👨‍💻 Entwickler
**Kemal Akçocuk** - Vollständige Entwicklung in C++ mit Qt6
- **Freeware** - Kostenlos für private und kommerzielle Nutzung
- **Open Source Ansatz** - Einfache Build-Scripts ohne komplexe Dependencies
- **Professionelle UI/UX** - Moderne Editor-Standards implementiert