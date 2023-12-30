all: scheduler

scheduler: scheduler.c
	gcc -o scheduler scheduler.c -Wall -Werror

clean:
	rm -f scheduler
