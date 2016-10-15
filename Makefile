
.PHONY: all release clean shared
export CBOX_MAIN_DIR=/home/kiennt/share/vnexpress_dev
all:
	$(MAKE) -C . -f Makefile.app
clean:
	$(MAKE) -C $(CBOX_MAIN_DIR) -f Makefile.app clean
