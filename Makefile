CC = gcc
CFLAGS = -g
TARGET_DIR = ./bin
TARGET = $(TARGET_DIR)/gdpoise
SRCDIR = ./src
INSTALL_DIR = $(HOME)/.local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(SRCDIR)/gdpoise.c
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET)
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/
	@if ! echo "$$PATH" | grep -q "$(INSTALL_DIR)"; then \
		echo 'export PATH="$(INSTALL_DIR):$$PATH"' >> $(HOME)/.zshrc; \
		source $(HOME)/.zshrc; \
	fi
	@echo "Installation complete! You can now run: gdpoise"

uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)
	@if grep -q "$(INSTALL_DIR)" "$(HOME)/.zshrc"; then \
		sed -i '/\.local\/bin/d' $(HOME)/.zshrc; \
		source $(HOME)/.zshrc; \
	fi
	@echo "Uninstallation complete."

clean:
	rm -f $(TARGET)
