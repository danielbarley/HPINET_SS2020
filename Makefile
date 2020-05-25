build/%: %
	cd $<; opp_makemake -f --deep
	cd $</src; make clean
	cd $</src; make MODE=release all

run/%: % build/%
	cd $</simulations; ../src/$< -n .:../src

clean/%: %
	cd $</; make clean
