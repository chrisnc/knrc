MAKEFLAGS = -j 4
CFLAGS = -Wall -Wextra -Wpedantic -Werror -O3

TARGETS = \
	array \
	atoi \
	bits \
	chario \
	control \
	decomment \
	detab \
	entab \
	expand \
	fold \
	hello \
	limits \
	lines \
	maxline_extern \
	misc \
	power \
	shellsort \
	simplecheck \
	strs \
	switch \
	temperature \
	wc

.PHONY: all clean
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
