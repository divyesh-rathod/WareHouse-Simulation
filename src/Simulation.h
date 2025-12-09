#include "Event.h"
#include  "Order.h"
#include <queue>
#include <vector>
using namespace std;

#ifndef SIMULATION_H
#define SIMULATION_H

struct ShippingComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.getOrderPriority() != b.getOrderPriority()) {
            return a.getOrderPriority() < b.getOrderPriority();
        }
       
        return a.getOrderPrice() < b.getOrderPrice();
    }
};



class Simulation {
      private:
          int pickers,packers,qualityChekers,shippers;
          int originalPickers, originalPackers, originalQualityChekers, originalShippers;
          double current_time;

          priority_queue<Event, vector<Event>, greater<Event>> eventQueue;
          queue<Order> pickerQueue;
          queue<Order> packerQueue;
          queue<Order> qualityChekerQueue;
          priority_queue<Order, vector<Order>, ShippingComparator> shipperQueue;

      
          double pickerIdleTime, packerIdleTime, qualityCheckerIdleTime, shipperIdleTime;
          int maxPickerQueueLength, maxPackerQueueLength, maxQualityCheckerQueueLength, maxShipperQueueLength;
          int totalOrdersProcessed;
          double totalPickerWaitTime, totalPackerWaitTime, totalQualityCheckerWaitTime, totalShipperWaitTime;

          void handelArrival(const Order& order );
          void handelPickup(const Order& order);
          void handelQualityCheck(const Order& order);
          void handelPacking(const Order& order);
          void handelShipping(const Order& order);
          void printStats();
          void freeLastPicker();
          void freeLastPacker();
          void freeLastQualityCheker();
          void updateQueueStats();

      public:
          Simulation(int pickers, int qualityChekers, int packers , int shippers);
          ~Simulation() = default;
          void run();
          void addOrder(const Order &order);

};

#endif