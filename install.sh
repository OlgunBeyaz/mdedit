#!/bin/bash
# Installation script for mdedit

set -e

INSTALL_DIR="/usr/local/bin"
DESKTOP_DIR="$HOME/.local/share/applications"
ICON_THEME_DIR="$HOME/.local/share/icons/hicolor"
CURRENT_DIR="$(pwd)"

echo "Installing mdedit Markdown Editor..."
echo "Author: Kemal Akçocuk | Freeware"
echo ""

# 1. Copy binary to system path
echo "Installing binary to $INSTALL_DIR..."
sudo cp build/mdedit "$INSTALL_DIR/"
sudo chmod +x "$INSTALL_DIR/mdedit"

# 2. Install icons
echo "Installing icons..."
ICON_SIZES="16 32 48 128"
for size in $ICON_SIZES; do
    mkdir -p "$ICON_THEME_DIR/${size}x${size}/apps"
    cp "icons/mdedit-${size}.png" "$ICON_THEME_DIR/${size}x${size}/apps/mdedit.png"
done
mkdir -p "$ICON_THEME_DIR/scalable/apps"
cp "mdedit.svg" "$ICON_THEME_DIR/scalable/apps/mdedit.svg"

# 3. Create desktop entry for current user
echo "Creating desktop entry..."
mkdir -p "$DESKTOP_DIR"
sed "s|Exec=.*|Exec=$INSTALL_DIR/mdedit|" mdedit.desktop > "$DESKTOP_DIR/mdedit.desktop"
chmod +x "$DESKTOP_DIR/mdedit.desktop"

# 4. Update desktop and icon databases
if command -v update-desktop-database >/dev/null 2>&1; then
    echo "Updating desktop database..."
    update-desktop-database "$DESKTOP_DIR" 2>/dev/null || true
fi

if command -v gtk-update-icon-cache >/dev/null 2>&1; then
    echo "Updating icon cache..."
    gtk-update-icon-cache "$ICON_THEME_DIR" 2>/dev/null || true
fi

echo ""
echo "✅ mdedit successfully installed!"
echo ""
echo "Features:"
echo "  • Splash screen with author info"
echo "  • Info menu: Hilfe → Über mdedit"
echo "  • Custom icon and desktop integration"
echo "  • Freeware - kostenlos für alle!"
echo ""
echo "You can now:"
echo "  • Run 'mdedit' from terminal"
echo "  • Find 'mdedit' in your application menu"
echo "  • Right-click .md files → 'Open with mdedit'"
echo ""
echo "To uninstall, run: sudo rm $INSTALL_DIR/mdedit && rm $DESKTOP_DIR/mdedit.desktop"