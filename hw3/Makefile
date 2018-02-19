target = 3_4_1.out 3_4_2.out
CFLAGS = -O2 -Wall
CPPFLAGS = -O2 -std=c++11 -Wall

all: $(target)

3_4_1.out: 1.cpp 
	g++ $(CPPFLAGS) 1.cpp -o $@
3_4_2.out: 2.cpp 
	g++ $(CPPFLAGS) 2.cpp -o $@
                        
clean:
	rm -rf $(target)