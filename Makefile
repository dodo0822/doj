# DOJ core Makefile
all: DOJ.cpp
	mkdir -p out
	g++ DOJ.cpp DOJ_compile.cpp DOJ_execute.cpp DOJ_judger.cpp -o out/DOJ

clean:
	rm -f out/DOJ

