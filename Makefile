build/%: %
	cd $<; opp_makemake -f --deep
	cd $<; make clean
	cd $<; make MODE=release all

run/%: % build/%
	cd $</simulations; ../$< -n .:../src

clean/%: %
	cd $</; make clean
