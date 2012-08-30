CC=gcc
CFLAGS=
LFLAGS=
OBJS=main.o bit_operations.o tree.o priority_queue.o count_dictionary.o compressor.o bit_stream.o code_dictionary.o

all: compressor clean

compressor: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -f *.o