
#include <fstream>
#include <sstream>
#include <iostream>
#include "Reading.h"
#include "Network.h"
using namespace std;

Network Reading::readAllFiles(){
    Network network = Network();

    int check_station = 0;
    int check_segment = 0;

    int verify = 0;
    string NAME, DISTRICT, MUNICIPALITY, TOWNSHIP, LINE;
    char c;
    ifstream in("../Project1_Data/stations.csv");
    if (!in.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in, line);) {
        istringstream iss(line);
        if (verify == 0) {
            verify++;
            continue;
        }
        getline(iss, NAME, ',');
        getline(iss,DISTRICT, ',');
        getline(iss, MUNICIPALITY, ',');
        getline(iss, TOWNSHIP, ',');
        getline(iss, LINE, ',');

        Station station = Station(NAME, DISTRICT, MUNICIPALITY, TOWNSHIP, LINE);
        if(network.stationMAP.find(NAME) == network.stationMAP.end()) network.stationMAP.emplace(NAME, station);
        for(auto station_in : network.station_vector){
            if(station_in.getName() == station.getName()){
                check_station = 1;
            }
        }
        if(check_station == 0) network.station_vector.push_back(station);
        check_station = 0;
    }

    vector<Segment> segments;
    int verify1 = 0, CAPACITY;
    string STATION_A,STATION_B,SERVICE;
    char c1;
    ifstream in1("../Project1_Data/network.csv");
    if (!in1.is_open()) exit(EXIT_FAILURE);

    for (string line1; getline(in1, line1);) {
        istringstream iss1(line1);
        if (verify1 == 0) {
            verify1++;
            continue;
        }
        getline(iss1, STATION_A, ',');
        getline(iss1,STATION_B, ',');
        iss1 >> CAPACITY >> c1;
        getline(iss1, SERVICE, ',');

        Segment segment = Segment(STATION_A, STATION_B, CAPACITY, SERVICE);
        for(auto segment_in : segments){
            if((segment_in.getStationA() == segment.getStationA()) && (segment_in.getStationB() == segment.getStationB())){
                check_segment = 1;
            }
        }
        if(check_segment == 0) segments.push_back(segment);
        check_segment = 0;
    }

    for(auto segment: segments){
        string id1, id2;
        auto itr1 = network.stationMAP.find(segment.getStationA());
        auto itr2 = network.stationMAP.find(segment.getStationB());
        if(itr1 != network.stationMAP.end()) id1 = itr1->first;
        if(itr2 != network.stationMAP.end()) id2 = itr2->first;
        network.addSegment(id1, id2, (segment.getCapacity() / 2), segment.getService());
        network.addSegment(id2, id1, (segment.getCapacity() / 2), segment.getService());
    }

    return network;
}

