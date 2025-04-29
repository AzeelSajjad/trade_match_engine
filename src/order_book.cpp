#include "order_book.hpp"
#include "order.hpp"

#include <map>         
#include <vector>      
#include <iostream>
using namespace std;

void OrderBook::addOrder(const Order &order){
    if(order.side == OrderSide::BUY){
        buyOrders.insert({});
    }
};