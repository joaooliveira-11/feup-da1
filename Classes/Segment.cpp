#include <iostream>
#include "Segment.h"


Segment::Segment(string _stationA, string _stationB, int _capacity, string _service) : stationA(_stationA), stationB(_stationB), capacity(_capacity), service(_service){}

string Segment::getStationA() const{
    return stationA;
}

string Segment::getStationB() const{
    return stationB;
}

int Segment::getCapacity() const{
    return capacity;
}

string Segment::getService() const{
    return service;
}

int Segment::getFlow() const{
    return flow;
}

void Segment::setFlow(int f) {flow = f;}

int Segment::getCost(){
    if(this->getService() == "STANDARD") return getFlow() * 2;
    else if(this->getService() == "ALFA PENDULAR") return getFlow() * 4;
    else {
        cout << "error";
        return 0;
    }
}
