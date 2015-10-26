MAKEFLAGS = -j 4
CFLAGS = -Wall -Wextra -Wpedantic -Werror -O3

TARGETS = \
	src/array \
	src/atoi \
	src/bits \
	src/chario \
	src/control \
	src/decomment \
	src/detab \
	src/entab \
	src/expand \
	src/fold \
	src/hello \
	src/limits \
	src/lines \
	src/maxline_extern \
	src/misc \
	src/power \
	src/shellsort \
	src/simplecheck \
	src/strs \
	src/switch \
	src/temperature \
	src/wc

.PHONY: all clean
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
