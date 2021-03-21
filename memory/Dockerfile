FROM gcc:latest

COPY . /usr/src/memory

WORKDIR /usr/src/memory

RUN gcc -std=c11 -c ./libs/memory_blocks.c -o memory_blocks.out 

RUN gcc -std=c11 -I ./libs main.c memory_blocks.out -o main.out

CMD ["./main.out"]

# sudo docker run -a stdin -a stdout -i -t memory:latest  