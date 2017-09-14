start:	P3_header.h DapC_00_P3_main.cpp DapC_00_P3_func.cpp
	g++ -o prog3 P3_header.h DapC_00_P3_main.cpp DapC_00_P3_func.cpp -I.

run:	prog3
	./prog3