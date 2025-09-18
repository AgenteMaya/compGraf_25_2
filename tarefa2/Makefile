#$(TARGET): $(OBJ) Makefile 
#	$(CPP) $(LIB) -o $@ $(OBJ) -lstdc++ -framework OpenGL -lglfw -lassimp

CXX = g++
CXXFLAGS = -g -Wall
INC = -I. -Iexternal/include
PKG = $(shell pkg-config --cflags --libs glfw3)
LDLIBS = $(PKG) -ldl

TARGET = exec2

SRC = \
  external/glad.cpp \
  error.cpp \
  shader.cpp \
  triangle.cpp \
  circle.cpp \
  main.cpp

#OBJ = $(addsuffix .o, $(basename $(SRC))) 
OBJ = $(patsubst %.cpp, build/%.o, $(patsubst %.c, build/%.o, $(SRC)))

#all: $(TARGET)
all: build $(TARGET)

build:
	mkdir -p build/external

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

build/%.o: %.c
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

nv: $(TARGET)
	prime-run ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

