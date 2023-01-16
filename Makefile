MAKE := mingw32-make
CD := cd

.PHONY: build
build:
	$(CD) UCM && $(MAKE) build
	$(CD) UVM && $(MAKE) build
	@echo " build done!"

.PHONY: clean
clean:
	$(CD) UCM && $(MAKE) clean
	$(CD) UVM && $(MAKE) clean
	@echo " clean done!"