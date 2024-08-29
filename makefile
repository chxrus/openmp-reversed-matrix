CC = g++
ALL_FUNC = $(wildcard ./lib/*.cc)
ALL_HEADER = $(wildcard ./lib/*.h)
CFLAGS = -Wall -Werror -Wextra -fopenmp -std=c++17

run: compile
	cls && matrix.exe

compile: main.cc
	$(CC) main.cc $(CFLAGS) -o matrix.exe

charts:
	python charts.py

clean:
	del /S /Q /F "*.exe"
	del /S /Q /F "tests\*.txt"
	del /S /Q /F "tests\*.png"
	del /S /Q /F "tests\*.svg"
	cls

# check style
style:
	clang-format -n -style=google $(ALL_HEADER) $(ALL_FUNC) main.cc

# repair style in place
style_repair:
	@clang-format -i -style=google $(ALL_HEADER) $(ALL_FUNC) main.cc