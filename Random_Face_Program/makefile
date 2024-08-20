all: Randomface.exe

Randomface.exe: Random_Face.o RWimage.o
	g++ RWimage.o Random_Face.o -o Randomface.exe -lpng

Random_Face.o: Random_Face.cpp RWimage.h
	g++ -c Random_Face.cpp -o Random_Face.o

RWimage.o: RWimage.cpp
	g++ -c RWimage.cpp -o RWimage.o

clean:
	rm -f Randomface.exe Random_Face.o RWimage.o
