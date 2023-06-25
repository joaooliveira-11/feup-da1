#include <queue>
#include <iostream>
#include <climits>
#include <algorithm>
#include "Network.h"

using namespace std;

Network::~Network() {
}

bool Network::addSegment(string &stationA, string &stationB, int w, string service) {
    auto v1 = stationMAP.find(stationA);
    auto v2 = stationMAP.find(stationB);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    Segment *s = new Segment(stationA, stationB, w, service);
    v1->second.addSegment(s);
    v2->second.addIncoming(s);
    return true;
}


bool Network::AugmentingPath(string source, string target) {
    for(auto& station: stationMAP){
        station.second.setVisited(false);
        station.second.setPath(nullptr);
    }
    queue<string>q;
    q.push(source);
    stationMAP.find(source)->second.setVisited(true);
    while(!q.empty()){
        string v = q.front();
        q.pop();
        for(auto edge : stationMAP.find(v)->second.getSegments()){
            string w = edge->getStationB();
            if(!stationMAP.find(w)->second.isVisited() && ((edge->getCapacity() - edge->getFlow()) > 0)){
                q.push(w);
                stationMAP.find(w)->second.setVisited(true);
                stationMAP.find(w)->second.setPath(edge);
                if(w == target) return true;
            }
        }
        for(auto edge: stationMAP.find(v)->second.getIncoming()){
            string w = edge->getStationA();
            if(!stationMAP.find(w)->second.isVisited() && edge->getFlow() > 0){
                q.push(w);
                stationMAP.find(w)->second.setVisited(true);
                stationMAP.find(w)->second.setPath(edge);
            }
        }
    }
    return stationMAP.find(target)->second.isVisited();
}

int Network::edmondsKarp(string source, string target){
    for (auto& station : stationMAP) {
        for (auto& edge : station.second.getSegments()) {
            edge->setFlow(0);
        }
    }
    int exit_error = 0;
    int maxFlow = 0;
    while (AugmentingPath(source, target)) {
        string idDest = target;
        int minResidual = INT_MAX;
        while (idDest != source) {
            auto edge = stationMAP.find(idDest)->second.getPath();
            int residual;
            if (edge->getStationB()== idDest) {
                residual = edge->getCapacity() - edge->getFlow();
                idDest = edge->getStationA();
            } else {
                residual = edge->getFlow();
                idDest = edge->getStationB();
            }
            if (residual < minResidual) {
                minResidual = residual;
            }
        }
        idDest = target;
        while (idDest != source) {
            auto edge = stationMAP.find(idDest)->second.getPath();
            if (edge->getStationB() == idDest) {
                edge->setFlow(edge->getFlow() + minResidual);
                idDest = edge->getStationA();
            } else {
                edge->setFlow(edge->getFlow() - minResidual);
                idDest = edge->getStationB();
            }
        }
        maxFlow += minResidual;
    }
    return maxFlow;
}

void Network::removeSegment(string stationA, string stationB){
    int count = 0;
    //remove da origem
    vector<Segment *> newSegments;
    for(auto s :  stationMAP.find(stationA)->second.getSegments()){
        if(s->getStationB() == stationB){
            removedSegments.push_back(s);
            count++;
        }else{
            newSegments.push_back(s);
        }
    }
    count = 0;

    stationMAP.find(stationA)->second.setSegments(newSegments);

    //remove do destino
    vector<Segment *> newIncoming;
    for(auto s : stationMAP.find(stationB)->second.getIncoming()){
        if(s->getStationA() == stationA){
            count++;
        }else{
            newIncoming.push_back(s);
        }
    }

    stationMAP.find(stationB)->second.setIncoming(newIncoming);

}

void Network::removeStation(string station){
    for(auto segment  : stationMAP.find(station)->second.getSegments()){
        removeSegment(station, segment->getStationB());
    }

    for(auto segment  : stationMAP.find(station)->second.getIncoming()){
        removeSegment(segment->getStationA(), station);
    }
}

void Network::resetSegments(){
    for (auto s : removedSegments){
        if(s->getStationA() != "bigsource") {
            stationMAP.find(s->getStationA())->second.addSegment(s);
            stationMAP.find(s->getStationB())->second.addIncoming(s);
            cout << "Added " << s->getStationA() << " - " << s->getStationB() << "\n";
        }
    }
    removedSegments = {};
}

int Network::MaxTrainsArriveAtStation(string dest){
    vector<Station> startingStations;
    for (auto station_: station_vector) {
        string station_name = station_.getName();
        if (stationMAP.find(station_name)->second.getSegments().size() == 1 && stationMAP.find(station_name)->second.getName() != dest && (stationMAP.find(station_name)->second.getSegments().size() != 0 | stationMAP.find(station_name)->second.getIncoming().size() != 0) ){
            startingStations.push_back(stationMAP.find(station_name)->second);
        }
    }
    string bigsource_name = "bigsource";
    Station bigstation = Station(bigsource_name, "none", "none", "none", "none");
    stationMAP.emplace(bigsource_name, bigstation);

    for (auto station1: startingStations) {
        string stationb = station1.getName();
        addSegment(bigsource_name, stationb, INT_MAX, "none");
    }

    int maxflow = edmondsKarp(bigsource_name, dest);

    //remover os edges adicionados
    for(auto station2 : startingStations){
        removeSegment(bigsource_name, station2.getName());
    }
    startingStations.clear();
    return maxflow;
}

void Network::stationsMaxFlow(){
    for(auto _station_ : station_vector){
        string name = _station_.getName();
        int flow = MaxTrainsArriveAtStation(name);
        stations_maxflow.insert({name, flow});
    }
}


int Network::getCost(string stationA, string stationB){
    int total = 0;
    string station = stationA;
    for(auto e : stationMAP) {
        for(auto seg : e.second.getSegments()){
            if(seg->getCost() > 0) {
                total += seg->getCost();
            }
        }
    }
    return total;
}

bool Network::shortestPath(string src, string dest, int flow) {
    //initialize flow of every station dist
    for (auto& station : stationMAP) {
        station.second.setVisited(false);
        station.second.setDist(INT_MAX);
    }
    stationMAP.find(src)->second.setDist(0);
    stationMAP.find(src)->second.setVisited(true);
    queue<string> q;
    q.push(src);
    while(!q.empty()){
        string u = q.front();
        q.pop();
        for(auto& segment : stationMAP.find(u)->second.getSegments()){
            string v = segment->getStationB();
            segment->setFlow(flow);
            if(segment->getCapacity() > 0 &&
            (stationMAP.find(v)->second.getDist() > (stationMAP.find(u)->second.getDist() + segment->getCost()))){
                stationMAP.find(v)->second.setDist(stationMAP.find(u)->second.getDist() + segment->getCost());
                stationMAP.find(v)->second.setPath(segment);

                if(!stationMAP.find(v)->second.isVisited()){
                    stationMAP.find(v)->second.setVisited(true);
                    q.push(v);
                }
            }
        }
    }
    return true;
}

pair<int, int> Network::minCostFlow(string src, string dest){
    int flow = 1;
    while(true){
        if(!shortestPath(src, dest, flow));
        if(stationMAP.find(dest)->second.getDist() == INT_MAX){
            cout << "station unreachable";
            break;
        }

        string cur = dest;
        int f = INT_MAX;

        while(cur != src){
            f = min(f, stationMAP.find(cur)->second.getPath()->getCapacity());
            cur = stationMAP.find(cur)->second.getPath()->getStationA();

        }
        if(flow == f) return {stationMAP.find(dest)->second.getDist(), flow};
        else flow = f;

        //print path
        string current = dest;
        vector<Segment *> path;
        cout <<"The path is: " <<endl;
        while(current != src){
            path.push_back(stationMAP.find(current)->second.getPath());
            current = stationMAP.find(current)->second.getPath()->getStationA();
        }

        reverse(path.begin(), path.end());

        for( auto item : path){
            cout <<item->getStationA() <<" -> " <<item->getStationB() <<" ("<<item->getService() <<")"<<endl;
        }
    }
    return {stationMAP.find(dest)->second.getDist(), flow};
}