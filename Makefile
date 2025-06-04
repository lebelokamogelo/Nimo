CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build

$(shell mkdir -p $(BUILD_DIR))

all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(SRC_DIR)/main.c lexer/lexer.c parser/parser.c
	$(CC) $(CFLAGS) $< -o $@

run: $(BUILD_DIR)/main
	./$(BUILD_DIR)/main

clean:
	rm -rf $(BUILD_DIR)
