all: c.c
	gcc -o pipo c.c

debug: c.c
	gcc -o debugo -g c.c

run: all
	./pipo

clean:
	rm pipo debugo *~
