CXX = g++
CXXFLAGS = -std=c++17 -g

SRC_DIR = src
PREPROCESSOR_DIR = $(SRC_DIR)/Preprocessor

SOURCES = $(SRC_DIR)/assembler.cc $(PREPROCESSOR_DIR)/preprocessor.cc
OBJECTS = assembler.o preprocessor.o
EXECUTABLE = my_assembler

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: $(PREPROCESSOR_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) a.out
