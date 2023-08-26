APP_NAME = testapp
OUTPUT_DIR = out

CXX ?= g++
CXXFLAGS ?= -std=c++17

SRCS = $(wildcard *.cpp)
OBJS = $(addprefix $(OUTPUT_DIR)/, $(notdir $(SRCS:.cpp=.o)))

INCLUDE = -I ../include/ -I.

clean: 
	rm -rf out/*

all: $(OUTPUT_DIR)/$(APP_NAME)

$(OUTPUT_DIR)/$(APP_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OUTPUT_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

run:
	./$(OUTPUT_DIR)/$(APP_NAME)