#ifndef EVENT_H
#define EVENT_H 

#include "Order.h"


enum eventType {
    ORDER_ARRIVAL,
    PICKING_COMPLETE,
    PACKING_COMPLETE,
    QUALITY_CHECK_COMPLETE,
    SHIPPING_COMPLETE
};
class Event {
    private:
        double eventTime;
        eventType type;
        Order order;
    public:

        bool operator>(const Event& other) const{
            return eventTime > other.eventTime;
        };

        Event(double eventTime, eventType type, Order order);

        ~Event()=default;
        double getEventTime();
        eventType getEventType();
       const Order& getOrder();
};
#endif