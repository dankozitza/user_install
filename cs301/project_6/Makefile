# bdc381a4fa3c955eec5b54514c0c942f
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/pofxcalc.o objs/postfixcalc.o objs/Stack.o


.PHONY: all
all: objs postfixcalc

./postfixcalc:  $(OBJS)
	@ echo "    LINK ./postfixcalc"
	@ $(CXX) $(OBJS) -o "./postfixcalc" $(LFLAGS)

objs/pofxcalc.o: src/pofxcalc.cpp src/pofxcalc.hpp src/Stack.hpp
	@ echo "    CXX  src/pofxcalc.cpp"
	@ $(CXX) $(CFLAGS) -c "src/pofxcalc.cpp" -o $@
objs/postfixcalc.o: src/postfixcalc.cpp src/pofxcalc.hpp src/Stack.hpp
	@ echo "    CXX  src/postfixcalc.cpp"
	@ $(CXX) $(CFLAGS) -c "src/postfixcalc.cpp" -o $@
objs/Stack.o: src/Stack.cpp src/Stack.hpp
	@ echo "    CXX  src/Stack.cpp"
	@ $(CXX) $(CFLAGS) -c "src/Stack.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./postfixcalc"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././postfixcalc

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
	@ install -D -m 755 postfixcalc $(PREFIX)/bin/postfixcalc
	@ echo "[1;32m*[0m postfixcalc installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove postfixcalc[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/postfixcalc
	@ echo "[1;32m*[0m postfixcalc removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S src/*
