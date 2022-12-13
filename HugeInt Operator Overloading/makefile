a.exe: main.o HugeInt.o
	g++ main.o HugeInt.o

main.o: HugeInt.h main.cpp
	g++ -c -g main.cpp

HugeInt.o: HugeInt.h HugeInt.cpp
	g++ -c -g HugeInt.cpp

clean:
	del *.o a.exe