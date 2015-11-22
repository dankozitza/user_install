# b3bec6377e6c562fa09ea19e58d44404
# Generated with vfnmkmc by the mc program.
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/concordance.o objs/getconc.o


.PHONY: all
all: objs getconc

./getconc:  $(OBJS)
	@ echo "    LINK ./getconc"
	@ $(CXX) $(OBJS) -o "./getconc" $(LFLAGS)

objs/concordance.o: src/concordance.cpp src/concordance.hpp
	@ echo "    CXX  src/concordance.cpp"
	@ $(CXX) $(CFLAGS) -c "src/concordance.cpp" -o $@
objs/getconc.o: src/getconc.cpp src/concordance.hpp
	@ echo "    CXX  src/getconc.cpp"
	@ $(CXX) $(CFLAGS) -c "src/getconc.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./getconc"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././getconc

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: sc superclean
sc: superclean
superclean: clean
	@ rm -rf "deps"
	@ echo "    SUPERCLEAN"

.PHONY: install
install: all
	@ install -D -m 755 getconc $(PREFIX)/bin/getconc
	@ echo "[1;32m*[0m getconc installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove getconc[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/getconc
	@ echo "[1;32m*[0m getconc removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S src/*
