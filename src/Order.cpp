#include "Order.h"

Order::Order(double arrivalTime, double pickingTime, double packingTime, double qualityCheckTime, double shippingTime, double orderPrice, orderPriority priority) 
: 
                                                                                                                            arrivalTime(arrivalTime),
                                                                                                                            pickingTime(pickingTime),
                                                                                                                            packingTime(packingTime),
                                                                                                                            qualityCheckTime(qualityCheckTime),
                                                                                                                            shippingTime(shippingTime),
                                                                                                                            orderPrice(orderPrice),
                                                                                                                            priority(priority),
                                                                                                                            pickingCompleteTime(0),
                                                                                                                            qualityCheckCompleteTime(0),
                                                                                                                            packingCompleteTime(0)
                                                                                                                            {  };

double Order::getArrivalTime() const {
    return arrivalTime;
};

double Order::getPickingTime()const {
    return pickingTime;
};
double Order::getPackingTime()const{
    return packingTime;
};
double Order::getShippingTime()const{
    return shippingTime;
};
double Order::getQualityCheckTime()const{
    return qualityCheckTime;
};
double Order::getOrderPrice()const{
    return orderPrice;
};


orderPriority Order::getOrderPriority()const{
    return priority;
};


void Order::setPickingCompleteTime(double time) const {
    pickingCompleteTime = time;
}

void Order::setQualityCheckCompleteTime(double time) const {
    qualityCheckCompleteTime = time;
}

void Order::setPackingCompleteTime(double time) const {
    packingCompleteTime = time;
}

double Order::getPickingCompleteTime() const {
    return pickingCompleteTime;
}

double Order::getQualityCheckCompleteTime() const {
    return qualityCheckCompleteTime;
}

double Order::getPackingCompleteTime() const {
    return packingCompleteTime;
}


