#================================================================================
# Makefile used for building and running unit tests.
#
#    Generate list of targets based on files in unittests directory.
#    Rules to build these targets will then need to be manually added.
#    Once the list of targets has a matching set of rules the Makefile handles
#    the building and running of unit tests as well as any post-test cleanup.
#    This makefile is invoked from the makefile in the project root directory
#    when given the command "make test".
#================================================================================

#================================================================================
# Project & toolchain configurations.
#================================================================================
SRC_DIR = src
INC_DIR = inc
UNITY_SRC := Unity/src/unity.c
UNITY_INC := Unity/src
UNIT_TEST_DIR := unittests
UNIT_TEST_BUILD_DIR := $(UNIT_TEST_DIR)/build
UNIT_TEST_CC := gcc
UNIT_TEST_INC := -I$(UNITY_INC) -I$(INC_DIR)
UNIT_TEST_TARGETS := $(patsubst $(UNIT_TEST_DIR)/%.c,$(UNIT_TEST_BUILD_DIR)/%.exe,$(wildcard $(UNIT_TEST_DIR)/*.c))
TESTRUNNER_ARGS := >> test_results.txt 2>&1 || true

#================================================================================
# Rule used for running unit tests.
#    Accumulate test results from stdout & stderr into test_result.txt,
#    present the results by running the test_result_parser.py script.
#    Perform post-test cleanup.
#================================================================================
.PHONY: run_tests
run_tests: build_tests
	@echo "Running unit tests..."
	@$(UNIT_TEST_BUILD_DIR)/test_lrc.exe $(TESTRUNNER_ARGS)
	@$(UNIT_TEST_BUILD_DIR)/test_fifo.exe $(TESTRUNNER_ARGS)
	@$(UNIT_TEST_BUILD_DIR)/test_fsm.exe $(TESTRUNNER_ARGS)
	@python scripts/test_result_parser.py test_results.txt
	@rm -rf $(UNIT_TEST_BUILD_DIR)/*.exe
	@rm test_results.txt

#================================================================================
# Rule to build all defined targets.
#================================================================================
.PHONY: build_tests
build_tests: $(UNIT_TEST_TARGETS)
	@echo "Building target tests..."

#================================================================================
# Rule to build testrunner for test_lrc.
#================================================================================
$(UNIT_TEST_BUILD_DIR)/test_lrc.exe: $(UNIT_TEST_DIR)/test_lrc.c $(SRC_DIR)/lrc.c $(UNITY_SRC)
	@$(UNIT_TEST_CC) $(UNIT_TEST_INC) $^ -o $@

#================================================================================
# Rule to build testrunner for test_fifo.
#================================================================================
$(UNIT_TEST_BUILD_DIR)/test_fifo.exe: $(UNIT_TEST_DIR)/test_fifo.c $(SRC_DIR)/fifo.c $(UNITY_SRC)
	@$(UNIT_TEST_CC) $(UNIT_TEST_INC) $^ -o $@

#================================================================================
# Rule to build testrunner for test_fsm.
#================================================================================
$(UNIT_TEST_BUILD_DIR)/test_fsm.exe: $(UNIT_TEST_DIR)/test_fsm.c $(SRC_DIR)/fsm.c $(UNITY_SRC)
	@$(UNIT_TEST_CC) $(UNIT_TEST_INC) $^ -o $@