
#ifndef ORDER_H
#define ORDER_H 

enum orderPriority {
    NORMAL,
    HIGH
};

class Order {
    private:
        double arrivalTime;
        double pickingTime;
        double packingTime;
        double qualityCheckTime;
        double shippingTime;
        double orderPrice;
        orderPriority priority;

    public:
        Order(double arrivalTime, double pickingTime, double qualityCheckTime , double packingTime, double shippingTime, double orderPrice, orderPriority priority);

        ~Order()=default;
        double getArrivalTime() const;
        double getPickingTime() const;
        double getPackingTime() const;
        double getShippingTime() const;
        double getQualityCheckTime() const;
        double getOrderPrice() const;
        orderPriority getOrderPriority() const;
};

#endif 