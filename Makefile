CFLAGS= -std=c99 -Wall -Werror

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
	simplecheck

all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) $(TARGETS)
