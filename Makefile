# CPU
FFTW_LIBS = -lfftw3
CPULIBS = $(FFTW_LIBS)
CPUCC=gcc

# GPU
CUFFT_LIBS = -lcufft
CUDA_LIBS = -lcuda
GPULIBS = $(CUDA_LIBS) $(CUFFT_LIBS)
GPUCC=nvcc

CC=$(CPUCC)

CFLAGS= -O2

fftw_1d_objs = fftw_1d.o
fftw_1d.x:	$(fftw_1d_objs)
	$(CC) $(CFLAGS) -o fftw_1d.x $(fftw_1d_objs) $(CPULIBS)		


clean:
	rm *.o *.x -rf
	rm *.*~ -rf
	rm *~ -rf

.SUFFIXES:      .c

.c.o:
	$(CC) $(CFLAGS)  -c $<

