MAJOR = 1
MINOR = 0
PATCH = 0
VERSION = "$(MAJOR).$(MINOR).$(PATCH)"

all: test

test: test.c flag.h
	gcc ./test.c -std=c99 -o test -ggdb -Wall -Wextra

clean:
	rm -f test flag.h-*.zip

package: flag.h
	rm -f flag.h-*.zip
	zip flag.h-$(VERSION).zip $^
