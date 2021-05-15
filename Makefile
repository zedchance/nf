all: nf

nf: nf.c
	clang nf.c -o nf

clean:
	rm nf

test: nf hello.nf
	@echo "Expecting 7"
	./nf -e '+++ > ++++ < [ >> + << - ] > [ > + < - ] >.'
	@echo
	@echo "Expecting 7210110810811132871111141081003310"
	./nf hello.nf
	@echo
	./nf -e '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'
