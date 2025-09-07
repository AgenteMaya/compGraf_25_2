CXX = g++
CXXFLAGS = -Wall -I.
LIBS = $(shell pkg-config --cflags --libs glfw3) -ldl

TARGET = exec
SRC = test0-glfw.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

run: $(TARGET)
	./$(TARGET)

nv: $(TARGET)
	prime-run ./$(TARGET)

clean:
	rm -f $(TARGET)
