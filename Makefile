# Makefile for compiling the PYTHIA8 example program

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -pedantic -Wshadow -fPIC -pthread

# PYTHIA8 settings
PYTHIA8_DIR = /mnt/e/LBT-jet/pythia8307
PYTHIA8_INC = $(PYTHIA8_DIR)/include
PYTHIA8_LIB = $(PYTHIA8_DIR)/lib -lpythia8

# Executable name
TARGET = run_pythia

# Source file
SRC = run_pythia.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -I$(PYTHIA8_INC) -L$(PYTHIA8_LIB)

clean:
	rm -f $(TARGET)
