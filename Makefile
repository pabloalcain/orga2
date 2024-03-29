SUBDIRS := $(wildcard clase*/.) $(wildcard tp*/.)
SUBCLEAN := $(addsuffix .clean,$(SUBDIRS))

.PHONY: default clean $(SUBDIRS) $(SUBCLEAN)

default: $(SUBDIRS)

clean: $(SUBCLEAN)

$(SUBDIRS): 
	$(MAKE) -C $@

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
