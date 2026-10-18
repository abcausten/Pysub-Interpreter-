CXX      ?= clang++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -g
TARGET   = pysub

$(TARGET): src/Main.cpp src/interface.h src/lexanalyzer.h src/expevaluator.h
	$(CXX) $(CXXFLAGS) src/Main.cpp -o $(TARGET)

debug: src/Main.cpp src/interface.h src/lexanalyzer.h src/expevaluator.h
	$(CXX) $(CXXFLAGS) -fsanitize=address,undefined src/Main.cpp -o $(TARGET)_debug

clean:
	rm -f $(TARGET) $(TARGET)_debug

.PHONY: debug clean
