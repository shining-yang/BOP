# Makefile to build C++ programs which demostrate new features in C++11

RM = rm -rf
BUILD_DIR = build
CXX_FLAGS += -std=c++11
SOURCES = $(wildcard *.cpp)
PROGRAMS = $(addprefix $(BUILD_DIR)/, $(basename $(SOURCES)))

.PHONY: all
all: make_build_dir $(PROGRAMS)

.PHONY: make_build_dir
make_build_dir:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/numeric-limits: numeric-limits.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

$(BUILD_DIR)/variadic-template: variadic-template.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

$(BUILD_DIR)/template-constructor: template-constructor.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

$(BUILD_DIR)/lambda-vs-functor: lambda-vs-functor.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

$(BUILD_DIR)/utility-pair: utility-pair.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

$(BUILD_DIR)/utility-tuple: utility-tuple.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)
