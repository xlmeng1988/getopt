# a simple example for getopt
TARGET := getopt_example
SRC := main.c
CC := gcc

.PHONY: all

$(TARGET) : $(SRC)
	$(CC) $^ -o $@

all: $(TARGET)

clean:
	rm -f $(TARGET)
