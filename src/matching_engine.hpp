#pragma once

#include "order.hpp"
#include "order_book.hpp"

class MatchingEngine {
public:
    MatchingEngine();
    bool processOrder(Order order);

private:
    OrderBook orderBook;
};