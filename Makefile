CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
TARGET = ccwc
SRCS = main.c 
OBJS = $(SRCS:.c=.o)
DEBUG = 0  # Set this to 1 to enable debugging, 0 to disable

ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

