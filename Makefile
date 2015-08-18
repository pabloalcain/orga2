SUBDIRS := $(wildcard clase*/.)

.PHONY: default $(SUBDIRS)

default: $(SUBDIRS)

$(SUBDIRS): 
	$(MAKE) -C $@
	
