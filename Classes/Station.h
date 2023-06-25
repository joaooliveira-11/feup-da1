#ifndef DA_PROJ1_STATION_H
#define DA_PROJ1_STATION_H

using namespace std;
#include <string>
#include <vector>
#include "Segment.h"


class Station {
private:
    string name, district, municipality, township, line;
    vector<Segment *> segments;

    bool visited = false;
    Segment *path = nullptr;

    std::vector<Segment *> incoming;

    int dist = 0;

public:

    ///@brief Constructor of new Station given it´s station name, district, municipality, township and line.
    ///@param _name
    ///@param _district
    ///@param _municipality
    ///@param _township
    ///@param _line
    Station(string _name, string _district, string _municipality, string _township, string _line);

    ///@brief Getter for the Station´s name.
    ///@returns A Station´s name.
    string getName() const;

    ///@brief Getter for the Station´s district.
    ///@returns A Station´s district.
    string getDistrict() const;

    ///@brief Getter for the Station´s municipality.
    ///@returns A Station´s municipality.
    string getMunicipality() const;

    ///@brief Getter for the Station´s township.
    ///@returns A Station´s township.
    string getTownship() const;

    ///@brief Getter for the Station´s line.
    ///@returns A Station´s line.
    string getLine() const;

    ///@brief Operator= overload.
    ///@returns True if our Station´s name is equal to the Station received as parameter.
    ///@param _otherStation
    bool operator==(const Station& _otherStation) const;

    ///@brief Setter for the Station´s visited attribute.
    ///@param visited
    void setVisited(bool visited);

    ///@brief Setter for the Station´s path attribute.
    ///@param path
    void setPath(Segment *path);

    ///@return True if the station is visited, false otherwise
    bool isVisited();

    ///@brief Getter for the Station´s adjacent segments.
    ///@returns A vector with all adjacent segments.
    vector<Segment *> getSegments();

    ///@brief Getter for the Station´s incoming segments.
    ///@returns A vector with all incoming segments.
    vector<Segment *> getIncoming();

    ///@brief Getter for the Station´s path.
    ///@returns A Station´s path.
    Segment * getPath();

    ///@brief Add a segment to the station's incoming segments.
    ///@param segment
    void addIncoming(Segment *segment);

    ///@brief Add a segment to the station's adjacent segments.
    ///@param s
    void addSegment(Segment *s);

    ///@brief Setter for the Station´s adjacent segments vector.
    ///@param newSegments
    void setSegments(vector<Segment *> newSegments);

    ///@brief Setter for the Station´s incoming segments vector.
    ///@param newIncoming
    void setIncoming(vector<Segment *> newIncoming);

    ///@brief Gets the cost to get to a station from a single source
    ///@returns cost to get to a station from a single source
    int getDist();

    ///@brief Sets the cost to get to a station from a single source
    ///@param distance
    void setDist(int distance);
};


#endif //DA_PROJ1_STATION_H
