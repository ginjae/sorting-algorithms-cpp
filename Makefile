SANFLAGS = -fsanitize=address
CXX = g++
CXXFLAGS = -std=c++17 $(SANFLAGS) -O2
DEPS = algorithms/bubble_sort.h algorithms/cocktail_shaker_sort.h algorithms/comb_sort.h	\
		algorithms/heap_sort.h algorithms/insertion_sort.h algorithms/intro_sort.h	\
		algorithms/library_sort.h algorithms/merge_sort.h algorithms/quick_sort.h	\
		algorithms/selection_sort.h algorithms/tim_sort.h algorithms/tournament_sort.h

main:	main.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

eval:	eval.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) main eval