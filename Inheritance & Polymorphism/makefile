#instructions to create executable file *MUST COME FIRST*
a.exe: account.o checking.o savings.o main.o
	g++ account.o checking.o savings.o main.o

#instructions to create account.o file, checks timestamps of .h and .cpp files
account.o: account.h account.cpp
	g++ -c -g account.cpp

#instructions to create checking.o file, checks timestamps of .h and .cpp files
checking.o: checking.h checking.cpp
	g++ -c -g checking.cpp

#instructions to create savings.o file, checks timestamps of .h and .cpp files
savings.o: savings.h savings.cpp
	g++ -c -g savings.cpp

#instructions to create main.o file, checks timestamps of all .h files and main.cpp
main.o: account.h checking.h savings.h main.cpp
	g++ -c -g main.cpp

#clean process to clear all .o files and a.exe executable file
clean:
	del *.o a.exe