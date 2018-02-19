target = system
CPPFLAGS = -O2 -std=c++11 -Wall

all: $(target)

system: main.cpp binomial_heap.h
	g++ $(CPPFLAGS) main.cpp -o $@
                        
clean:
	rm -rf $(target)