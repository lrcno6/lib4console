lib4console:main.cpp
	g++ main.cpp -o lib4console -L./libcore -llibcore -Ofast
debug:main.cpp
	g++ main.cpp -o lib4console -L./libcore -llibcore -g
clean:
	rm lib4console
windows:main.cpp
	cl main.cpp libcore/libcore.lib /Felib4console /DWIN_OS /EHsc