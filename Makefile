MAKE := mingw32-make
CD := cd

.PHONY: build
build:
	$(CD) UCM && $(MAKE) build
	$(CD) UVM && $(MAKE) build
	@echo " main done!"