
RM = rm -rf

BUILD_DIR = ./build

CXX_FLAGS += -std=c++11

PROGRAMS += \
			numeric-limits \
			variadic-template \
			template-constructor \
			lambda-vs-functor

.PHONY: all
all: make_build_dir $(PROGRAMS)

make_build_dir:
	@mkdir -p $(BUILD_DIR)

numeric-limits: numeric-limits.cpp
	$(CXX) -o $(BUILD_DIR)/$@ $< $(CXX_FLAGS)

variadic-template: variadic-template.cpp
	$(CXX) -o $(BUILD_DIR)/$@ $< $(CXX_FLAGS)

template-constructor: template-constructor.cpp
	$(CXX) -o $(BUILD_DIR)/$@ $< $(CXX_FLAGS)

lambda-vs-functor: lambda-vs-functor.cpp
	$(CXX) -o $(BUILD_DIR)/$@ $< $(CXX_FLAGS)

clean:
	$(RM) $(BUILD_DIR)
