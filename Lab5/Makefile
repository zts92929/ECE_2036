test_matrix : main.o matrix.o complex.o
	g++ -std=c++0x -o test_matrix main.o matrix.o complex.o 

main.o : main.cc matrix.h complex.h
	g++ -c -std=c++0x main.cc

matrix.o : matrix.cc matrix.h complex.h
	g++ -c -std=c++0x matrix.cc 

complex.o : complex.cc complex.h
	g++ -c -std=c++0x complex.cc

