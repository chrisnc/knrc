CFLAGS= -std=c99 -Wall -Werror

TARGETS = \
	hello \
	temperature \
	chario \
	wc \
	array \
	power \
	lines

all: $(TARGETS)

.PHONY: clean
clean:
	$(RM) -f $(TARGETS)
