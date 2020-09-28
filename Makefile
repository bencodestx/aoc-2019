CC=clang-10
CXX=clang++-10

all:
	mkdir -p .build
	cd .build && cmake -DCMAKE_BUILD_TYPE=Release ..
	cd .build && ${MAKE} all

clean:
	rm -rf .build
