#include "matching_engine.hpp"
#include "order.hpp"
#include "order_book.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool MatchingEngine::processOrder(const Order& order){
    if(order.side == OrderSide::BUY){
        const auto& orders = orderBook.getBestSell();
        
    } else if (order.side == OrderSide::SELL){
        
    }
}