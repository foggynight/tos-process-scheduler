CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic
LIBS=-lpthread
DEBUGFLAGS=-g

SRCS=$(wildcard src/*.c)
INCS=$(wildcard src/list/*.c)

OBJS=$(SRCS:%.c=%.o)
OBJS+=$(INCS:%.c=%.o)

PROG=kernel

all: $(PROG)
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG) $(LIBS)
$(OBJS): $(SRCS)
$(OBJS): $(INCS)

# Build program with debug flags
debug: $(SRCS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(SRCS) $(INCS) -o $(PROG) $(LIBS)

# Delete object files
.PHONY: clean
clean:
	rm -f $(OBJS)

# Delete object files and program executable
.PHONY: uninstall
uninstall:
	rm -f $(OBJS) $(PROG)

# Build, execute, and cleanup test suite
.PHONY: test
test:
	@+for test in $(wildcard src/test/*); do\
	 	$(CC) $(CFLAGS) $(INCS) -o src/test/test $$test;\
	 	src/test/test;\
	 	rm src/test/test;\
	done;\
