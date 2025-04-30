#include "order_book.hpp"
#include "order.hpp"

#include <map>         
#include <vector>      
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

OrderBook::OrderBook() {
}

void OrderBook::addOrder(const Order &order){
    if(order.side == OrderSide::BUY){
        buyOrders[order.price].push_back(order);
    }
    if(order.side == OrderSide::SELL){
        sellOrders[order.price].push_back(order);
    }
    orderIdToPrice[order.orderId] = {order.price, order.side};
}

void OrderBook::removeOrder(int orderId){
    auto it = orderIdToPrice.find(orderId);
    if(it != orderIdToPrice.end()){
        double price = it->second.first;
        OrderSide side = it->second.second;
        if(side == OrderSide::BUY){
            auto& orders = buyOrders[price];
            auto orderIt = find_if(orders.begin(), orders.end(), [orderId](const Order& o) {
                return o.orderId == orderId;
            });
            if(orderIt != orders.end()){
                orders.erase(orderIt);
                if(orders.empty()){
                    buyOrders.erase(price);
                }
            }
        } else if(side == OrderSide::SELL) {
            auto& orders = sellOrders[price];
            auto orderIt = find_if(orders.begin(), orders.end(), [orderId](const Order& o) {
                return o.orderId == orderId;
            });
            if(orderIt != orders.end()){
                orders.erase(orderIt);
                if(orders.empty()){
                    sellOrders.erase(price);
                }
            }
        }
    }
    orderIdToPrice.erase(orderId);
}

vector<Order> OrderBook::getBestBuy(){
    vector<Order> result;
    if(buyOrders.empty()){
        cout << "Error: No buy orders available." << endl;
        return result;
    }
    return buyOrders.rbegin()->second;
}

vector<Order> OrderBook::getBestSell(){
    vector<Order> result;
    if(sellOrders.empty()){
        cout << "Error: No sell orders available." << endl;
        return result;
    }
    return sellOrders.begin()->second;
}