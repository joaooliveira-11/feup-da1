#ifndef DA_PROJ1_NETWORK_H
#define DA_PROJ1_NETWORK_H
using namespace std;

#include <unordered_set>
#include <unordered_map>
#include <map>
#include "Station.h"
#include "Segment.h"
class Network {
public:
    ~Network();

    ///@brief Add this segment to the source station's adjacent segments vector and to the dest station's incoming segments vector.
    ///@param sourc
    ///@param dest
    ///@param w
    ///@param service
    ///@note Time complexity : O(1)
    ///@return True if added with success and false otherwise.
    bool addSegment(string &sourc, string &dest, int w, string service);

    ///@brief Calculates the max flow between two stations.
    ///@param source
    ///@param target
    ///@note Time complexity : O(VE^2)
    ///@return max flow
    int edmondsKarp(string source, string target);

    ///@brief Calculates the max amount of trains that can simultaneously arrive at a given station
    ///@param dest
    ///@note Time complexity : O(VE^2)
    ///@return max amount of trains that can simultaneously arrive at a given station
    int MaxTrainsArriveAtStation(string dest);

    ///@brief Removes a segment in both directions for periodic maintenance
    ///@param stationA
    ///@param stationB
    ///@note Time Complexity : O(E)
    void removeSegment(string stationA, string stationB);

    ///@brief Removes a station for periodic maintenance
    ///@param station
    ///@note Time Complexity : O(E)
    void removeStation(string station);

    ///@brief Finish the maintenance and resets all segments and stations
    ///@note Time Complexity : O(E)
    void resetSegments();

    ///@brief Calculates the max amount of trains for every station before any maintenance
    ///@note Helper function for topic 4.2
    ///@note Store each station and the max amount of trains in a map
    ///@note Time Complexity : O(V * VE^2)
    void stationsMaxFlow();

    ///@brief Gets the cost of the segments used to calculate the maxflow between 2 stations
    ///@param stationA
    ///@param stationB
    ///@note Time Complexity : O(V * E)
    ///@returns The cost of the segments used to calculate the maxflow between 2 stations
    int getCost(string stationA, string stationB);

    ///@brief Gets the most amount of trains at minimum cost between 2 stations (best trains / price ratio)
    ///@param src
    ///@param dest
    ///@note Time Complexity : O(V ^2 * E * log(V*C)) where C is the value of the largest arc cost in the graph
    ///@returns A pair with the flow(amount of trains)  and the cost
    pair<int, int> minCostFlow(string src, string dest);

    struct StringHash {
        std::size_t operator()(const string& str) const {
            return 37* hash<string>()(str);
        }
    };

    struct StringEqual {
        bool operator()(const string& str1, const string& str2) const {
            return str1 == str2;
        }
    };

    std::unordered_map<string, Station, StringHash, StringEqual> stationMAP;
    std::vector<Segment *> removedSegments;
    vector<Station> station_vector;
    map<string, int> stations_maxflow;
protected:


    ///@brief Auxiliary function to find the shortest path with bfs.
    ///@note The segments must have residual capacity greater than 0.
    ///@param source
    ///@param target
    ///@note Time Complexity: O(V * E)
    ///@return True if a valid path is found, false otherwise.
    bool AugmentingPath(string source, string target);

    ///@brief Bellman-Ford Algorithm for finding shortest path while flagging negative cycles
    ///@param src
    ///@param dest
    ///@param flow
    ///@note Time Complexity : O(V*E)
    ///@returns True if there are no negative cycles
    bool shortestPath(string src, string dest, int flow);

};

#endif //DA_PROJ1_NETWORK_H
