build-debug/Makefile:
	@mkdir -p build_debug
	@cd build_debug && cmake -DBUILD_TESTS=ON ..

build-release/Makefile:
	@mkdir -p build_release
	@cd build_release && cmake -DBUILD_TESTS=OFF ..

build-debug: build-debug/Makefile
	@cmake --build build_debug

build-release: build-release/Makefile
	@cmake --build build_release

.PHONY: build-release/Makefile build-release build-debug/Makefile build-debug start tests

start-release: build-release
	@cd ./build_release && ./main

start-debug: build-debug
	@cd ./build_debug && ./main

tests: build-debug
	@cd ./build_debug/unittests && ./runUnitTests

clean:
	@rm -rf build*
