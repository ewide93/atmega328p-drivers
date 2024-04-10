#================================================================================
# Build & run unit tests for module lrc.c
#================================================================================
SRC_DIR = src
INC_DIR = inc

UNITY_SRC_DIR := Unity/src
UT_DIR := unittests
UT_BUILD_DIR := $(UT_DIR)/build
UT_CC := gcc
UT_INC := -I$(UNITY_SRC_DIR) -I$(INC_DIR)

TEST_SRC_FILES := $(UT_DIR)/test_lrc.c $(SRC_DIR)/lrc.c $(UNITY_SRC_DIR)/unity.c

.PHONY: test_lrc
test_lrc: $(UT_BUILD_DIR)/run_test_lrc.exe
	@$(UT_BUILD_DIR)/run_test_lrc
	@rm -rf $(UT_BUILD_DIR)/*.exe

$(UT_BUILD_DIR)/run_test_lrc.exe: $(TEST_SRC_FILES)
	@$(UT_CC) $^ $(UT_INC) -o $@