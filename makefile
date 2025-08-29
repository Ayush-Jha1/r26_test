CXX = g++
CXXFLAGS = -std=c++17 -Og -g -Wall

# default target
all: main

# alias for build
build: main

# build main executable
main: src/*.cpp
	$(CXX) $(CXXFLAGS) src/*.cpp -Ilib -o main.exe

check: main
	@echo "--------------------------------------------"
	@echo "Checking..."
	@echo "Test-1: "
	main.exe test\testcase1.txt test\result1.txt
	fc test\result1.txt test\expected1.txt
	@echo "Test-2: "
	main.exe test\testcase2.txt test\result2.txt
	fc test\result2.txt test\expected2.txt
	@echo "Test-3: "
	main.exe test\testcase3.txt test\result3.txt
	fc test\result3.txt test\expected3.txt
	@echo "**** Success: ***"
	@echo "--------------------------------------------"

clean:
	del /Q main.exe test\result* 2>nul || echo "Nothing to clean"

.PHONY: all clean check

