#================================================================================
# Build & run unit tests for module fifo.c
#================================================================================
SRC_DIR = src
INC_DIR = inc

UNITY_SRC_DIR := Unity/src
UT_DIR := unittests
UT_BUILD_DIR := $(UT_DIR)/build
UT_CC := gcc
UT_INC := -I$(UNITY_SRC_DIR) -I$(INC_DIR)

TEST_SRC_FILES := $(UT_DIR)/test_fifo.c $(SRC_DIR)/fifo.c $(UNITY_SRC_DIR)/unity.c

.PHONY: test_fifo
test_fifo: $(UT_BUILD_DIR)/run_test_fifo.exe
	@$(UT_BUILD_DIR)/run_test_fifo
	@rm -rf $(UT_BUILD_DIR)/*.exe

$(UT_BUILD_DIR)/run_test_fifo.exe: $(TEST_SRC_FILES)
	@$(UT_CC) $^ $(UT_INC) -o $@