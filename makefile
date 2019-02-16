lib4console:main.cpp inside.cpp os.h
	g++ main.cpp -o lib4console -L./libcore -llibcore
	g++ inside.cpp -o inside
debug:main.cpp inside.cpp os.h
	g++ main.cpp -o lib4console -L./libcore -llibcore -g
	g++ inside.cpp -o inside -g
clean:
	rm lib4console inside
windows:main.cpp inside.cpp os.h
	cl main.cpp libcore/libcore.lib /Felib4console /DWIN_OS /EHsc
	cl inside.cpp /EHsc