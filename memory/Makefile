CXX = gcc
FLAGS = -std=c11 -I ./libs
main.out: main.c memory_blocks.out
	$(CXX) $(FLAGS) $^ -o $@ 

memory_blocks.out: ./libs/memory_blocks.c
	$(CXX) -std=c11 -c $^ -o $@
