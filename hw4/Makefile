target = tree forest
CFLAGS = -O2 -Wall
CPPFLAGS = -O2 -std=c++11 -Wall

all: $(target)

tree: tree.cpp 
	g++ $(CPPFLAGS) tree.cpp -o $@
forest: tree.cpp 
	g++ $(CPPFLAGS) forest.cpp -o $@


                        
clean:
	rm -rf $(target)