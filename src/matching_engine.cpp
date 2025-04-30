#include "matching_engine.hpp"
#include "order.hpp"
#include "order_book.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool MatchingEngine::processOrder(Order order) {
    if (order.side == OrderSide::BUY) {
        vector<Order> orders = orderBook.getBestSell(); 
        for (auto& o : orders) {
            if (o.price <= order.price) {
                int fillAmount = min(o.quantity, order.quantity);
                o.quantity -= fillAmount;
                order.quantity -= fillAmount;
                if (o.quantity == 0) {
                    orderBook.removeOrder(o.orderId);
                }
                if (order.quantity == 0) {
                    orderBook.removeOrder(order.orderId);
                    break;
                }
            }
        }
        if (order.quantity > 0) {
            orderBook.addOrder(order);
        }
        return true;
    } else if (order.side == OrderSide::SELL) {
        vector<Order> orders = orderBook.getBestBuy();
        for (auto& o : orders) {
            if(o.price >= order.price){
                int fillAmount = min(o.quantity, order.quantity);
                o.quantity -= fillAmount;
                order.quantity -= fillAmount;
                if(o.quantity == 0){
                    orderBook.removeOrder(o.orderId);
                }
                if(order.quantity == 0){
                    orderBook.removeOrder(order.orderId);
                    break;
                }
            }
        }
        if(order.quantity > 0) {
            orderBook.addOrder(order);
        }
        return true;
    }
    return false;
}