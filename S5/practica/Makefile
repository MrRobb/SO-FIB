all: mem1_previo mem2_previo mem3_previo mem1 mem2

mem1_previo: mem1_previo.c
	gcc -o mem1_previo mem1_previo.c

mem2_previo: mem2_previo.c
	gcc -o mem2_previo mem2_previo.c

mem3_previo: mem3_previo.c
	gcc -o mem3_previo mem3_previo.c

mem1: mem1.c
	gcc -o mem1 mem1.c

mem2: mem2.c
	gcc -o mem2 mem2.c

clean:
	rm -f *.o mem1_previo mem2_previo mem3_previo mem1 mem2

