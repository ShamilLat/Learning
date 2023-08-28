CXX = g++ 
CXXFLAGS = -Wall -Werror -g -std=gnu++17 -D_GNU_SOURCE 

all: main

main: main.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@ -lm 

test: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -lm 

.PHONY: clean 

clean: 
	rm main
	rm test