#!/bin/bash

INSTALL_DIR="$HOME/.local/bin"
PROGRAM_NAME="gdpoise"

echo "Uninstalling the program..."
rm -f "$INSTALL_DIR/$PROGRAM_NAME"

if grep -q "$INSTALL_DIR" "$HOME/.zshrc"; then
  echo "Removing $INSTALL_DIR from PATH..."
  sed -i '/\.local\/bin/d' "$HOME/.zshrc"
  
  source "$HOME/.zshrc"
else
  echo "$INSTALL_DIR not found in PATH. No changes made to ~/.zshrc."
fi

echo "Uninstallation complete."

