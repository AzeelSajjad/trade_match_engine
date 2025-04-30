#include "order_book.hpp"
#include "order.hpp"

#include <map>         
#include <vector>      
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

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

Order OrderBook::getBestBuy(){
    if(buyOrders.empty()){
        fprintf(stderr, "Error: No buy orders available.\n");
        return Order{-1, 0.0, 0, OrderSide::BUY, 0};
    }
    auto& bestOrders = buyOrders.rbegin()->second;
    if(bestOrders.empty()){
        fprintf(stderr, "Error: Empty order vector at the best price.\n");
        return Order{-1, 0.0, 0, OrderSide::BUY, 0};
    }
    return bestOrders[0];
}

Order OrderBook::getBestSell(){
    if(sellOrders.empty()){
        fprintf(stderr, "Error: No sell orders available.\n");
        return Order{-1, 0.0, 0, OrderSide::SELL, 0};
    }
    auto& bestOrders = sellOrders.begin()->second;
     if(bestOrders.empty()){
        fprintf(stderr, "Error: Empty order vector at the lowest price.\n");
        return Order{-1, 0.0, 0, OrderSide::SELL, 0};
    }
    return bestOrders[0];
}