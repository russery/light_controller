CC=gcc
CFLAGS=-I.
DEPS = bitarray.h crc.h
OBJ = rf_devel.o bitarray.o crc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rf_devel: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
