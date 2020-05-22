# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
arrayTest: test.cpp todolist.cpp
	$(CC) $(CPPFLAGS) test.cpp todolist.cpp -no-pie $(GTEST_LL) -o arrayTest

all: todolist-test

tests: arrayTest
	arrayTest
	-@echo "--- All Tested!---"

todolist-test: todolist-test.cpp todolist.cpp
	g++ -g -Wall  --std=c++11 todolist-test.cpp todolist.cpp -o todolist-test
test: todolist.cpp test.cpp
	g++ -g -Wall  --std=c++11 todolist.cpp test.cpp -o test

clean:
	rm -f *.o todolist-test
	