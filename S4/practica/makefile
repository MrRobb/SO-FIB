all: ejemplo_waitpid ejemplo_waitpid2 alarms signalPerdido ejemplo_signal ejemplo_signal2 eventos

ejemplo_waitpid:ejemplo_waitpid.c
	gcc -o ejemplo_waitpid ejemplo_waitpid.c

ejemplo_waitpid2:ejemplo_waitpid2.c
	gcc -o ejemplo_waitpid2 ejemplo_waitpid2.c

alarms: alarm1 alarm2 alarm3 alarm4

alarm1:ejemplo_alarm1.c
	gcc -o alarm1 ejemplo_alarm1.c 
alarm2:ejemplo_alarm2.c
	gcc -o alarm2 ejemplo_alarm2.c 
alarm3:ejemplo_alarm3.c
	gcc -o alarm3 ejemplo_alarm3.c 
alarm4:ejemplo_alarm4.c
	gcc -o alarm4 ejemplo_alarm4.c 
signalPerdido:signalPerdido.c
	gcc -o signalPerdido signalPerdido.c 
ejemplo_signal: ejemplo_signal.c
	gcc -o ejemplo_signal ejemplo_signal.c
ejemplo_signal2: ejemplo_signal2.c
	gcc -o ejemplo_signal2 ejemplo_signal2.c
eventos: eventos.c
	gcc -o eventos eventos.c

clean:
	rm -rf alarm1 alarm2 alarm3 alarm4 ejemplo_waitpid ejemplo_waitpid2 signalPerdido ejemplo_signal ejemplo_signal2 eventos
