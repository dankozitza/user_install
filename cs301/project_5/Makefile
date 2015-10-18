# 542c132c44d2df28a9b36b8c8dbfae55
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/d_list.o objs/backspace.o


.PHONY: all
all: objs backspace

./backspace:  $(OBJS)
	@ echo "    LINK ./backspace"
	@ $(CXX) $(OBJS) -o "./backspace" $(LFLAGS)

objs/d_list.o: src/d_list.cpp src/d_list.hpp
	@ echo "    CXX  src/d_list.cpp"
	@ $(CXX) $(CFLAGS) -c "src/d_list.cpp" -o $@
objs/backspace.o: src/backspace.cpp src/d_list.hpp
	@ echo "    CXX  src/backspace.cpp"
	@ $(CXX) $(CFLAGS) -c "src/backspace.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./backspace"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././backspace

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
	@ install -D -m 755 backspace $(PREFIX)/bin/backspace
	@ echo "[1;32m*[0m backspace installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove backspace[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/backspace
	@ echo "[1;32m*[0m backspace removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S src/*
