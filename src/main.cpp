#include <iostream>
#include <chrono>
#include "matching_engine.hpp"
#include "order.hpp"

long getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count();
    return millis;
}

void printOrder(const Order& order) {
    std::cout << "Order ID: " << order.orderId 
              << ", Side: " << (order.side == OrderSide::BUY ? "BUY" : "SELL")
              << ", Price: " << order.price
              << ", Quantity: " << order.quantity
              << std::endl;
}

int main() {
    MatchingEngine engine;
    int nextOrderId = 1;
    
    std::cout << "=== Trading Engine Demo ===" << std::endl;
    std::cout << "Adding initial orders to the book..." << std::endl;
    
    Order buy1 = {nextOrderId++, 100.0, 10, OrderSide::BUY, getCurrentTimestamp()};
    engine.processOrder(buy1);
    std::cout << "Added: "; printOrder(buy1);
    
    Order buy2 = {nextOrderId++, 101.0, 5, OrderSide::BUY, getCurrentTimestamp()};
    engine.processOrder(buy2);
    std::cout << "Added: "; printOrder(buy2);
    
    Order sell1 = {nextOrderId++, 103.0, 7, OrderSide::SELL, getCurrentTimestamp()};
    engine.processOrder(sell1);
    std::cout << "Added: "; printOrder(sell1);
    
    Order sell2 = {nextOrderId++, 102.0, 3, OrderSide::SELL, getCurrentTimestamp()};
    engine.processOrder(sell2);
    std::cout << "Added: "; printOrder(sell2);
    
    std::cout << "\nProcessing matching orders..." << std::endl;
    
    Order matchingBuy = {nextOrderId++, 102.0, 2, OrderSide::BUY, getCurrentTimestamp()};
    std::cout << "New order: "; printOrder(matchingBuy);
    engine.processOrder(matchingBuy);
    std::cout << "Order processed - should have matched with sell order at price 102.0" << std::endl;
    
    Order matchingSell = {nextOrderId++, 101.0, 3, OrderSide::SELL, getCurrentTimestamp()};
    std::cout << "New order: "; printOrder(matchingSell);
    engine.processOrder(matchingSell);
    std::cout << "Order processed - should have matched with buy order at price 101.0" << std::endl;
    
    std::cout << "\nDemonstration complete." << std::endl;
    return 0;
}