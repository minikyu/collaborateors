#include<iostream>
using namespace std;

class Order
{
public:
	int Quantity;
	Order(int orderid, string side, string symbol, double price, int quantity);
	int get_orderid() { return OrderId; };
	string get_side() { return Side; };
	string get_symbol() { return Symbol; };
	double get_price() { return Price; };
	

private:
	int OrderId;
	string Side;
	string Symbol;
	double Price;
	

};

Order::Order(int orderid, string side, string symbol, double price, int quantity)
	: OrderId(orderid), Side(side), Symbol(symbol), Price(price), Quantity(quantity)
{}







