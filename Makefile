# DOJ core Makefile
all: judger.cpp
	mkdir -p out
	g++ judger.cpp DOJ_compile.cpp DOJ_execute.cpp DOJ_judger.cpp -o out/judger

clean:
	rm -f out/judger

