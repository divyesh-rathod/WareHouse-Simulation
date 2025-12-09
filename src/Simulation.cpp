#include "Simulation.h"
#include "iostream"


using namespace std;

Simulation::Simulation(int pickers, int qualityChekers,int packers, int shippers )
    :pickers(pickers),packers(packers),shippers(shippers),qualityChekers(qualityChekers),
    originalPickers(pickers), originalPackers(packers), originalShippers(shippers), originalQualityChekers(qualityChekers),
    current_time(0.0),
    pickerIdleTime(0.0), packerIdleTime(0.0), qualityCheckerIdleTime(0.0), shipperIdleTime(0.0),
    maxPickerQueueLength(0), maxPackerQueueLength(0), maxQualityCheckerQueueLength(0), maxShipperQueueLength(0),
    totalOrdersProcessed(0),
    totalPickerWaitTime(0.0), totalPackerWaitTime(0.0), totalQualityCheckerWaitTime(0.0), totalShipperWaitTime(0.0)
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
      
      
      double timeDelta = current_event.getEventTime() - current_time;
      if (timeDelta > 0) {
          pickerIdleTime += pickers * timeDelta;
          qualityCheckerIdleTime += qualityChekers * timeDelta;
          packerIdleTime += packers * timeDelta;
          shipperIdleTime += shippers * timeDelta;
      }
      
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
              totalOrdersProcessed++;
              handelShipping(current_event.getOrder());
      break;
      
      }
      
      updateQueueStats();
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
   
    order.setPickingCompleteTime(current_time);
    
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
 order.setQualityCheckCompleteTime(current_time);
 
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
    
    order.setPackingCompleteTime(current_time);
    
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
    
        totalShipperWaitTime += (current_time - newOrder.getPackingCompleteTime());
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
      // Calculate wait time: current_time (when worker became available) - arrival time
      totalPickerWaitTime += (current_time - newOrder.getArrivalTime());
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
 
        totalQualityCheckerWaitTime += (current_time - newOrder.getPickingCompleteTime());
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

        totalPackerWaitTime += (current_time - newOrder.getQualityCheckCompleteTime());
        auto time = newOrder.getPackingTime() + current_time;
        Event Shipping(time, PACKING_COMPLETE, newOrder);
        eventQueue.push(Shipping);
    }
}

void Simulation::updateQueueStats() {
    if (pickerQueue.size() > maxPickerQueueLength) maxPickerQueueLength = pickerQueue.size();
    if (packerQueue.size() > maxPackerQueueLength) maxPackerQueueLength = packerQueue.size();
    if (qualityChekerQueue.size() > maxQualityCheckerQueueLength) maxQualityCheckerQueueLength = qualityChekerQueue.size();
    if (shipperQueue.size() > maxShipperQueueLength) maxShipperQueueLength = shipperQueue.size();
}

void Simulation :: printStats(){
    cout << "\n========== SIMULATION RESULTS ==========" << endl;
    cout << "Total time to complete all orders: " << current_time << endl;
    cout << "Total orders processed: " << totalOrdersProcessed << endl;
    

    
    double totalPickerTime = originalPickers * current_time;
    double totalQCTime = originalQualityChekers * current_time;
    double totalPackerTime = originalPackers * current_time;
    double totalShipperTime = originalShippers * current_time;
    
    double pickerUtilization = totalPickerTime > 0 ? ((totalPickerTime - pickerIdleTime) / totalPickerTime * 100) : 0;
    double qcUtilization = totalQCTime > 0 ? ((totalQCTime - qualityCheckerIdleTime) / totalQCTime * 100) : 0;
    double packerUtilization = totalPackerTime > 0 ? ((totalPackerTime - packerIdleTime) / totalPackerTime * 100) : 0;
    double shipperUtilization = totalShipperTime > 0 ? ((totalShipperTime - shipperIdleTime) / totalShipperTime * 100) : 0;
    
    cout << "Pickers - Idle time: " << pickerIdleTime << " / Utilization: " << pickerUtilization << "% (" << originalPickers << " workers)" << endl;
    cout << "Quality Checkers - Idle time: " << qualityCheckerIdleTime << " / Utilization: " << qcUtilization << "% (" << originalQualityChekers << " workers)" << endl;
    cout << "Packers - Idle time: " << packerIdleTime << " / Utilization: " << packerUtilization << "% (" << originalPackers << " workers)" << endl;
    cout << "Shippers - Idle time: " << shipperIdleTime << " / Utilization: " << shipperUtilization << "% (" << originalShippers << " workers)" << endl;
    
    cout << "\n--- Bottleneck Analysis (Max Queue Lengths) ---" << endl;
    cout << "Picker Queue: " << maxPickerQueueLength << endl;
    cout << "Quality Checker Queue: " << maxQualityCheckerQueueLength << endl;
    cout << "Packer Queue: " << maxPackerQueueLength << endl;
    cout << "Shipper Queue: " << maxShipperQueueLength << endl;
    
    cout << "\n--- Average Wait Times ---" << endl;
    if (totalOrdersProcessed > 0) {
        cout << "Avg wait for Picker: " << (totalPickerWaitTime / totalOrdersProcessed) << endl;
        cout << "Avg wait for Quality Checker: " << (totalQualityCheckerWaitTime / totalOrdersProcessed) << endl;
        cout << "Avg wait for Packer: " << (totalPackerWaitTime / totalOrdersProcessed) << endl;
        cout << "Avg wait for Shipper: " << (totalShipperWaitTime / totalOrdersProcessed) << endl;
    }
    cout << "========================================\n" << endl;
}