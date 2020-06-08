build/%: %
	cd $</src; opp_makemake -f --deep
	cd $</src; make clean
	cd $</src; make MODE=release all

run/%: % build/%
	cd $</simulations; ../$< -n .:../src

clean/%: %
	cd $</; make clean
