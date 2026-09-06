CXX = g++
CXXFLAGS = -Wall -O2

DRIVER_DIR = driver
SRC_DIR = source
TEST_DIR = test
OUT_DIR = output

CSR_DIR = ../../Assignment_01/Task_03/source

TARGET = $(DRIVER_DIR)/pagerank_app

all: $(TARGET)

$(TARGET): $(DRIVER_DIR)/pageRankMain.cpp $(SRC_DIR)/pageRank.cpp $(CSR_DIR)/csr.cpp
	$(CXX) $(CXXFLAGS) $(DRIVER_DIR)/pageRankMain.cpp $(SRC_DIR)/pageRank.cpp $(CSR_DIR)/csr.cpp -o $(TARGET)

# Spec example (section 6.2)
run-example: $(TARGET)
	./$(TARGET) $(TEST_DIR)/pagerank_example.txt $(OUT_DIR)/output_example.txt
	@echo "Example test finished! Check $(OUT_DIR)/output_example.txt for results."

# Required sizes (section 4.2): 10, 100, 1000, 10000, 50000
run1: $(TARGET)
	./$(TARGET) $(TEST_DIR)/pagerank_10.txt $(OUT_DIR)/output_01.txt
	@echo "Test 1 (V=10) finished! Check $(OUT_DIR)/output_01.txt for results."

run2: $(TARGET)
	./$(TARGET) $(TEST_DIR)/pagerank_100.txt $(OUT_DIR)/output_02.txt
	@echo "Test 2 (V=100) finished! Check $(OUT_DIR)/output_02.txt for results."

run3: $(TARGET)
	./$(TARGET) $(TEST_DIR)/pagerank_1000.txt $(OUT_DIR)/output_03.txt
	@echo "Test 3 (V=1000) finished! Check $(OUT_DIR)/output_03.txt for results."

run4: $(TARGET)
	./$(TARGET) $(TEST_DIR)/pagerank_10000.txt $(OUT_DIR)/output_04.txt
	@echo "Test 4 (V=10000) finished! Check $(OUT_DIR)/output_04.txt for results."

run5: $(TARGET)
	./$(TARGET) $(TEST_DIR)/pagerank_50000.txt $(OUT_DIR)/output_05.txt
	@echo "Test 5 (V=50000) finished! Check $(OUT_DIR)/output_05.txt for results."

# Optional per spec (100,000 vertices; failure is acceptable and should be documented)
run6: $(TARGET)
	./$(TARGET) $(TEST_DIR)/pagerank_100000.txt $(OUT_DIR)/output_06.txt
	@echo "Test 6 (V=100000, optional) finished! Check $(OUT_DIR)/output_06.txt for results."

run-all: run-example run1 run2 run3 run4 run5

clean:
	rm -f $(TARGET)
