CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = dijkstra

all: $(TARGET)

$(TARGET): dijkstra.cpp
    $(CXX) $(CXXFLAGS) -o $(TARGET) dijkstra.cpp

clean:
    rm -f $(TARGET)

help:
	@echo "make            : compila"
	@echo "make clean      : remove binários"

.PHONY: all clean help




# CXX = g++
# CXXFLAGS = -std=c++17 -O2 -Wall

# TARGET = prim

# all: $(TARGET)

# $(TARGET): prim.cpp
# 	$(CXX) $(CXXFLAGS) -o $@ $<

# clean:
# 	rm -f $(TARGET)

# help:
# 	@echo "make            : compila"
# 	@echo "make clean      : remove binários"

# .PHONY: all clean help
