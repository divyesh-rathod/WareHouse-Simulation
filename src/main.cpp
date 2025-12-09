#include "Simulation.h"
#include "iostream"
#include <fstream>
#include "Order.h"

#include "vector"
#include "queue"

using namespace std;

int main(int argc, char* argv[]) {
    int pickers, packers, shippers, qualityChekers =0;
    ifstream inputFile(argv[1]);
    inputFile >> pickers>>qualityChekers>>packers>>shippers;
    int totalOrders = 0;
    inputFile >> totalOrders;
    Simulation WareHouse(pickers,qualityChekers,packers,shippers);
    double arrivalTime, pickingTime, packingTime, qualityControTime, shippingTime, price = 0.0;
    int priorityValue = 0;
    for (int i = 0; i < totalOrders;i++){
        inputFile >> arrivalTime >> pickingTime >> packingTime >> qualityControTime >> shippingTime >> price >> priorityValue;
        orderPriority priority = (priorityValue == 1) ? HIGH : NORMAL;
        Order newOrder(arrivalTime, pickingTime, qualityControTime, packingTime, shippingTime, price, priority);
        WareHouse.addOrder(newOrder);
    }

    WareHouse.run();
    return 0;
};
