# e8c169c7f5dcec7edb58b9098374cb4e
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/qsim.o


.PHONY: all
all: objs qsim

./qsim:  $(OBJS)
	@ echo "    LINK ./qsim"
	@ $(CXX) $(OBJS) -o "./qsim" $(LFLAGS)

objs/qsim.o: src/qsim.cpp src/Q.hpp
	@ echo "    CXX  src/qsim.cpp"
	@ $(CXX) $(CFLAGS) -c "src/qsim.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./qsim"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././qsim

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
	@ install -D -m 755 qsim $(PREFIX)/bin/qsim
	@ echo "[1;32m*[0m qsim installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove qsim[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/qsim
	@ echo "[1;32m*[0m qsim removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S src/*
