
#include "Menu.h"
#include "Network.h"
#include "Reading.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <climits>


using namespace std;
bool execute = true;
Network railway = Reading::readAllFiles();

//T2.1
void Menu::SimultaneouslyMaxTrains(string departurestation_, string arrivalstation_) {
    int maxFlow = 0;
    maxFlow = railway.edmondsKarp(departurestation_, arrivalstation_);
    cout << "The maximum number of trains that can simultaneously travel between these two stations is " << maxFlow
         << endl;
}

//T2.2
void Menu::NetworksSimultaneouslyMaxTrains() {
    int maxflow = 0;
    set<pair<string, string>> topNetworksTrains;

    for (auto index_station1 = 0; index_station1 != railway.station_vector.size(); index_station1++) {
        for (auto index_station2 = index_station1 + 1;
             index_station2 != railway.station_vector.size(); index_station2++) {
            string start, target;
            start = railway.station_vector[index_station1].getName();
            target = railway.station_vector[index_station2].getName();
            int flow = railway.edmondsKarp(start, target);
            if (flow == maxflow) {
                pair<string, string> pair = make_pair(start, target);
                topNetworksTrains.insert(pair);
            } else if (flow > maxflow) {
                topNetworksTrains.clear();
                maxflow = flow;
                pair<string, string> pair = make_pair(start, target);
                topNetworksTrains.insert(pair);
            }
        }
    }
    cout
            << "The Segment/'s with the most amount of trains when taking full advantage of the existing network capacity is/are: \n";
    for (auto pair: topNetworksTrains) {
        cout << "{" << pair.first << "," << pair.second << "}" << endl;
        cout << "{" << pair.second << "," << pair.first << "}" << endl;
    }
    cout << "With " << maxflow << " trains when taking full advantage of the existing network capacity\n";
}

//T2.3
struct Compare_pair {
    bool operator()(const pair<string, int> &a, const pair<string, int> &b) {
        if(a.second != b.second)  return a.second > b.second;
        return a.first < b.first;
    }
};

void Menu::topK_municipalities_districts(int k) {
    string district, municipalitie;
    map<string, vector<string>> districs_stations;
    map<string, vector<string>> municipalies_stations;
    for (auto el: railway.station_vector) {
        district = el.getDistrict();
        municipalitie = el.getMunicipality();

        if (districs_stations.find(district) != districs_stations.end()) {
            districs_stations[district].push_back(el.getName());
        }
        if (municipalies_stations.find(municipalitie) != municipalies_stations.end()) {
            municipalies_stations[municipalitie].push_back(el.getName());
        }
        if (districs_stations.find(district) == districs_stations.end()) {
            vector<string> aux;
            aux.push_back(el.getName());
            districs_stations.insert({district, aux});
        }
        if (municipalies_stations.find(municipalitie) == municipalies_stations.end()) {
            vector<string> aux1;
            aux1.push_back(el.getName());
            municipalies_stations.insert({municipalitie, aux1});
        }
    }
    set<pair<string, int>, Compare_pair> topk_districts;
    set<pair<string, int>, Compare_pair> topk_municipalities;
    int totalflow1 = 0;
    for (auto pair: districs_stations) {
        for (auto station1: pair.second) {
            for (auto station2: pair.second) {
                if (station1 != station2) {
                    int flow = railway.edmondsKarp(station1, station2);
                    totalflow1 += flow;
                }
            }
        }
        std::pair<string, int> pair1 = make_pair(pair.first, totalflow1);
        topk_districts.insert(pair1);
        totalflow1 = 0;
    }
    int totalflow = 0;
    for (auto pair: municipalies_stations) {
        for (auto station1: pair.second) {
            for (auto station2: pair.second) {
                if (station1 != station2) {
                    int flow = railway.edmondsKarp(station1, station2);
                    totalflow += flow;

                }
            }
        }
        std::pair<string, int> pair2 = make_pair(pair.first, totalflow);
        topk_municipalities.insert(pair2);
        totalflow = 0;
    }

    int count_districts = 0;
    int count_municipalities = 0;

    cout << "The " << k << " districts with the most transportation needes" << endl;
    for (auto pair: topk_districts) {
        if (count_districts != k) {
            cout << pair.first << " " << pair.second << endl;
            count_districts++;
        } else break;
    }

    cout << endl;
    cout << "The " << k << " municipalities with the most transportation needes" << endl;
    for (auto pair: topk_municipalities) {
        if (count_municipalities != k) {
            cout << pair.first << " " << pair.second << endl;
            count_municipalities++;
        } else break;
    }
}

void Menu::topK_municipalities_districtsv2(int k) {
    string district, municipalitie;
    map<string, vector<string>> districs_stations;
    map<string, vector<string>> municipalies_stations;
    for (auto el: railway.station_vector) {
        district = el.getDistrict();
        municipalitie = el.getMunicipality();

        if (districs_stations.find(district) != districs_stations.end()) {
            districs_stations[district].push_back(el.getName());
        }
        if (municipalies_stations.find(municipalitie) != municipalies_stations.end()) {
            municipalies_stations[municipalitie].push_back(el.getName());
        }
        if (districs_stations.find(district) == districs_stations.end()) {
            vector<string> aux;
            aux.push_back(el.getName());
            districs_stations.insert({district, aux});
        }
        if (municipalies_stations.find(municipalitie) == municipalies_stations.end()) {
            vector<string> aux1;
            aux1.push_back(el.getName());
            municipalies_stations.insert({municipalitie, aux1});
        }
    }
    set<pair<string, int>, Compare_pair> topk_districts;
    set<pair<string, int>, Compare_pair> topk_municipalities;
    int totalflow1 = 0;
    for (auto pair: districs_stations) {
        for (auto station1: pair.second) {
            for (auto station2: pair.second) {
                if (station1 != station2) {
                    int flow = railway.edmondsKarp(station1, station2);
                    totalflow1 += flow;
                }
            }
            auto station = railway.stationMAP.find(station1)->second;
            for (auto edge: station.getSegments()) {
                auto station_Dest = edge->getStationB();
                if (railway.stationMAP.find(station_Dest)->second.getDistrict() != pair.first) {
                    int flow = railway.edmondsKarp(station1, station_Dest);
                    totalflow1 -= flow;
                }
            }
            for (auto edge: station.getIncoming()) {
                auto station_start = edge->getStationA();
                if (railway.stationMAP.find(station_start)->second.getDistrict() != pair.first) {
                    int flow = railway.edmondsKarp(station_start, station1);
                    totalflow1 += flow;
                }
            }
        }
        std::pair<string, int> pair1 = make_pair(pair.first, totalflow1);
        topk_districts.insert(pair1);
        totalflow1 = 0;
    }

    int totalflow = 0;
    for (auto pair: municipalies_stations) {
        for (auto station1: pair.second) {
            for (auto station2: pair.second) {
                if (station1 != station2) {
                    int flow = railway.edmondsKarp(station1, station2);
                    totalflow += flow;
                }
            }
            auto station = railway.stationMAP.find(station1)->second;
            for (auto edge: station.getSegments()) {
                auto station_Dest = edge->getStationB();
                if (railway.stationMAP.find(station_Dest)->second.getMunicipality() != pair.first) {
                    int flow = railway.edmondsKarp(station1, station_Dest);
                    totalflow -= flow;
                }
            }
            for (auto edge: station.getIncoming()) {
                auto station_start = edge->getStationA();
                if (railway.stationMAP.find(station_start)->second.getMunicipality() != pair.first) {
                    int flow = railway.edmondsKarp(station_start, station1);
                    totalflow += flow;
                }
            }
        }
        std::pair<string, int> pair2 = make_pair(pair.first, totalflow);
        topk_municipalities.insert(pair2);
        totalflow = 0;
    }

    int count_districts = 0;
    int count_municipalities = 0;

    cout << "The " << k << " districts with the most transportation needes" << endl;
    for (auto pair: topk_districts) {
        if (count_districts != k) {
            cout << pair.first << " " << pair.second << endl;
            count_districts++;
        } else break;
    }

    cout << endl;
    cout << "The " << k << " municipalities with the most transportation needes" << endl;
    for (auto pair: topk_municipalities) {
        if (count_municipalities != k) {
            cout << pair.first << " " << pair.second << endl;
            count_municipalities++;
        } else break;
    }
}

void Menu::topK_municipalities_districtsv3(int k) {
    string district, municipalitie;
    map<string, vector<string>> districs_stations;
    map<string, vector<string>> municipalies_stations;
    for (auto el: railway.station_vector) {
        district = el.getDistrict();
        municipalitie = el.getMunicipality();

        if (districs_stations.find(district) != districs_stations.end()) {
            districs_stations[district].push_back(el.getName());
        }
        if (municipalies_stations.find(municipalitie) != municipalies_stations.end()) {
            municipalies_stations[municipalitie].push_back(el.getName());
        }
        if (districs_stations.find(district) == districs_stations.end()) {
            vector<string> aux;
            aux.push_back(el.getName());
            districs_stations.insert({district, aux});
        }
        if (municipalies_stations.find(municipalitie) == municipalies_stations.end()) {
            vector<string> aux1;
            aux1.push_back(el.getName());
            municipalies_stations.insert({municipalitie, aux1});
        }
    }
    set<pair<string, int>, Compare_pair> topk_districts;
    set<pair<string, int>, Compare_pair> topk_municipalities;

    int maxflow1 = 0;
    for (auto pair: districs_stations) {
        for (auto station1: pair.second) {
            for (auto station2: pair.second) {
                if (station1 != station2) {
                    int flow = railway.edmondsKarp(station1, station2);
                    if(flow > maxflow1) maxflow1 = flow;
                }
            }
        }
        std::pair<string, int> pair1 = make_pair(pair.first, maxflow1);
        topk_districts.insert(pair1);
        maxflow1 = 0;
    }
    int maxflow = 0;
    for(auto pair: municipalies_stations) {
        for (auto station1: pair.second) {
            for (auto station2: pair.second) {
                if (station1 != station2) {
                    int flow = railway.edmondsKarp(station1, station2);
                    if(flow > maxflow) maxflow = flow;
                }
            }
        }
        std::pair<string, int> pair2 = make_pair(pair.first, maxflow);
        topk_municipalities.insert(pair2);
        maxflow = 0;
    }

    int count_districts = 0;
    int count_municipalities = 0;

    cout << "The " << k << " districts with the most transportation needes" << endl;
    for (auto pair: topk_districts) {
        if (count_districts != k) {
            cout << pair.first << " " << pair.second << endl;
            count_districts++;
        } else break;
    }

    cout << endl;
    cout << "The " << k << " municipalities with the most transportation needes" << endl;
    for (auto pair: topk_municipalities) {
        if (count_municipalities != k) {
            cout << pair.first << " " << pair.second << endl;
            count_municipalities++;
        } else break;
    }
}

//T2.4
void Menu::MaxTrainsArriveAtStation(string dest) {
    int flow = railway.MaxTrainsArriveAtStation(dest);
    cout << "The maximum number of trains that arrive in " << dest << " at the same time is " << flow << endl;
}

//T3.1(custo do max flow)
void Menu::maxFlowCost(){
    string stationA, stationB;

    cout << "Select source of segment: ";
    getline(cin >> ws, stationA);
    while (railway.stationMAP.find(stationA) == railway.stationMAP.end()) {
        cout << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
        getline(cin >> ws, stationA);
    }

    cout << "Select destiny of segment: ";
    getline(cin >> ws, stationB);
    while (railway.stationMAP.find(stationB) == railway.stationMAP.end()) {
        cout << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
        getline(cin >> ws, stationB);
    }

    int flow = railway.edmondsKarp(stationA, stationB);
    int cost = railway.getCost(stationA, stationB);
    cout << "The cost of the maximal amount of trains is " <<cost <<" euros, with " <<flow <<" trains simultaneously" <<"\n";
}

//T3.1 (minimo custo com max flow)
void Menu::minCostFlow() {
    string stationA, stationB;

    cout << "Select source of segment: ";
    getline(cin >> ws, stationA);
    while (railway.stationMAP.find(stationA) == railway.stationMAP.end()) {
        cout << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
        getline(cin >> ws, stationA);
    }

    cout << "Select destiny of segment: ";
    getline(cin >> ws, stationB);
    while (railway.stationMAP.find(stationB) == railway.stationMAP.end()) {
        cout << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
        getline(cin >> ws, stationB);
    }

    pair<int, int> result = railway.minCostFlow(stationA, stationB);
    cout <<"The minimal cost of travelling between these 2 stations is "<<result.first << " euros using " << result.second <<" trains simultaneously." <<"\n";
}

//T4.1(1 segmento)
void Menu::RemoveSegment() {
    string stationA, stationB;

    cout << "Select source of segment: ";
    getline(cin >> ws, stationA);
    while (railway.stationMAP.find(stationA) == railway.stationMAP.end()) {
        cout << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
        getline(cin >> ws, stationA);
    }

    cout << "Select destiny of segment: ";
    getline(cin >> ws, stationB);
    while (railway.stationMAP.find(stationB) == railway.stationMAP.end()) {
        cout << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
        getline(cin >> ws, stationB);
    }

    railway.removeSegment(stationA, stationB);
    railway.removeSegment(stationB, stationA);
}

//T4.1 (estação completa)
void Menu::RemoveStation() {
    string stationA;

    cout << "Select Station to make inactive: ";
    getline(cin >> ws, stationA);
    while (railway.stationMAP.find(stationA) == railway.stationMAP.end()) {
        cout << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
        getline(cin >> ws, stationA);
    }

    railway.removeStation(stationA);
}


void Menu::ResetSegments() {
    railway.resetSegments();
    cout << "All maintenance has been canceled. Whole netowrk is available \n";
}

//4.2
void Menu::topK_mostaffected(int k){
    set<pair<string, int>, Compare_pair> new_station_flow_difference;
    for(auto station : railway.station_vector){
        if(station.getName() != "bigsource") {
            string name = station.getName();
            int flow = railway.MaxTrainsArriveAtStation(name);
            std::pair<string, int> pair = make_pair(name, (railway.stations_maxflow[name] - flow));
            new_station_flow_difference.insert(pair);
        }
    }

    int count = 0;

    cout << "By removing the following segments:\n";
    for(auto edge : railway.removedSegments){
        if(edge->getStationA() != "bigsource") cout << edge->getStationA() << " -> " << edge->getStationB() << endl;
    }

    cout << "The most affected stations are:\n";
    for (auto pair: new_station_flow_difference) {
        if (count != k) {
            cout << railway.stations_maxflow[pair.first] << " -> " << railway.stations_maxflow[pair.first] - pair.second << "  " << pair.first << endl;
            count++;
        } else break;
    }
}

void Menu::maintenanceSubmenu() {
    if(execute){
        railway.stationsMaxFlow();
        execute = false;
    }

    int option;
    cout << "What maintenance do you want to perform?" << endl;
    cout << "1 - Maintenance on a segment of train track" << endl;
    cout << "2 - Maintenance on a station " << endl;
    cout << "3 - Re-activate all segments / stations in maintenance" << endl;
    cout << "4 - View the most affected stations by the maintenance repairs" << endl;
    cin >> option;

    switch (option) {
        case 1: {
            RemoveSegment();

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }
        case 2: {
            RemoveStation();

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }
        case 3: {
            ResetSegments();

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }
        case 4:{
            int k;
            cout << "\nInsert the number of stations\n";
            cin >> k;

            topK_mostaffected(k);

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }
        default:
            break;
    }
}

void Menu::costSubmenu(){
    cout << "What do you prefer:" <<"\n" <<"1 - the cost of the max trains simultaneously" <<"\n"
    <<"2 - The best Flow-Cost ratio (Min Cost-Flow )" <<"\n";
    int option;
    cin >> option;
    switch (option) {
        case 1:
            maxFlowCost();
            break;

        case 2:
            minCostFlow();
            break;
        default:
            break;
    }
}


void Menu::readmenu() {
    int option;
    cout << "===============MAIN MENU===============" << endl;
    cout << "1 - Maximum number of trains that can simultaneously travel between tow specific stations" << endl;
    cout << "2 - Networks with the most amount of trains when taking full advantage of the existing network capacity"
         << endl;
    cout << "3 - TopK Districts and Municipalies with the most transportation needs" << endl;
    cout << "4 - Maximum number of trains arriving at the same time at a specific station" << endl;
    cout << "5 - Cost Optimized Max Flow" << endl;
    cout << "6 - Maintenance on the tracks" << endl;
    cout << "=======================================" << endl;
    cout << "Option:";
    cin >> option;

    switch (option) {
        case 1: {
            string departure_station, arrival_station;
            cout << "\nEnter the name of the departure station. (ex.: Porto Campanhã)\n";
            getline(cin >> ws, departure_station);
            while (railway.stationMAP.find(departure_station) == railway.stationMAP.end()) {
                cout
                        << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
                getline(cin >> ws, departure_station);
            }

            cout << "\nEnter the name of the arrival station. (ex.: Porto Campanhã)\n";
            getline(cin >> ws, arrival_station);
            while (railway.stationMAP.find(arrival_station) == railway.stationMAP.end()) {
                cout
                        << "This station does not exist in our database, please enter a valid name. (ex.: Porto Campanhã) \n";
                getline(cin >> ws, arrival_station);
            }

            SimultaneouslyMaxTrains(departure_station, arrival_station);

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }

        case 2: {
            NetworksSimultaneouslyMaxTrains();

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }

        case 3: {
            int k, version;
            cout << "\nInsert the number of districts and municipalities\n";
            cin >> k;

            cout << "Chose what version of 2.3 you want to see\n";
            cout << "1 - Transportation needs by the amount of flow inside the district / municipaly" << endl;
            cout << "2 - Transportation needs by the balance of flow inside, leaving and coming in the district / municipaly"<< endl;
            cout << "3 - Transportation needs by the biggest flow between all pairs of station in a district / municipaly" << endl;
            cin >> version;

            switch(version){
                case 1: {
                    topK_municipalities_districts(k);
                    break;
                }
                case 2:{
                    topK_municipalities_districtsv2(k);
                    break;
                }
                case 3:{
                    topK_municipalities_districtsv3(k);
                    break;
                }
                default:
                    cout << "Insira uma tecla valida";
            }

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }

        case 4: {
            string target_station;
            cout << "\nInsert the name of the arrival station. (ex.: Lisboa Oriente)\n";
            getline(cin >> ws, target_station);
            while (railway.stationMAP.find(target_station) == railway.stationMAP.end()) {
                cout
                        << "This station does not exist in our data base, insert a valid station. (ex.: Lisboa Oriente) \n";
                getline(cin >> ws, target_station);
            }
            MaxTrainsArriveAtStation(target_station);

            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }
        case 5: {
            costSubmenu();
            string decision;
            cout << "Do you want to do another action?. (ex.: yes or no) \n";
            cin >> decision;
            while (decision != "yes" && decision != "no") {
                cout << "Do you want to do another action?. (ex.: yes or no) \n";
                cin >> decision;
            }
            if (decision == "yes") readmenu();
            else break;
        }
        case 6: {
            maintenanceSubmenu();
            break;
        }

        default:
            cout << "\nEnter a valid key.\n";
            break;
    }
}