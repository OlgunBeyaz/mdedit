#!/bin/bash
# Git Repository Setup Script

echo "Setting up mdedit Git repository..."

# Initialize git if not already done
if [ ! -d ".git" ]; then
    git init
    echo "Git repository initialized."
fi

# Create .gitignore if not exists
if [ ! -f ".gitignore" ]; then
    cat > .gitignore << 'EOF'
# Build directories
build/
*.o
*.obj
*.exe
*.app
*.dmg

# Qt MOC files
moc_*.cpp
moc_*.h
*.moc

# IDE files
*.pro.user
*.pro.user.*
.vscode/
.vs/
*.vcxproj
*.vcxproj.filters
*.sln

# OS specific
.DS_Store
Thumbs.db
desktop.ini

# Backup files
*~
*.bak
*.tmp

# Icons (generated)
icons/
*.png
*.ico
*.icns
EOF
    echo ".gitignore created."
fi

# Add all source files
git add src/
git add *.sh
git add *.bat
git add *.md
git add CMakeLists.txt
git add Makefile
git add mdedit.desktop
git add *.svg
git add beispiel.md

# Initial commit if no commits exist
if ! git rev-parse HEAD >/dev/null 2>&1; then
    git commit -m "Initial commit: Professional Markdown Editor with Qt6

Features:
- VSCode-like dark editor with syntax highlighting
- GitHub-style live preview
- Professional toolbar with emoji icons
- Full text editor functions (undo/redo, copy/paste, find/replace)
- Zoom functionality
- Cross-platform support (Linux, Windows, macOS)
- Freeware by Kemal Akçocuk"
    echo "Initial commit created."
fi

echo ""
echo "Git repository ready!"
echo "Next steps:"
echo "1. Create repository on GitHub: https://github.com/new"
echo "2. Add remote: git remote add origin https://github.com/USERNAME/mdedit.git"
echo "3. Push: git push -u origin main"
echo ""
echo "Repository structure:"
git ls-tree --name-only HEAD