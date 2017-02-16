deq: main_link.o libdeq.so
    gcc -o deq main_link.o -L. -ldeq -Wl,-rpath,.

main_link.o: main_link.c
    gcc -c main_link.c

libdeq.so: deq.o
    gcc -shared -o libdeq.so deq.o

deq.o: deq.c
    gcc -c -fPIC deq.c

clean:
    rm -f *.o deq