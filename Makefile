# Makefile

compile:
	g++ src/generator.cpp -o build/generator
	g++ src/scheduler.cpp -o build/scheduler
	g++ src/validator.cpp -o build/validator

generate:
	./build/generator.exe

schedule:
	./build/scheduler.exe

validate:
	./build/validator.exe

main: generate schedule validate