all:
	$(MAKE) -C libtl
	$(MAKE) -C tlbones
	$(MAKE) -C tli

clean:
	$(MAKE) clean -C libtl
	$(MAKE) clean -C tlbones
	$(MAKE) clean -C tli
