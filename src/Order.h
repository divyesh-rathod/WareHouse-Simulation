
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
        
       
        mutable double pickingCompleteTime;
        mutable double qualityCheckCompleteTime;
        mutable double packingCompleteTime;

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
        
       
        void setPickingCompleteTime(double time) const;
        void setQualityCheckCompleteTime(double time) const;
        void setPackingCompleteTime(double time) const;
        
        
        double getPickingCompleteTime() const;
        double getQualityCheckCompleteTime() const;
        double getPackingCompleteTime() const;
};
 
#endif 