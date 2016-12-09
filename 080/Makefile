CXX = g++
CXXFLAGS = -std=c++14 -Wall -O3
LINKER = $(CXX)
LDFLAGS = 

TARGET = ./80
SOURCES = 80.cc $(wildcard **/*.cc)
OBJECTS = $(SOURCES:.cc=.o)

DEPS = $(OBJECTS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINKER) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(CXXINCL) $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) $(DEPS)

-include $(DEPS)