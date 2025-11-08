#!/bin/bash
# Icon installation script for mdedit

set -e

ICON_SIZES="16 32 48 128"
ICON_THEME_DIR="$HOME/.local/share/icons/hicolor"
CURRENT_DIR="$(pwd)"

echo "Installing mdedit icons..."

# Create icon theme directories
for size in $ICON_SIZES; do
    mkdir -p "$ICON_THEME_DIR/${size}x${size}/apps"
    cp "icons/mdedit-${size}.png" "$ICON_THEME_DIR/${size}x${size}/apps/mdedit.png"
    echo "  ✓ Installed ${size}x${size} icon"
done

# Install scalable SVG icon
mkdir -p "$ICON_THEME_DIR/scalable/apps"
cp "mdedit.svg" "$ICON_THEME_DIR/scalable/apps/mdedit.svg"
echo "  ✓ Installed scalable SVG icon"

# Update icon cache
if command -v gtk-update-icon-cache >/dev/null 2>&1; then
    echo "Updating icon cache..."
    gtk-update-icon-cache "$ICON_THEME_DIR" 2>/dev/null || true
fi

echo ""
echo "✅ Icons installed successfully!"
echo "The mdedit icon is now available system-wide."