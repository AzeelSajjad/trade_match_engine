#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "order.hpp"

class OrderBook {
public:
    OrderBook();
    void addOrder(const Order &order);
    void removeOrder(int orderId);
    Order getBestBuy();
    Order getBestSell();
};

#endif 