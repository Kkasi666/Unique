CPPC := g++ # you also can use 'gcc' or 'clang++'.
MKDIR := mkdir
DELFILES := del # if use 'del' couldn't pass, you can try using 'rm'.

CPP_INCLUDE := -I"./include/"
CPP_SOURCE  := fileOperate bytePrjLoader byteCode executer main

BUILDDIR := ./build
SRCDIR   := ./src

OBJECTS := $(foreach src, $(CPP_SOURCE), $(BUILDDIR)/$(src).o)
OUTPUT  := $(BUILDDIR)/que

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	-$(MKDIR) build
	$(CPPC) $(CPP_INCLUDE) -c -o $@ $^

$(OUTPUT): $(OBJECTS)
	-$(MKDIR) build
	$(CPPC) -o $@ $(OBJECTS) -static-libstdc++

# .PHONY: build
# build: $(OUTPUT)
# @echo "done!"

.PHONY: clean
clean:
	cd build && \
	$(DELFILES) $(foreach src, $(CPP_SOURCE), $(src).o) && \
	cd ../