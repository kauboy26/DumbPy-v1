CXXFLAGS= -std=c++14 -O2 -W -Wall -Wextra -pedantic
OBJFILES= dumbpy.m.o tokenizer.o

dumbpy: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES) lab1

.PHONY: clean
