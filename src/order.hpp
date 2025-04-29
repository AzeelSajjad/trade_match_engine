#pragma once 

enum class OrderSide {
    BUY,
    SIDE
};

struct Order {
    int orderId;
    double price;
    int quantity;
    OrderSide side;
    long timestamp;
};