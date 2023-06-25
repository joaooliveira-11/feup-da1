#ifndef DA_PROJ1_SEGMENT_H
#define DA_PROJ1_SEGMENT_H

#include <string>
using  namespace std;

class Segment {
private:
    string stationA, stationB, service;
    int capacity;
    int flow;
public:
    ///@brief Constructor of new Segment given it's departure station name, arrival station name, capacity and service.
    ///@param _stationA
    ///@param _stationB
    ///@param _capacity
    ///@param _service
    Segment( string _stationA, string _stationB, int _capacity, string _service);

    ///@brief Getter for the Segment´s departure station name.
    ///@returns A Station´s departure station name.
    string getStationA() const;

    ///@brief Getter for the Segment´s arrival station name.
    ///@returns A Station´s arrival station name.
    string getStationB() const;

    ///@brief Getter for the Segment´s capacity.
    ///@returns A Segment´s capacity.
    int getCapacity() const;

    ///@brief Getter for the Segment´s flow.
    ///@returns A Segment´s flow.
    int getFlow() const;

    ///@brief Setter for the Segment´s flow attribute.
    ///@param f
    void setFlow(int f);

    ///@brief Getter for the Segment´s service.
    ///@returns A Segment´s service.
    string getService() const;

    ///@brief Gets the segment service cost multiplied by the current flow
    ///@returns the segment service cost multiplied by the current flow
    int getCost();
};


#endif //DA_PROJ1_SEGMENT_H
