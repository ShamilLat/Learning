CXX = clang++ 
CXXFLAGS = -std=c++17 -Werror 

all: main

main: main.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@ 

test: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ 

.PHONY: clean 

clean: 
	rm test
	rm main
