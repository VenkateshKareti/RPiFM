all:
	gcc  FM.c oscillatorPi.c -lpthread
debug:
	gcc -g FM.c oscillatorPi.c -lpthread
release:
	gcc  FM.c oscillatorPi.c -lpthread
