# 683ad5ad80f40e86f8d9e0b464049a41
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/Set.o objs/modsets.o


.PHONY: all
all: objs modsets

./modsets: $(OBJS)
	@ echo "    LINK ./modsets"
	@ $(CXX) $(OBJS) -o "./modsets" $(LFLAGS)

objs/Set.o: src/Set.cpp src/Set.hpp
	@ echo "    CXX  src/Set.cpp"
	@ $(CXX) $(CFLAGS) -c "src/Set.cpp" -o $@
objs/modsets.o: src/modsets.cpp src/Set.hpp
	@ echo "    CXX  src/modsets.cpp"
	@ $(CXX) $(CFLAGS) -c "src/modsets.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./modsets"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././modsets

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
	@ install -D -m 755 mc $(PREFIX)/bin/modsets
	@ echo "[1;32m*[0m modsets installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove modsets[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/modsets
	@ echo "[1;32m*[0m modsets removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S src/*
