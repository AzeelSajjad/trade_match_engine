#include "matching_engine.hpp"
#include "order.hpp"
#include "order_book.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

MatchingEngine::MatchingEngine() {
}

bool MatchingEngine::processOrder(Order order) {
    bool shouldAddToBook = true; 
    if (order.side == OrderSide::BUY) {
        vector<Order> bestSellOrders = orderBook.getBestSell();
        if (!bestSellOrders.empty() && bestSellOrders[0].price <= order.price) {
            for (auto& sellOrder : bestSellOrders) {
                int fillAmount = min(sellOrder.quantity, order.quantity);
                if (fillAmount > 0) {
                    sellOrder.quantity -= fillAmount;
                    order.quantity -= fillAmount;
                    if (sellOrder.quantity == 0) {
                        orderBook.removeOrder(sellOrder.orderId);
                    }
                    if (order.quantity == 0) {
                        shouldAddToBook = false;
                        break;
                    }
                }
            }
        }
    } 
    else if (order.side == OrderSide::SELL) {
        vector<Order> bestBuyOrders = orderBook.getBestBuy();
        if (!bestBuyOrders.empty() && bestBuyOrders[0].price >= order.price) {
            for (auto& buyOrder : bestBuyOrders) {
                int fillAmount = min(buyOrder.quantity, order.quantity);
                if (fillAmount > 0) {
                    buyOrder.quantity -= fillAmount;
                    order.quantity -= fillAmount;
                    if (buyOrder.quantity == 0) {
                        orderBook.removeOrder(buyOrder.orderId);
                    }
                    if (order.quantity == 0) {
                        shouldAddToBook = false;
                        break;
                    }
                }
            }
        }
    }
    if (shouldAddToBook && order.quantity > 0) {
        orderBook.addOrder(order);
    }
    
    return true;
}