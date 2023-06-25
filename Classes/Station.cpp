#include "Station.h"

Station::Station(string _name, string _district, string _municipality, string _township, string _line) : name(_name), district(_district), municipality(_municipality), township(_township), line(_line){}


string Station::getName() const {
    return name;
}

string Station::getDistrict() const {
    return district;
}

string Station::getMunicipality() const {
    return municipality;
}


bool Station::isVisited() {return visited;}

void Station::setVisited(bool visited) {this->visited = visited;}

void Station::setPath(Segment *path) { this->path = path;}

vector<Segment *> Station::getSegments() {return segments;}

void Station::setSegments(vector<Segment *>newSegments){segments = newSegments;}


bool Station::operator==(const Station& _otherStation) const{
    return this->name == _otherStation.name;
}

void Station::addSegment(Segment *s) {
    segments.push_back(s);

}

void Station::addIncoming(Segment *segment) {
    incoming.push_back(segment);
}

vector<Segment*> Station::getIncoming(){
    return incoming;
}

void Station::setIncoming(vector<Segment *> newIncoming){incoming = newIncoming;}

Segment* Station::getPath() {return path;}

int Station::getDist(){ return dist;}

void Station::setDist(int distance){ dist = distance;}
