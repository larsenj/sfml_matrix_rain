CC = g++
CFLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system 
OBJECTS = rain.o

rain: $(OBJECTS)
	$(CC) $(OBJECTS) -o rain $(CFLAGS)	

%.o: %.cpp
	$(CC) -std=c++0x -c $<

clean:
	rm *.o rain

#target: dependencies
#	system command
