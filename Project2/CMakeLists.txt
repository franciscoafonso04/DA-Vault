cmake_minimum_required(VERSION 3.28)
project(TSP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data_structures)

add_executable(TSP
        Graph.cpp
        Graph.h
        MutablePriorityQueue.h
        ParsingFunctions.cpp
        ParsingFunctions.h
        main.cpp
        App.cpp
        App.h
        BackTracking.cpp
        BackTracking.h
        TriangularApproximation.cpp
        TriangularApproximation.h
        OtherHeuristics.cpp
        OtherHeuristics.h
        RealWorld.cpp
        RealWorld.h
)