SOURCE = test.cpp Entity.cpp

build: test

../build:
	mkdir ../build/

test: test.cpp ../build/
	g++ -std=c++11 -lboost_system -lboost_thread -lglfw -o ../build/test test.cpp

clean:
	rm ../build/test
