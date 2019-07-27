TARGET := test

SRC := $(wildcard *.cpp)

OBJ := $(notdir $(SRC))
OBJ := $(OBJ:.cpp=.o)
OBJ := $(addprefix objects/, $(OBJ))

CXX      := g++
CXXFLAGS := -std=c++17
LDFLAGS  :=

build: objects $(TARGET)
	@echo "Build success"

objects:
	mkdir objects

$(TARGET): $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

objects/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run buildrun clean
buildrun: $(TARGET)
	-./$(TARGET)
run:
	-./$(TARGET)
clean:
	-rm -rf $(OBJ)
