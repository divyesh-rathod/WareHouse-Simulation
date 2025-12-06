#include "Simulation.h"
#include "iostream"


using namespace std;

Simulation::Simulation(int pickers, int packers, int shippers, int qualityChekers)
    :pickers(pickers),packers(packers),shippers(shippers),qualityChekers(qualityChekers),
    current_time(0.0)
     {
         
      };


void Simulation ::addOrder(const Order& order){
    double arrivalTIme = order.getArrivalTime();
    Event arrivalEvent(arrivalTIme, ORDER_ARRIVAL, order);
    eventQueue.push(arrivalEvent);
}

void Simulation::run(){
  while (!eventQueue.empty()){
      auto current_event = eventQueue.top();
      current_time = current_event.getEventTime();
      eventQueue.pop();
      
      auto order = current_event.getOrder();
      cout << "Time " << current_time << ": ";
      
      switch (current_event.getEventType())
      {
        
      case ORDER_ARRIVAL:
          cout << "Order arrives (Priority=" << (order.getOrderPriority() == HIGH ? "HIGH" : "NORMAL") 
               << ", Price=$" << order.getOrderPrice() << ")" << endl;
          handelArrival(current_event.getOrder());
      break;


      case PICKING_COMPLETE:
            cout << "Picking complete (Priority=" << (order.getOrderPriority() == HIGH ? "HIGH" : "NORMAL") 
                 << ", Price=$" << order.getOrderPrice() << ")" << endl;
            handelPickup(current_event.getOrder());
      break;


      case QUALITY_CHECK_COMPLETE:
               cout << "Quality check complete (Priority=" << (order.getOrderPriority() == HIGH ? "HIGH" : "NORMAL") 
                    << ", Price=$" << order.getOrderPrice() << ")" << endl;
               handelQualityCheck(current_event.getOrder());
      break;


      case PACKING_COMPLETE:
               cout << "Packing complete (Priority=" << (order.getOrderPriority() == HIGH ? "HIGH" : "NORMAL") 
                    << ", Price=$" << order.getOrderPrice() << ")" << endl;
               handelPacking(current_event.getOrder());
      break;


      case SHIPPING_COMPLETE:
              cout << "Shipping complete (Priority=" << (order.getOrderPriority() == HIGH ? "HIGH" : "NORMAL") 
                   << ", Price=$" << order.getOrderPrice() << ")" << endl;
              handelShipping(current_event.getOrder());
      break;
      
      }
  }
  printStats();
}

void Simulation::handelArrival(const Order &order) {
  if(pickers>0){
      pickers--;
      auto pickUpCompleteTime = order.getPickingTime() + current_time;
      Event QualityCheck(pickUpCompleteTime, PICKING_COMPLETE, order);
      eventQueue.push(QualityCheck);
  }
  else{
      pickerQueue.push(order);
  }
};

void Simulation :: handelPickup(const Order& order ){
    if(qualityChekers>0){
        qualityChekers--;
        auto QualityCheckCompleteTime = order.getQualityCheckTime() + current_time;
        Event Packing(QualityCheckCompleteTime, QUALITY_CHECK_COMPLETE, order);
        eventQueue.push(Packing);
    }
    else{
        qualityChekerQueue.push(order);
    }
    pickers++;
    freeLastPicker();
};

void Simulation ::handelQualityCheck(const Order &order) {
 if(packers>0){
     packers--;
     auto PackingCompleteTime = order.getPackingTime() + current_time;
     Event Shiping(PackingCompleteTime, PACKING_COMPLETE, order);
     eventQueue.push(Shiping);
 }
 else{
     packerQueue.push(order);
 }
 qualityChekers++;
 freeLastQualityCheker();
};

void Simulation :: handelPacking(const Order& order){
    if(shippers>0){
         shippers--;
         auto ShippingCompleteTime = order.getShippingTime() + current_time;
         Event FinalDelevery(ShippingCompleteTime, SHIPPING_COMPLETE, order);
         eventQueue.push(FinalDelevery);
    }
    else{
        shipperQueue.push(order);
    }
    packers++;
    freeLastPacker();
};

void Simulation ::handelShipping( const Order& order){
    shippers++;
    while(!shipperQueue.empty() && shippers>0){
        shippers--;
        auto newOrder = shipperQueue.top();
        shipperQueue.pop();
        auto time = newOrder.getShippingTime() + current_time;
        Event FinalDelevery(time, SHIPPING_COMPLETE, newOrder);
         eventQueue.push(FinalDelevery); 

    }
}

void Simulation ::freeLastPicker() {
  while (!pickerQueue.empty() && pickers>0)
  {
      pickers--;
      auto newOrder = pickerQueue.front();
      pickerQueue.pop();
      auto time = newOrder.getPickingTime() + current_time;
      Event PicupCompleteEvent(time, PICKING_COMPLETE, newOrder);
      eventQueue.push(PicupCompleteEvent);
  }
  
};

void Simulation :: freeLastQualityCheker(){
    while (!qualityChekerQueue.empty() && qualityChekers>0)
    {
        qualityChekers--;
        auto newOrder = qualityChekerQueue.front();
        qualityChekerQueue.pop();
        auto time = newOrder.getQualityCheckTime() + current_time;
        Event QualityCheckComplete(time, QUALITY_CHECK_COMPLETE, newOrder);
        eventQueue.push(QualityCheckComplete);
    }
    
}


void Simulation :: freeLastPacker(){
    while(!packerQueue.empty() && packers>0){
        packers--;
        auto newOrder = packerQueue.front();
        packerQueue.pop();
        auto time = newOrder.getPackingTime() + current_time;
        Event Shipping(time, PACKING_COMPLETE, newOrder);
        eventQueue.push(Shipping);
    }
}



void Simulation :: printStats(){
    cout << " " << "Total no of Pickers" << pickers << endl;
    cout << " " << "Total no of packers"<<packers<< endl;
    cout << " " << "Total no of qualityChekers"<<qualityChekers << endl;
    cout << " " << "Total no of shippers"<<shippers<< endl;
    cout << " " << "Total time to deliver the last good"<<" "<<current_time << endl;
}