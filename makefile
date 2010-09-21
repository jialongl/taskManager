all : taskManager

taskManager : main.cpp
	g++ -o taskManager main.cpp

clean:
	rm taskManager
