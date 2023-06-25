
#ifndef DA_PROJ1_READING_H
#define DA_PROJ1_READING_H
#include "Segment.h"
#include "Station.h"
#include "Network.h"
#include <vector>

class Reading {
public:
    ///@brief Reads network.csv and stations.csv
    ///@note Store Stations in an unordered_map and build a graph with vertexes representing stations and edges the networks.
    ///@note Time complexity : O(n)
    ///@returns A graph with the vertexes being stations and the edges being networks
    static Network readAllFiles();
};


#endif //DA_PROJ1_READING_H
