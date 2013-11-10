#Object files
PROJECT = obj/angleConversion.o obj/haversine.o obj/main.o obj/plane.o

#Compiler flags
LDFLAGS = -lm
CXXFLAGS = -std=gnu++11 -O2

all: software

obj/angleConversion.o: src/angleConversion.cpp
	g++ src/angleConversion.cpp -c -o obj/angleConversion.o $(CXXFLAGS)
obj/haversine.o: src/haversine.cpp
	g++ src/haversine.cpp -c -o obj/haversine.o $(CXXFLAGS)
obj/main.o: src/main.cpp
	g++ src/main.cpp -c -o obj/main.o $(CXXFLAGS)
obj/plane.o: src/plane.cpp
	g++ src/plane.cpp -c -o obj/plane.o $(CXXFLAGS)

#Compilation
software: $(PROJECT)
	g++ $(PROJECT) $(CXXFLAGS) $(LDFLAGS) -o bin/flight

clean:
	rm -f $(PROJECT)
