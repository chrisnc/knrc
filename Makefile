CFLAGS= -std=c99 -Wall -Wextra -Wpedantic -Werror

TARGETS = \
	hello \
	temperature \
	chario \
	wc \
	array \
	power \
	lines \
	maxline_extern \
	detab \
	entab \
	fold \
	decomment \
	simplecheck \
	limits \
	misc \
	atoi \
	strs \
	bits \
	control

.PHONY: all clean
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
