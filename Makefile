CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wno-unused-function -std=c99 -O2
LDLIBS = -lm -lAX12 -lwiringPi
LDLIBS_DB = -lm
SRCS = src/main.c \
       src/coordinate.c \
       src/parse.c \
       src/path.c \
       src/ax12.c \
       src/pump.c
OBJS = $(SRCS:%.c=%.o)
OUT = nutella
IN_FILE = star5.txt

.PHONY: clean run db format stop gui

run: $(OUT)
	./$< $(IN_FILE) 320

format: $(SRCS:%.c=%.format)

%.format: %.c
	clang-format $^ > $@
	mv $@ $^

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(DB) -o $@ $^ $(LDLIBS)

db:
	make $(OUT) CFLAGS="$(CFLAGS) -D DEBUG=1" LDLIBS="$(LDLIBS_DB)"
	make run

stop_pump: $(OBJS:src/main.o=) src/stop_pump.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

stop: stop_pump
	./$<

gui:
	gui/build-nutella_draw-Desktop-Debug/nutella_draw

%:
	make run IN_FILE="$@.txt"

clean:
	rm -f $(OBJS)
	rm -f $(OUT)
	rm -f src/stop_pump
