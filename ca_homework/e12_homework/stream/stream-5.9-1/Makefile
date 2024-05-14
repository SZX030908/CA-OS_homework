CC = gcc
CFLAGS = -O2
CFLAGS1 = -O3

FF = g77
FFLAGS = -O2
LPTBIN=/usr/local/bin

all:  stream stream_mu stream_O3 stream_mu_O3
#stream_f.exe: stream.f mysecond.o
#	$(CC) $(CFLAGS) -c mysecond.c
#	$(FF) $(FFLAGS) -c stream.f
#	$(FF) $(FFLAGS) stream.o mysecond.o -o stream_f.exe

stream: stream.c
	$(CC) $(CFLAGS) stream.c -o stream
	
stream_O3: stream.c
	$(CC) $(CFLAGS1) stream.c -o stream_O3

stream_mu: stream.c
	$(CC) $(CFLAGS) -fopenmp  stream.c -o stream_mu

stream_mu_O3: stream.c
	$(CC) $(CFLAGS1) -fopenmp  stream.c -o stream_mu_O3
	
clean:
	rm -f stream *.o
	rm -f stream_O3
	rm -r stream_mu
	rm -r stream_mu_O3
	rm -f $(LPTBIN)/stream_mu
	rm -f $(LPTBIN)/stream
install:
	cp -r stream $(LPTBIN)/stream
	cp -r stream_mu $(LPTBIN)/stream_mu
