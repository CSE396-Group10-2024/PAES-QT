# Paths
SRC_DIR_SHAPE = PAES-QT-SRC/shapeDetect
BUILD_DIR_SHAPE = PAES-QT-SRC/shapeDetect/build
EXECUTABLE_NAME_SHAPE = detect_shapes

SRC_DIR_ONNX = PAES-QT-SRC/onnx_pose
BUILD_DIR_ONNX = PAES-QT-SRC/onnx_pose/build
EXECUTABLE_NAME_ONNX = pose_generator

SRC_DIR_QT = PAES-QT-SRC
PRO_FILE = PAES.pro
EXECUTABLE_NAME_QT = PAES

INSTALL_DIR = PAES-QT-SRC

# Default target
all: clean_qt build_shape build_onnx build_qt move_executables

# Pre-clean target
clean_qt:
	$(MAKE) -C $(SRC_DIR_QT) clean

# Build targets
build_shape:
	mkdir -p $(BUILD_DIR_SHAPE)
	cmake -S $(SRC_DIR_SHAPE) -B $(BUILD_DIR_SHAPE)
	$(MAKE) -C $(BUILD_DIR_SHAPE)

build_onnx:
	mkdir -p $(BUILD_DIR_ONNX)
	cd $(BUILD_DIR_ONNX) && cmake ..
	$(MAKE) -C $(BUILD_DIR_ONNX)

build_qt:
	cd $(SRC_DIR_QT) && qmake6 $(PRO_FILE)
	$(MAKE) -C $(SRC_DIR_QT)

# Move the executables to the PAES-QT-SRC folder
move_executables: build_shape build_onnx build_qt
	mv $(BUILD_DIR_SHAPE)/$(EXECUTABLE_NAME_SHAPE) $(INSTALL_DIR)/$(EXECUTABLE_NAME_SHAPE)
	#mv $(BUILD_DIR_ONNX)/$(EXECUTABLE_NAME_ONNX) $(INSTALL_DIR)/$(EXECUTABLE_NAME_ONNX)
	#mv $(SRC_DIR_QT)/$(EXECUTABLE_NAME_QT) $(INSTALL_DIR)/$(EXECUTABLE_NAME_QT)

# Clean targets
clean:
	$(MAKE) -C $(BUILD_DIR_SHAPE) clean
	rm -rf $(BUILD_DIR_SHAPE)
	$(MAKE) -C $(BUILD_DIR_ONNX) clean
	rm -rf $(BUILD_DIR_ONNX)
	$(MAKE) -C $(SRC_DIR_QT) clean

# Install target (assumes CMake install path is set to INSTALL_DIR)
install: move_executables
	$(MAKE) -C $(BUILD_DIR_SHAPE) install DESTDIR=$(INSTALL_DIR)
	$(MAKE) -C $(BUILD_DIR_ONNX) install DESTDIR=$(INSTALL_DIR)
	$(MAKE) -C $(SRC_DIR_QT) install DESTDIR=$(INSTALL_DIR)

# Run the executable
run: move_executables
	./$(INSTALL_DIR)/$(EXECUTABLE_NAME_QT)

.PHONY: all clean_qt build_shape build_onnx build_qt clean install move_executables run




