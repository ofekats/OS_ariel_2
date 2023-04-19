CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

CODEC_A_OBJS = codecA.o
CODEC_B_OBJS = codecB.o
CMP_OBJS = cmp.o
COPY_OBJS = copy.o
ENCODE_OBJS = encode.o
DECODE_OBJS = decode.o

CODEC_A_LIB = libcodecA.so
CODEC_B_LIB = libcodecB.so

all: libcodecA.so libcodecB.so encode decode cmp copy

libcodecA.so: $(CODEC_A_OBJS) codec.h
	$(CC) $(LDFLAGS) -o $@ $^

libcodecB.so: $(CODEC_B_OBJS) codec.h
	$(CC) $(LDFLAGS) -o $@ $^

cmp: $(CMP_OBJS)
	$(CC) -o $@ $^

copy: $(COPY_OBJS)
	$(CC) -o $@ $^

encode: $(ENCODE_OBJS) codec.h
	$(CC) -o $@ $^ -ldl

decode: $(DECODE_OBJS) codec.h
	$(CC) -o $@ $^ -ldl

clean:
	rm -f libcodecA.so libcodecB.so cmp copy encode decode *.o
