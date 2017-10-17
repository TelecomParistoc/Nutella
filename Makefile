CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wno-unused-function -std=c99
LDLIBS = -lm -lAX12
LDLIBS_DB = -lm
SRCS = src/main.c \
	   src/coordinate.c \
       src/parse.c \
	   src/path.c \
	   src/ax12.c
OBJS = $(SRCS:%.c=%.o)
OUT = nutella

.PHONY: clean run db format

run: $(OUT)
	./$< star5.txt 320

format: $(SRCS:%.c=%.format)

%.format: %.c
	clang-format $^ > $@
	mv $@ $^

$(OUT): $(OBJS)
	make format
	$(CC) $(CFLAGS) $(DB) -o $@ $^ $(LDLIBS)

db:
	make $(OUT) CFLAGS="$(CFLAGS) -D DEBUG=1" LDLIBS="-lm"
	./$(OUT) star5.txt 320

clean:
	rm -f $(OBJS)
	rm -f $(OUT)

