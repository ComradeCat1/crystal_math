comp: expr.c interp.c main.c scan.c tree.c compile.c
	gcc -o te -g expr.c interp.c main.c scan.c tree.c compile.c

clean:
	rm -f te te2 *.o

interp: interp.c main2.c
	gcc -o interp -g interp.c main2.c

test: parser
	-(./parser input01; \
	 ./parser input02; \
	 ./parser input03; \
	 ./parser input04; \
	 ./parser input05)

test2: parser2
	-(./parser2 input01; \
	 ./parser2 input02; \
	 ./parser2 input03; \
	 ./parser2 input04; \
	 ./parser2 input05)