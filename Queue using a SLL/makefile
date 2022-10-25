#1. First line must be how to generate an executable
#  colon(:) means dependency -> list all the files that are used to create the file prior to the colon
#  executable_file_name: list of all .o files with a whitespace
a.exe: main.o queue.o
#	command to create a.exe that must start with a tab
	g++ main.o queue.o

#2. How to build each .o file
main.o: queue.h main.cpp
#	only one single cpp file with g++ -c
#	-g to use gdb debugger
	g++ -c -g main.cpp

queue.o: queue.h queue.cpp
	g++ -c -g queue.cpp

clean:
	del *.o a.exe