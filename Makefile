CC = g++
LD = -std=c++17 -O3 -Wextra -Wall
SRC = *.cpp
SRCDIR = src
BINDIR = bin
BIN = todo

all: todo

todo: | $(BINDIR)
	$(CC) -o $(BINDIR)/$(BIN) $(SRCDIR)/$(SRC) $(LD)

$(BINDIR):
	mkdir $@

clean:
	@rm -rf $(BINDIR)
