BUILD_DIR = build
SRC_DIR = src
HEADER_DIR = h
OBJ_DIR = $(BUILD_DIR)/obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

OUTPUT = $(BUILD_DIR)/output

all : $(OUTPUT) | $(BUILD_DIR) $(OBJ_DIR)

$(OUTPUT): $(OBJ_FILES) | $(BUILD_DIR) $(OBJ_DIR)
	g++ $(OBJ_FILES) -o $(OUTPUT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR) $(OBJ_DIR)
	g++ -c -o $@ $< 

$(OBJ_DIR): | $(BUILD_DIR)
	mkdir $(@)

$(BUILD_DIR): 
	mkdir $(@)

clean : 
	rm -rf $(BUILD_DIR)
