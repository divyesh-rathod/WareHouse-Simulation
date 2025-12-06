#include "Event.h"
#include  "Order.h"
#include <queue>
#include <vector>
using namespace std;

#ifndef SIMULATION_H
#define SIMULATION_H

// Custom comparator for shipping queue
// Prioritizes by: 1) HIGH priority first, 2) Higher price first
struct ShippingComparator {
    bool operator()(const Order& a, const Order& b) const {
        // If priorities differ, NORMAL has lower priority (should wait)
        if (a.getOrderPriority() != b.getOrderPriority()) {
            return a.getOrderPriority() < b.getOrderPriority();
        }
        // Same priority: lower price waits (higher price first)
        return a.getOrderPrice() < b.getOrderPrice();
    }
};

//   ORDER_ARRIVAL,
//     PICKING_COMPLETE,
//     PACKING_COMPLETE,
//     QUALITY_CHECK_COMPLETE,
//     SHIPPING_COMPLETE

class Simulation {
      private:
          int pickers,packers,qualityChekers,shippers;
          double current_time;

          priority_queue<Event, vector<Event>, greater<Event>> eventQueue;
          queue<Order> pickerQueue;
          queue<Order> packerQueue;
          queue<Order> qualityChekerQueue;
          priority_queue<Order, vector<Order>, ShippingComparator> shipperQueue;

          void handelArrival(const Order& order );
          void handelPickup(const Order& order);
          void handelQualityCheck(const Order& order);
          void handelPacking(const Order& order);
          void handelShipping(const Order& order);
          void handelDilevery(const Order& order);
          void printStats();
          void freeLastPicker();
          void freeLastPacker();
          void freeLastQualityCheker();
          void freeLastShipper();

      public:
          Simulation(int pickers, int qualityChekers, int packers , int shippers);
          ~Simulation() = default;
          void run();
          void addOrder(const Order &order);

};

#endif