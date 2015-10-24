CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Werror

TARGETS = \
	array \
	atoi \
	bits \
	chario \
	control \
	decomment \
	detab \
	entab \
	fold \
	hello \
	limits \
	lines \
	maxline_extern \
	misc \
	power \
	simplecheck \
	strs \
	switch \
	temperature \
	wc

.PHONY: all clean
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
