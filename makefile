run.exe : *.o
	g++ *.o -o run -LC:/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
	del *.o

*.o : *.cpp
	g++ -c *.cpp -IC:/SFML-2.5.1/include