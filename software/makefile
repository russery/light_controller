CC=gcc
CFLAGS=-I.
DEPS = bitarray.h
OBJ = rf_devel.o bitarray.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rf_devel: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
