CPPC := g++
MKDIR := mkdir

CPP_INCLUDE := -I"./include/"
CPP_SOURCE  := lexer ASTNode parser main

BUILDDIR := ./build
SRCDIR   := ./src

OBJECTS := $(foreach src, $(CPP_SOURCE), $(BUILDDIR)/$(src).o)

OUTPUT  := $(BUILDDIR)/main

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	-$(MKDIR) build
	$(CPPC) $(CPP_INCLUDE) -c -o $@ $^

$(OUTPUT): $(OBJECTS)
	-$(MKDIR) build
	$(CPPC) -o $@ $(OBJECTS)

.PHONY: build
build: $(OUTPUT)
	@echo "done!"

.PHONY: clean
clean:
	-rm $(OBJECTS)