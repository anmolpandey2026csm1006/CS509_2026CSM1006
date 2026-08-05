# Compiler settings
CXX = g++
CXXFLAGS = -Wall -O2

# Directories
DRIVER_DIR = driver
SRC_DIR = source
TEST_DIR = test
OUT_DIR = output

# Executable name
TARGET = $(DRIVER_DIR)/block_app

# Default target: compile the code
all: $(TARGET)

# Rule to compile the executable
$(TARGET): $(DRIVER_DIR)/blockingMain.cpp $(SRC_DIR)/blockMatrix.cpp
	$(CXX) $(CXXFLAGS) $(DRIVER_DIR)/blockingMain.cpp $(SRC_DIR)/blockMatrix.cpp -o $(TARGET)

# Run Test 01
run1: $(TARGET)
	./$(TARGET) $(TEST_DIR)/test_01.txt $(OUT_DIR)/output_01.txt
	@echo "Test 1 finished! Check $(OUT_DIR)/output_01.txt for results."

# Run Test 02
run2: $(TARGET)
	./$(TARGET) $(TEST_DIR)/test_02.txt $(OUT_DIR)/output_02.txt
	@echo "Test 2 finished! Check $(OUT_DIR)/output_02.txt for results."

# Run Test 03
run3: $(TARGET)
	./$(TARGET) $(TEST_DIR)/test_03.txt $(OUT_DIR)/output_03.txt
	@echo "Test 3 finished! Check $(OUT_DIR)/output_03.txt for results."

# Run Test 04
run4: $(TARGET)
	./$(TARGET) $(TEST_DIR)/test_250x250x250.txt $(OUT_DIR)/output_04.txt
	@echo "Test 4 finished! Check $(OUT_DIR)/output_04.txt for results."

# Run Test 05
run5: $(TARGET)
	./$(TARGET) $(TEST_DIR)/test_1000x1000x1000.txt $(OUT_DIR)/output_05.txt
	@echo "Test 5 finished! Check $(OUT_DIR)/output_05.txt for results."

# Run all tests sequentially
run-all: run1 run2 run3 run4 run5

# Clean up compiled files
clean:
	rm -f $(TARGET)