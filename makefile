CC = clang
BUILD_DIR = target
INSTALL_DIR = /usr/local/bin

all: test coverage analyze compile

compile:
	@echo "###################"
	@echo "#### Compiling ####"
	@echo "###################"
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/wtl wtl.c
	@echo "\xe2\x9c\x85"

test:
	@echo "###################"
	@echo "####  Testing   ###"
	@echo "###################"
	mkdir -p $(BUILD_DIR)/test
	rm -rf $(BUILD_DIR)/test/*
	rm -f ./*.gcda ./*.gcno ./*.gcov
	GCOV_PREFIX=$(BUILD_DIR)/test; $(CC) --coverage -g -O0 \
		-o $(BUILD_DIR)/test/wtl-test \
		-DTEST=1 test.c wtl.c config.c timeformat.c lib/munit/munit.c
	./$(BUILD_DIR)/test/wtl-test --show-stderr

coverage:
	@echo "###################"
	@echo "####  Coverage  ###"
	@echo "###################"
	gcov -f ./*.c | ./coverage.sh

analyze:
	@echo "###################"
	@echo "#### Analyzing ####"
	@echo "###################"
	rm -rf $(BUILD_DIR)/report
	mkdir -p $(BUILD_DIR)/report
	$(CC) --analyze --analyzer-output html -o $(BUILD_DIR)/report wtl.c
	@echo "\xe2\x9c\x85"

install: compile
	@echo "###################"
	@echo "#### Installing ###"
	@echo "###################"
	cp $(BUILD_DIR)/wtl $(INSTALL_DIR)/wtl
	@echo "[INFO] Installed to $(INSTALL_DIR)/wtl"
	@echo "[INFO] Configure ~/.wtl to let it automatically tell you when to leave"
	@echo "[INFO] See https://github.com/jazzschmidt/wtl/blob/master/README.md"
	@echo "\xe2\x9c\x85"

uninstall:
	@echo "######################"
	@echo "#### Uninstalling ####"
	@echo "######################"
	rm -f $(INSTALL_DIR)/wtl
	@echo "\xe2\x9c\x85"

clean:
	rm -rf $(BUILD_DIR)
	rm -f ./*.gcda ./*.gcno
