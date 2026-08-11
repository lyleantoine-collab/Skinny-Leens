# Skinny Leens - Ultra-Lean Build System
# Apache 2.0 License

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -static
TARGET = skinny-init
SRC = src/init.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "[+] Skinny init compiled successfully. Zero bloat detected."

install: $(TARGET)
	@echo "[*] Installing Skinny Leens components..."
	install -d $(DESTDIR)/sbin
	install -m 755 $(TARGET) $(DESTDIR)/sbin/$(TARGET)
	install -m 755 src/swarm_health.sh $(DESTDIR)/usr/local/bin/swarm-health
	@echo "[+] Installation complete. Ready for bare-metal deployment."

clean:
	rm -f $(TARGET)
	@echo "[-] Workspace cleaned."

.PHONY: all install clean
