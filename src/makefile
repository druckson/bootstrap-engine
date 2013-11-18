SOURCE = test.cpp Entity.cpp

FLAGS = -std=c++11
LIBS = -L /usr/lib -lGLEW -lGL -lGLU -lglfw -lboost_system -lboost_thread
INCLUDES = -I /usr/include

build: test

../build:
	mkdir ../build/

test: test.cpp ../build/
	g++ $(FLAGS) $(LIBS) $(INCLUDES) -o ../build/test test.cpp

clean:
	rm ../build/test
