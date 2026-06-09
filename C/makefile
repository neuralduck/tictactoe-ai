CC      = clang
CFLAGS  = -Wall -Wextra -O2 -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lraylib -lm -lpthread -ldl -lrt -lX11

SRC     = game.c tictactoe.c minimax.c
TARGET  = game

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)