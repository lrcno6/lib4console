lib4console:main.cpp
	g++ main.cpp -o lib4console -L./libcore -llibcore
debug:main.cpp
	g++ main.cpp -o lib4console -L./libcore -llibcore -g
clean:
	rm lib4console