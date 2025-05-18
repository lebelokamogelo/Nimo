CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build

$(shell mkdir -p $(BUILD_DIR))

all: $(BUILD_DIR)/lexer

$(BUILD_DIR)/lexer: $(SRC_DIR)/lexer.c
	$(CC) $(CFLAGS) $< -o $@

run: $(BUILD_DIR)/lexer
	./$(BUILD_DIR)/lexer

clean:
	rm -rf $(BUILD_DIR)
