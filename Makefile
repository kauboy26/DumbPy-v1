CXXFLAGS= -std=c++14 -O2 -W -Wall -Wextra -pedantic
OBJFILES= dumbpy.m.o tokenizer.o parser.o runner.o

dumbpy: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES) dumbpy

.PHONY: clean
