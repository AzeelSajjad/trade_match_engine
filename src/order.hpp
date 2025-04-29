#pragma once 

enum class OrderSide {
    BUY,
    SELL
};

struct Order {
    int orderId;
    double price;
    int quantity;
    OrderSide side;
    long timestamp;
};