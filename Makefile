CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wno-unused-function -std=c99
LDLIBS = -lm
SRCS = src/main.c \
	   src/coordinate.c \
       src/parse.c \
	   src/path.c \
	   src/ax12.c
OBJS = $(SRCS:%.c=%.o)
OUT = nutella

.PHONY: clean run

run: $(OUT)
	./$< star5.txt 320

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f $(OBJS)
	rm -f $(OUT)
