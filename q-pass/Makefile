CFLAGS= -Wall -Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)
qpass	:	qpass.o stack.o stack.h queue.o queue.h
		$(CC) -o qpass qpass.o stack.o queue.o
stack.o qpass.o	:	qpass.c stack.c stack.h queue.h
	$(CC) -c qpass.c stack.c queue.c
.PHONY  :	clean
clean   :
	-rm -f qpass qpass.o stack.o queue.o infer-out
infer   : clean
	make clean; infer-capture -- make; infer-analyze -- make
