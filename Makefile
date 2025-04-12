SANFLAGS = -fsanitize=address
CXX = g++
CXXFLAGS = -Wall -std=c++23 $(SANFLAGS) -O2
DEPS = algorithms/merge_sort.h algorithms/insertion_sort.h algorithms/heap_sort.h algorithms/bubble_sort.h algorithms/quick_sort.h algorithms/selection_sort.h

main:	main.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) main