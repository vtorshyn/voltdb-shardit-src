SRCDIR=../superchat-src
all: build

build: compile dbc

dbc:
	cd db && $(MAKE) all
compile:
	cd build && cmake $(SRCDIR) && $(MAKE) $(MAKE_FLAGS)
clean:
	rm -rf build/*
	cd db && $(MAKE) stop $@
run: build
	cd db && make run 
test: build run
	cd build && ./voltdb-post-get-cpp localhost "Test run: $(shell date)"
heavy-test: build run
	date
	export COUNTER=0 && \
	time \
	    while test $$COUNTER -lt 10000; \
	do \
	    ./build/voltdb-post-get-cpp localhost "Test run: $$COUNTER" > /dev/null 2>&1;\
	    COUNTER=$$(($$COUNTER+1)); \
	done
	date
stop:
	cd db && $(MAKE) stop $@