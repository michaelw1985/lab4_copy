CPP = g++ -std=c++11
CPPFLAGS = -Wall -Wno-uninitialized
all: testbst

intbst.o: intbst.cpp
	$(CPP) $(CPPFLAGS) $^ -c

testbst.o: testbst.cpp
	$(CPP) $(CPPFLAGS) $^ -c

testbst: testbst.o intbst.o
	$(CPP) $(CPPFLAGS) $^ -o $@
