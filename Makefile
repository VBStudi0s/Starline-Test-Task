build/Makefile:
	@mkdir -p build
	@cd build && cmake ..

build: build/Makefile
	@cmake --build build

.PHONY: build/Makefile build start

start: build
	@cd ./build && ./main

clean:
	@rm -rf build
