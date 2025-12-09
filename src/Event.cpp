#include "Event.h"

Event::Event(double eventTime, eventType type, Order order) 
: eventTime(eventTime),
  type(type),
  order(order) 
  {  };

double Event::getEventTime(){
    return eventTime;
};

eventType Event::getEventType(){
    return type;
};

const Order& Event::getOrder(){
    return order;
};

