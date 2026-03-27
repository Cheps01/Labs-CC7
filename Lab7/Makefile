CC      = gcc
CFLAGS  = -Wall -Wextra -Iapp -Ilib

BIN     = bin
APP     = app
LIB     = lib

OBJS    = $(BIN)/main.o \
          $(BIN)/bridge.o \
          $(BIN)/threads.o \
		  $(BIN)/utils.o

TARGET  = bridge_system

all: $(BIN) $(TARGET)

$(BIN):
	mkdir -p $(BIN)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/bridge.o: $(APP)/bridge.c $(APP)/bridge.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/threads.o: $(LIB)/threads.c $(LIB)/threads.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/utils.o: $(LIB)/utils.c $(LIB)/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN)