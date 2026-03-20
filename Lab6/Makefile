CC      = gcc
SRC_DIR = lib
BIN_DIR = bin

SRCS = main.c $(SRC_DIR)/threads.c $(SRC_DIR)/parking.c $(SRC_DIR)/utils.c
OBJS = $(BIN_DIR)/main.o $(BIN_DIR)/threads.o $(BIN_DIR)/parking.o $(BIN_DIR)/utils.o
TARGET = smart_parking

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/utils.o: $(SRC_DIR)/utils.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BIN_DIR)/parking.o: $(SRC_DIR)/parking.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BIN_DIR)/threads.o: $(SRC_DIR)/threads.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BIN_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)