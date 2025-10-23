# ./Makefile

CXX       := g++
CC        := gcc
CXXFLAGS  := -g -Wall -std=c++17
CFLAGS    := -g -Wall
SRCDIR    := src
EXTDIR    := external
BUILDDIR  := build
TARGET    := exec

INCLUDES   := -I. -I$(EXTDIR)/include -I$(SRCDIR)
PKG_CFLAGS := $(shell pkg-config --cflags glfw3)
PKG_LIBS   := $(shell pkg-config --libs glfw3)
CXXFLAGS  += $(PKG_CFLAGS)
CFLAGS    += $(PKG_CFLAGS)
LDLIBS     := $(PKG_LIBS) -lGL -ldl

# Fontes: ajuste conforme seu projeto
SOURCES := \
	$(EXTDIR)/glad.c \
	$(wildcard $(SRCDIR)/*.cpp)

# build/external/glad.o, build/src/foo.o, ...
OBJECTS := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(patsubst %.c,$(BUILDDIR)/%.o,$(SOURCES)))

.PHONY: all clean run nv
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDLIBS)

# C++ -> .o
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# C -> .o
$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)  
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

nv: $(TARGET)
	prime-run ./$(TARGET)

clean:
	$(RM) -r $(BUILDDIR) $(TARGET)
