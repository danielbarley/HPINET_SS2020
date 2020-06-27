build/%: %
	cd $</src; opp_makemake -f --deep
	cd $</src; make clean
	cd $</src; make MODE=release all

run/%: % build/%
	rm $</simulations/results/* -f
	cd $</simulations; ../src/$< -n .:../src

clean/%: %
	cd $</; make clean
