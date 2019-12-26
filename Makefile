COMPILER = g++

PROGRAM = WebServer

SRC_DIR = src
BIN_DIR = bin
DEBUG_DIR = $(BIN_DIR)/debug
RELEASE_DIR = $(BIN_DIR)/release
WEB_CONTENT_DEBUG = $(DEBUG_DIR)/WebContent
WEB_CONTENT_RELEASE = $(RELEASE_DIR)/WebContent
TEMPLATE_DIR = templates

release:
	$(COMPILER) $(SRC_DIR)/* -o $(RELEASE_DIR)/$(PROGRAM)

debug:
	$(COMPILER) -g $(SRC_DIR)/* -o $(DEBUG_DIR)/$(PROGRAM)

init:
	mkdir $(BIN_DIR) $(DEBUG_DIR) $(RELEASE_DIR) $(WEB_CONTENT_RELEASE) $(WEB_CONTENT_DEBUG)
	cp -r $(TEMPLATE_DIR) $(DEBUG_DIR)
	cp -r $(TEMPLATE_DIR) $(RELEASE_DIR)

clean:
	rm -rf $(BIN_DIR)
