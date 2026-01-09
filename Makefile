all: build

run:
	./chronosyncher

build:
	gcc chronosyncher.c -o chronosyncher