CXX = gcc
FLAGS = -I ./libs -Wall -Wextra -g

main.out: main.c memory_blocks.out
	$(CXX) $(FLAGS) $^ -o $@ 

memory_blocks.out: ./libs/memory_blocks.c
	$(CXX) -c $^ -o $@