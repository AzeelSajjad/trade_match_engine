#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "order.hpp"
#include <map>
#include <vector>

class OrderBook {
public:
    OrderBook();
    void addOrder(const Order &order);
    void removeOrder(int orderId);
    const vector<Order>& getBestBuy() const;
    const vector<Order>& getBestSell() const;
private:
    map<double, vector<Order>> buyOrders;
    map<double, vector<Order>> sellOrders;
    map<int, pair<double, OrderSide>> orderIdToPrice;
};

#endif 