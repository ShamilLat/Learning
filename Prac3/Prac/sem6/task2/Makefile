CXX = g++ 
CXXFLAGS = -std=c++17

all: main

main: main.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

test: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

main2: main2.cpp
	$(CXX) $(CXXFLAGS) d_m.cpp op.cpp $< -o $@

.PHONY: clean 

clean: 
	rm test
	rm main
