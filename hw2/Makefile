target = demo
CPPFLAGS = -O2 -std=c++11 -Wall

all: $(target)

demo: main.cpp ReadDate.cpp ReadDate.h
	g++ $(CPPFLAGS) main.cpp ReadDate.cpp -o $@
                        
clean:
	rm -rf $(target)