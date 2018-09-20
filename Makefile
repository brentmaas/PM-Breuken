all:
	@g++ -o Assignment1 src/maas1.cc -std=c++17 -Wall -Wextra

clean:
	@rm Assignment1.exe

run:
	@./Assignment1.exe