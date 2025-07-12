CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O2

SRC_DIR := src
BIN_DIR := bin

ifeq ($(OS),Windows_NT)
	EXECUTABLE := CalcuMood.exe
	RM := del /Q
	MKDIR := if not exist $(BIN_DIR) mkdir $(BIN_DIR)
else
	EXECUTABLE := CalcuMood
	RM := rm -f
	MKDIR := mkdir -p $(BIN_DIR)
endif

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(BIN_DIR)/$(EXECUTABLE)

$(BIN_DIR)/$(EXECUTABLE): $(SRCS)
	@echo "Building CalcuMood..."
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(EXECUTABLE) $(SRCS)

clean:
	@echo "Cleaning up..."
	$(RM) $(BIN_DIR)/$(EXECUTABLE)

run: all
	@echo "Running CalcuMood..."
	@./$(BIN_DIR)/$(EXECUTABLE)

.PHONY: all clean run
