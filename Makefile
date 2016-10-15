include buildFlag.env
.PHONY: all release clean shared

all:
	$(MAKE) -C . -f Makefile.app
clean:
	$(MAKE) -C $(CBOX_MAIN_DIR) -f Makefile.app clean
