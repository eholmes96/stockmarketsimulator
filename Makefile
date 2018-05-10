all: main.o company.o investor.o tech.o retail.o 
	g++ -std=c++11 main.o company.o investor.o tech.o retail.o -o sms

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

company.o: company.cpp
	g++ -std=c++11 -c company.cpp

investor.o: investor.cpp
	g++ -std=c++11 -c investor.cpp

tech.o: tech.cpp
	g++ -std=c++11 -c tech.cpp 

retail.o: retail.cpp
	g++ -std=c++11 -c retail.cpp

