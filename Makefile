CC = g++
LD_RELEASE = -std=c++17 -O3 -Wextra -Wall -Wfatal-errors
LD_DEBUG = -std=c++17 -O3 -Wextra -Wall -Wfatal-errors -g
SRC = *.cpp
SRCDIR = src
BINDIR = bin
PKGDIR = pkg
BIN = todo

all: debug

debug: | $(BINDIR)
	$(CC) -o $(BINDIR)/$(BIN) $(SRCDIR)/$(SRC) $(LD_DEBUG)

$(BINDIR):
	mkdir $@

release: | $(PKGDIR)
	$(CC) -o $(PKGDIR)/$(BIN) $(SRCDIR)/$(SRC) $(LD_RELEASE)
	@strip -s $(PKGDIR)/$(BIN)

$(PKGDIR):
	mkdir $@

clean:
	@rm -rf $(BINDIR)

install:
	sudo install $(PKGDIR)/$(BIN) /usr/local/bin/
