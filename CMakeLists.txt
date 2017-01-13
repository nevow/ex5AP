cmake_minimum_required(VERSION 3.6)
project(ex5AP)

set(CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES
        src/server/coordinates/Point.cpp
        src/server/coordinates/Point.h
        src/server/coordinates/Map.cpp
        src/server/coordinates/Map.h
        src/server/coordinates/Node.cpp
        src/server/coordinates/Grid.h
        src/server/coordinates/CoordinatedItem.h
        src/server/coordinates/Node.h

        src/server/tripOperations/Driver.cpp
        src/server/tripOperations/Driver.h
        src/server/tripOperations/TripInfo.cpp
        src/server/tripOperations/Satisfaction.cpp
        src/server/tripOperations/Satisfaction.h
        src/server/tripOperations/TripInfo.h
        src/server/tripOperations/TaxiCenter.cpp
        src/server/tripOperations/TaxiCenter.h
        src/server/tripOperations/Passenger.cpp
        src/server/tripOperations/Passenger.h

        src/server/managment/BFS.cpp
        src/server/managment/BFS.h
        src/server/managment/SystemOperations.cpp
        src/server/managment/SystemOperations.h
        src/server/managment/MainFlow.cpp
        src/server/managment/MainFlow.h
        src/server/managment/ProperInput.cpp
        src/server/managment/ProperInput.h
        src/server/managment/DataSender.cpp
        src/server/managment/DataSender.h

        src/server/taxi/LuxuryCab.cpp
        src/server/taxi/LuxuryCab.h
        src/server/taxi/Taxi.h
        src/server/taxi/Cab.cpp
        src/server/taxi/Cab.h

        src/server/listeners/TripEndListener.cpp
        src/server/listeners/TripEndListener.h
        src/server/listeners/EventListener.h

        src/server/enum/MartialStatues.h
        src/server/enum/CarManufacture.h
        src/server/enum/Color.h
        src/server/enum/MartialStatuesFactory.h
        src/server/enum/ColorFactory.h
        src/server/enum/CarManufactureFactory.h

        src/server/sockets/Socket.cpp
        src/server/sockets/Socket.h
        src/server/sockets/Tcp.cpp
        src/server/sockets/Tcp.h
        src/server/sockets/Udp.cpp
        src/server/sockets/Udp.h

        src/server/sockets/Connection.cpp
        src/server/sockets/Connection.h

        src/server/listeners/SetTripListener.cpp
        src/server/listeners/SetTripListener.h)

add_executable(client src/client/client.cpp ${SOURCE_FILES})
add_executable(server src/server/server.cpp ${SOURCE_FILES})

target_link_libraries(client -lpthread ${Boost_LIBRARIES})
target_link_libraries(server -lpthread ${Boost_LIBRARIES})