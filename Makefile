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
	simplecheck \
	limits

.PHONY: all clean
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
