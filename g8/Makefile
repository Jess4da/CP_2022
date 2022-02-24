.SILENT:

all: clean main.o

run: clean main.o main.r

main.o:
	@echo [Make] compiling main.c
	gcc main.c -o main

main.r:
	@echo [Make] running main.exe
	./main.exe

clean:
	@echo [Make] cleaning main.exe
	-@del main.exe