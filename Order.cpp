#include "Order.h"

Order::Order(double arrivalTime, double pickingTime, double packingTime, double qualityCheckTime, double shippingTime, double orderPrice, orderPriority priority) 
: 
                                                                                                                            arrivalTime(arrivalTime),
                                                                                                                            pickingTime(pickingTime),
                                                                                                                            packingTime(packingTime),
                                                                                                                            qualityCheckTime(qualityCheckTime),
                                                                                                                            shippingTime(shippingTime),
                                                                                                                            orderPrice(orderPrice) 
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


