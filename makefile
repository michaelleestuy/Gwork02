run:
	gcc line.c -o test.out
	rm -f basic.ppm basic.png
	./test.out
	convert basic.ppm basic.png
