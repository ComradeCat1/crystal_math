comp: expr.c interp.c main.c scan.c tree.c compile.c
	gcc -o te -g expr.c interp.c main.c scan.c tree.c compile.c

clean:
	rm -f te te2 *.o

interp: interp.c main2.c
	gcc -o interp -g interp.c main2.c

test_tree: test_tree.c
	gcc -o test_tree -g test_tree.c