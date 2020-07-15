CXXFLAGS ?= -std=c++17

rot13_main: main.o librot13.a
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^

librot13.a: rot13.o
	ar rcs $@ $^

rot13.cc: rot13.h

.PHONY: clean
clean:
	rm -f *.o *.a rot13_main
