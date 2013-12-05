SOURCE = test.cpp Entity.cpp ../build/graphics.o

FLAGS = -std=c++11
LIBS = -L /usr/lib -lGLEW -lGL -lGLU -lglfw -lboost_system -lboost_thread
INCLUDES = -I /usr/include

all: ../build/test
	rm ../build/*.o

../build/:
	mkdir ../build/

../build/assets/: ../build/
	rm -rf ../build/assets/
	cp -r ./assets/ ../build/assets/

../build/graphics.o: systems/Graphics.h systems/Graphics.cpp
	g++ $(FLAGS) $(LIBS) $(INCLUDES) -c -o ../build/graphics.o systems/Graphics.cpp

../build/test: test.cpp ../build/graphics.o ../build/assets/
	g++ $(FLAGS) $(LIBS) $(INCLUDES) -o ../build/test test.cpp ../build/graphics.o

clean:
	rm -rf ../build
