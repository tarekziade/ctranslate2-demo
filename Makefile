
.PHONY: build

build:
	mkdir -p build
	cd build && cmake .. &&	make -j4
