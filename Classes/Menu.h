#ifndef DA_PROJ1_MENU_H
#define DA_PROJ1_MENU_H

#include <string>
using namespace std;
class Menu {
public:
    ///@brief Runs the interactive user menu.
    static void readmenu();

    ///@brief Prints the maximum number of trains that can simultaneously travel between 2 stations
    ///@note Calls edmonskarp algorithm
    static void SimultaneouslyMaxTrains(string departurestation_, string arrivalstation_);

    ///@brief Prints, from all pairs of staions, the ones that require the most amount of trains when taking full advantage of the network capacity
    ///@note Calls edmonskarp algorithm
    static void NetworksSimultaneouslyMaxTrains();

    ///@brief Prints the top-k municipalities and districts with the most transportation needs
    ///@param k
    ///@note Calls edmonskarp algorithm
    static void topK_municipalities_districts(int k);
    static void topK_municipalities_districtsv2(int k);
    static void topK_municipalities_districtsv3(int k);

    ///@brief Prints the maximum number of trains that can simultaneously arrive at a given station
    ///@param dest
    ///@note calls edmonskarp algorithm
    static void MaxTrainsArriveAtStation(string dest);

    ///@brief Runs the interactive maintenance submenu
    static void maintenanceSubmenu();

    ///@brief Removes a segment in both ways for maintenance
    ///@note Calls remove segment from network class
    static void RemoveSegment();

    ///@brief Removes a station for maintenance
    ///@note Removing a station is removing all the segment incoming and outgoing from a station making it unreachable
    ///@note Calls remove station from network class
    static void RemoveStation();

    ///@brief Finish the maintenance and resets all segments and stations
    ///@note Calls reset segments from network class
    static void ResetSegments();

    ///@brief Prints the topk most affected stations by the maintenance
    ///@note We consider the most affected the stations with the most difference of MaxTrainsArriveAtStation before - after the maintenance
    ///@note After a segment gets removed, we consider that a station can be considered temporarily as a starting station if its getSegments().size = 1 on 2.4) function
    ///@note Calls edmonskarp algortithm
    static void topK_mostaffected(int k);

    ///@brief Prints the minimum cost - maxflow between 2 stations
    ///@note Calls mincostflow from network
    static void minCostFlow();

    ///@brief Prints the cost of the maxflow between 2 stations
    ///@note Calls edmonskarp and getcost
    static void maxFlowCost();

    ///@brief Runs the interactive Cost Optimization submenu
    static void costSubmenu();
};


#endif
