#动态库编译文件
CFLAGS = -Wall -g 

all: clean test libtestso.o

libtestso.o:
	gcc $(CFLAGS) -fPIC -c cJSON.c -o libtestso.o

libtestso.so:
	gcc -g -shared libtestso.o -lm -ldl -lpthread -o libtestso.so

test:
	gcc -g test.c -ldl -L . -ltestso -o test

clean:
	@rm -vf test *.o
