KERNEL = 2.6.32-358.el6.x86_64
CFLAGS = -I/usr/src/kernels/$(KERNEL) 
SUBDIRS = kgpu services scripts
CC = gcc $(CFLAGS)
NVCC = nvcc $(CFLAGS)
N = @echo

all: $(SUBDIRS)


notice:
		$(N) "Building modules for $(KERNEL)"
		

.PHONY: $(SUBDIRS)

$(SUBDIRS): mkbuilddir
	$(MAKE) -C $@ $(TARGET) kv=$(kv) BUILD_DIR=`pwd`/build

mkbuilddir:
	mkdir -p build

services: kgpu

distclean:
	$(MAKE) all kv=$(kv) TARGET=clean

clean: distclean
	rm -rf build
