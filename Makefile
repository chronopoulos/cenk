all:
	gcc main.c -ljack -lm -o cenk

clean:
	rm cenk
