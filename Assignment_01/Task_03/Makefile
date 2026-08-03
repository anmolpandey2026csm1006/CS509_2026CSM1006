# Compiler settings
CXX = g++
CXXFLAGS = -Wall -O2

# Directories
DRIVER_DIR = driver
SRC_DIR = source
TEST_DIR = test
OUT_DIR = output

# Executable name
TARGET = $(DRIVER_DIR)/csr_app

# Default target
all: $(TARGET)

# Compile the executable
$(TARGET): $(DRIVER_DIR)/csrMain.cpp $(SRC_DIR)/csr.cpp
	$(CXX) $(CXXFLAGS) $(DRIVER_DIR)/csrMain.cpp $(SRC_DIR)/csr.cpp -o $(TARGET)

# Run Test 01
run1: $(TARGET)
	./$(TARGET) $(TEST_DIR)/test_01.txt $(OUT_DIR)/output_01.txt
	@echo "Test 1 finished! Check $(OUT_DIR)/output_01.txt for results."

# Run Test 02
run2: $(TARGET)
	./$(TARGET) $(TEST_DIR)/test_02.txt $(OUT_DIR)/output_02.txt
	@echo "Test 2 finished! Check $(OUT_DIR)/output_02.txt for results."

# Run all tests
run-all: run1 run2

# Clean
clean:
	rm -f $(TARGET)