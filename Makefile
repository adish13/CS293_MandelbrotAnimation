all: executables/mandel executables/mandel_dd

executables/mandel: mandel.cpp
	g++ -O3 -Wall mandel.cpp -o executables/mandel -lm

executables/mandel_dd: mandel_dd.cpp
	g++ -O3 -Wall mandel_dd.cpp -o executables/mandel_dd -lm

