SRCS = main.c z_math.c func.c stack_raise.c lastx.c file.c
OBJS = main.o z_math.o func.o stack_raise.o lastx.o file.o
BIN 	  = zrpn
CC_FLAGS =  -ansi -Wall -pedantic
CC = gcc
LDFLAGS = -lm
PREFIX = $(HOME)/bin

all : $(BIN)

$(BIN) : $(OBJS)
	$(CC) $(CC_FLAGS) -o $(BIN) $(OBJS) $(LDFLAGS)


install : all
	@echo "Installing $(BIN) to $(DESTDIR)$(PREFIX)..."
	@install -m 755 $(BIN) "$(DESTDIR)$(PREFIX)/$(BIN)"

clean:
	@echo "Removing object files $(OBJS) and executable $(BIN)..."
	@rm -f $(OBJS) $(BIN)


