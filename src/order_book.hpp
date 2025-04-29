#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

class OrderBook {
public:
    OrderBook();
    void addOrder();
    void removeOrder();
    void getBestBuy();
    void getBestSell();
};

#endif 