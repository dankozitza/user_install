# 6a7a818ba1223a6867ce8680aad722d4
PREFIX=/usr/local
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/are_anagrams.o


.PHONY: all
all: objs are_anagrams

./are_anagrams: $(OBJS)
	@ echo "    LINK ./are_anagrams"
	@ $(CXX) $(OBJS) -o "./are_anagrams" $(LFLAGS)

objs/are_anagrams.o: are_anagrams.cpp
	@ echo "    CXX  ./are_anagrams.cpp"
	@ $(CXX) $(CFLAGS) -c "./are_anagrams.cpp" -o $@

objs:
	@ mkdir "objs"

.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./are_anagrams"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././are_anagrams

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
	@ install -D -m 755 mc $(PREFIX)/bin/are_anagrams
	@ echo "[1;32m*[0m are_anagrams installed in $(PREFIX)/bin"
	@ echo "[1muse \`make uninstall\` to remove are_anagrams[0m"

.PHONY: uninstall
uninstall:
	@ rm $(PREFIX)/bin/are_anagrams
	@ echo "[1;32m*[0m are_anagrams removed from $(PREFIX)/bin[0m"

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S ./*
