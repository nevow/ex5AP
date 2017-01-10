all: server.out client.out

server.out: server.o Map.o Node.o Point.o TripEndListener.o SetTripListener.o BFS.o DataSender.o MainFlow.o ProperInput.o SystemOperations.o Socket.o Udp.o Cab.o LuxuryCab.o Driver.o Passenger.o Satisfaction.o TaxiCenter.o TripInfo.o
	g++ -o server.out -std=c++0x server.o Map.o Node.o Point.o TripEndListener.o SetTripListener.o BFS.o DataSender.o MainFlow.o ProperInput.o SystemOperations.o Socket.o Udp.o Cab.o LuxuryCab.o Driver.o Passenger.o Satisfaction.o TaxiCenter.o TripInfo.o -lboost_serialization

client.out: client.o Map.o Node.o Point.o TripEndListener.o SetTripListener.o BFS.o DataSender.o MainFlow.o ProperInput.o SystemOperations.o Socket.o Udp.o Cab.o LuxuryCab.o Driver.o Passenger.o Satisfaction.o TaxiCenter.o TripInfo.o
	g++ -o client.out -std=c++0x client.o Map.o Node.o Point.o TripEndListener.o SetTripListener.o BFS.o DataSender.o MainFlow.o ProperInput.o SystemOperations.o Socket.o Udp.o Cab.o LuxuryCab.o Driver.o Passenger.o Satisfaction.o TaxiCenter.o TripInfo.o -lboost_serialization

client.o: src/client/client.cpp
	g++ -std=c++0x -c src/client/client.cpp

server.o: src/server/server.cpp
	g++ -std=c++0x -c src/server/server.cpp

Map.o: src/server/coordinates/Map.cpp src/server/coordinates/Map.h
	g++ -std=c++0x -c src/server/coordinates/Map.cpp

Node.o: src/server/coordinates/Node.cpp src/server/coordinates/Node.h
	g++ -std=c++0x -c src/server/coordinates/Node.cpp

Point.o: src/server/coordinates/Point.cpp src/server/coordinates/Point.h
	g++ -std=c++0x -c src/server/coordinates/Point.cpp

TripEndListener.o: src/server/listeners/TripEndListener.cpp src/server/listeners/TripEndListener.h
	g++ -std=c++0x -c src/server/listeners/TripEndListener.cpp

SetTripListener.o: src/server/listeners/SetTripListener.cpp src/server/listeners/SetTripListener.h
	g++ -std=c++0x -c src/server/listeners/SetTripListener.cpp

BFS.o: src/server/managment/BFS.cpp src/server/managment/BFS.h src/server/coordinates/Grid.h src/server/coordinates/CoordinatedItem.h
	g++ -std=c++0x -c src/server/managment/BFS.cpp

DataSender.o: src/server/managment/DataSender.cpp src/server/managment/DataSender.h
	g++ -std=c++0x -c src/server/managment/DataSender.cpp

MainFlow.o: src/server/managment/MainFlow.cpp src/server/managment/MainFlow.h src/server/enum/CarManufactureFactory.h src/server/enum/ColorFactory.h src/server/enum/MartialStatuesFactory.h
	g++ -std=c++0x -c src/server/managment/MainFlow.cpp

ProperInput.o: src/server/managment/ProperInput.cpp src/server/managment/ProperInput.h
	g++ -std=c++0x -c src/server/managment/ProperInput.cpp

SystemOperations.o: src/server/managment/SystemOperations.cpp src/server/managment/SystemOperations.h
	g++ -std=c++0x -c src/server/managment/SystemOperations.cpp

Socket.o: src/server/sockets/Socket.cpp src/server/sockets/Socket.h
	g++ -std=c++0x -c src/server/sockets/Socket.cpp

Udp.o: src/server/sockets/Udp.cpp src/server/sockets/Udp.h
	g++ -std=c++0x -c src/server/sockets/Udp.cpp

Cab.o: src/server/taxi/Cab.cpp src/server/taxi/Cab.h
	g++ -std=c++0x -c src/server/taxi/Cab.cpp

LuxuryCab.o: src/server/taxi/LuxuryCab.cpp src/server/taxi/LuxuryCab.h
	g++ -std=c++0x -c src/server/taxi/LuxuryCab.cpp

Driver.o: src/server/tripOperations/Driver.cpp src/server/tripOperations/Driver.h src/server/enum/MartialStatues.h
	g++ -std=c++0x -c src/server/tripOperations/Driver.cpp

Passenger.o: src/server/tripOperations/Passenger.cpp src/server/tripOperations/Passenger.h
	g++ -std=c++0x -c src/server/tripOperations/Passenger.cpp

Satisfaction.o: src/server/tripOperations/Satisfaction.cpp src/server/tripOperations/Satisfaction.h
	g++ -std=c++0x -c src/server/tripOperations/Satisfaction.cpp

TaxiCenter.o: src/server/tripOperations/TaxiCenter.cpp src/server/tripOperations/TaxiCenter.h src/server/taxi/Taxi.h src/server/enum/Color.h src/server/enum/CarManufacture.h src/server/listeners/EventListener.h
	g++ -std=c++0x -c src/server/tripOperations/TaxiCenter.cpp

TripInfo.o: src/server/tripOperations/TripInfo.cpp src/server/tripOperations/TripInfo.h
	g++ -std=c++0x -c src/server/tripOperations/TripInfo.cpp

clean:
	rm -f *.o server.out client.out
