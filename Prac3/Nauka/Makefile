CXX = clang++ 
CXXFLAGS = -std=c++17 -Werror 

all: main

main: main.cpp 
	$(CXX) $(CXXFLAGS) ip.cpp id.cpp log_string.cpp functions.cpp $< -o $@ 

test: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ 

.PHONY: clean 

clean: 
	rm main
	rm schedule*
