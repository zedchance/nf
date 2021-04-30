all: nf

nf: nf.c
	clang nf.c -o nf

clean:
	rm nf

test: nf test.nf
	./nf test.nf
