
RM = rm -rf

CXX_FLAGS += -std=c++11

PROGRAMS += \
			numeric-limits \
			variadic-template \
			template-constructor \
			lambda-vs-functor

.PHONY: all
all: $(PROGRAMS)

numeric-limits: numeric-limits.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

variadic-template: variadic-template.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

template-constructor: template-constructor.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

lambda-vs-functor: lambda-vs-functor.cpp
	$(CXX) -o $@ $< $(CXX_FLAGS)

clean:
	$(RM) *.o $(PROGRAMS)
