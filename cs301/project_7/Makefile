# d76739025e19b285de4a9939384c4015
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/infixcalc.o objs/Infxcalc.o objs/L_Stack.o


.PHONY: all
all: objs infixcalc

./infixcalc:  $(OBJS)
	@ echo "    LINK ./infixcalc"
	@ $(CXX) $(OBJS) -o "./infixcalc" $(LFLAGS)

objs/infixcalc.o: src/infixcalc.cpp src/Infxcalc.hpp src/L_Stack.hpp
	@ echo "    CXX  src/infixcalc.cpp"
	@ $(CXX) $(CFLAGS) -c "src/infixcalc.cpp" -o $@
objs/Infxcalc.o: src/Infxcalc.cpp src/Infxcalc.hpp src/L_Stack.hpp
	@ echo "    CXX  src/Infxcalc.cpp"
	@ $(CXX) $(CFLAGS) -c "src/Infxcalc.cpp" -o $@
objs/L_Stack.o: src/L_Stack.cpp src/L_Stack.hpp
	@ echo "    CXX  src/L_Stack.cpp"
	@ $(CXX) $(CFLAGS) -c "src/L_Stack.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./infixcalc"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././infixcalc

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
	@ install -D -m 755 infixcalc $(PREFIX)/bin/infixcalc
	@ echo "[1;32m*[0m infixcalc installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove infixcalc[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/infixcalc
	@ echo "[1;32m*[0m infixcalc removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S src/*
