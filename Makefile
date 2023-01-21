CC = g++
CFLAGS = -std=c++11 -pthread

SOURCES_CLIENT = Client2.0.cpp Validation.cpp SocketIO.cpp
SOURCES_SERVER = Server2.0.cpp Validation.cpp DistanceCalc.cpp KnnCalc.cpp CLI.cpp CommandOne.cpp CommandTwo.cpp CommandThree.cpp CommandFour.cpp CommandFive.cpp CommandEight.cpp SocketIO.cpp


OBJECTS_CLIENT = $(SOURCES_CLIENT:.cpp=.o)
OBJECTS_SERVER = $(SOURCES_SERVER:.cpp=.o)


EXECUTABLE_CLIENT = client.out
EXECUTABLE_SERVER = server.out

all: $(EXECUTABLE_CLIENT) $(EXECUTABLE_SERVER)

$(EXECUTABLE_CLIENT): $(OBJECTS_CLIENT) $(OBJECTS_KNN) $(OBJECTS_DISTANCES)
	$(CC) $(OBJECTS_CLIENT)  -o $(EXECUTABLE_CLIENT) $(CFLAGS)

$(EXECUTABLE_SERVER): $(OBJECTS_SERVER) $(OBJECTS_KNN) $(OBJECTS_DISTANCES)
	$(CC) $(OBJECTS_SERVER) -o $(EXECUTABLE_SERVER) $(CFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o *.out
