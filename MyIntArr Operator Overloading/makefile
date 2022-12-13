a.exe: main.o MyIntArr.o
	g++ main.o MyIntArr.o

MyIntArr.o: MyIntArr.h MyIntArr.cpp
	g++ -c -g MyIntArr.cpp

main.o: MyIntArr.h main.cpp
	g++ -c -g main.cpp

clean:
	del *.o a.exe