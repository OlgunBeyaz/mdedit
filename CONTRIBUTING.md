# Contributing to mdedit

Vielen Dank für dein Interesse an mdedit! 🎉

## 🚀 Wie du beitragen kannst

### 🐛 Bug Reports
- Öffne ein [Issue](https://github.com/OlgunBeyaz/mdedit/issues)
- Beschreibe das Problem detailliert
- Gib dein Betriebssystem und Qt-Version an
- Füge Screenshots hinzu, wenn möglich

### ✨ Feature Requests  
- Öffne ein [Issue](https://github.com/OlgunBeyaz/mdedit/issues) mit dem Label "enhancement"
- Erkläre den Use Case
- Beschreibe die gewünschte Lösung

### 🔧 Code Contributions

1. **Fork** das Repository
2. **Clone** deinen Fork
3. Erstelle einen **Feature Branch**:
   ```bash
   git checkout -b feature/amazing-feature
   ```
4. **Entwickle** deine Änderung
5. **Teste** gründlich auf verschiedenen Plattformen
6. **Committe** mit aussagekräftiger Message
7. **Push** zum Branch
8. Öffne eine **Pull Request**

## 📋 Development Setup

### Linux/macOS
```bash
git clone https://github.com/OlgunBeyaz/mdedit.git
cd mdedit
sudo apt install qt6-base-dev  # Ubuntu/Debian
./build.sh
```

### Windows
```cmd
git clone https://github.com/OlgunBeyaz/mdedit.git
cd mdedit
# Install Qt6 from qt.io
generate_pro.bat
# Open mdedit.pro in Qt Creator
```

## 🎯 Code Style

- **C++17** Standard
- **Qt6** Coding Conventions
- **4 Spaces** Indentation
- **camelCase** für Variablen
- **PascalCase** für Klassen
- Kommentare in **Deutsch** oder **Englisch**

## 🧪 Testing

- Teste auf **Linux**, **Windows** und **macOS** wenn möglich
- Prüfe verschiedene **Qt6 Versionen**
- Teste **Markdown-Rendering** mit komplexen Dokumenten
- Validiere **UI/UX** auf verschiedenen Bildschirmgrößen

## 📝 Commit Messages

```
feat: Add export to HTML functionality
fix: Fix crash when opening large files  
docs: Update build instructions for Windows
style: Improve toolbar button spacing
refactor: Extract markdown parser to separate class
test: Add unit tests for syntax highlighter
```

## 🎨 UI/UX Guidelines

- **VSCode-ähnliches** dunkles Theme beibehalten
- **GitHub-Style** Preview verwenden
- **Intuitive** Emoji-Icons in Toolbar
- **Responsive** Design für verschiedene Fenstergrößen
- **Accessibility** beachten (Kontrast, Tastaturnavigation)

## 🚀 Release Process

1. Update Version in `CMakeLists.txt` und `src/MainWindow.cpp`
2. Update `README.md` mit neuen Features
3. Teste auf allen Plattformen
4. Create Git Tag: `git tag v1.2.0`
5. Push Tag: `git push origin v1.2.0`
6. GitHub Actions erstellt automatisch Releases

## 💡 Feature Ideas

- **Export to HTML/PDF**
- **Themes/Dark Mode** Toggle
- **Datei-Explorer** Sidebar
- **Plugin System** für Extensions
- **Live Collaboration**
- **Vim/Emacs** Key Bindings
- **Math Formula** Rendering (MathJax)
- **Diagram Support** (Mermaid)

## ❤️ Anerkennung

Alle Contributors werden in der README.md aufgeführt!

---

**Happy Coding! 🎉**