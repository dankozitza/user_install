# e3b3630f37a77f61eb8e51d964e44e85
# Generated with vfnmkmc by the mc program.
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/sort_test.o


.PHONY: all
all: objs sort_test

./sort_test:  $(OBJS)
	@ echo "    LINK ./sort_test"
	@ $(CXX) $(OBJS) -o "./sort_test" $(LFLAGS)

objs/sort_test.o: src/sort_test.cpp src/sorters.hpp
	@ echo "    CXX  src/sort_test.cpp"
	@ $(CXX) $(CFLAGS) -c "src/sort_test.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./sort_test"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././sort_test

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
	@ install -D -m 755 sort_test $(PREFIX)/bin/sort_test
	@ echo "[1;32m*[0m sort_test installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove sort_test[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/sort_test
	@ echo "[1;32m*[0m sort_test removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S src/*
