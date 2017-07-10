#pragma once
#include<iostream>
using namespace std;



class Report
{
public:
	Report(string exchange, string symbol, string side, double price, int quantity, int OrderId);
	string getExchange() { return Exchange; }
	string getSymbol() { return Symbol; }
	string getSide() { return Side; }
	double getPrice() { return Price; }
	int getQuantity() { return Quantity; }
	int getOrderId() { return OrderId; }
	~Report();

private:
	string Exchange;
	string Symbol;
	string Side;
	double Price;
	int Quantity;
	int OrderId;
};

Report::Report(string exchange, string symbol, string side, double price, int quantity, int orderid)
	:Exchange(exchange), Symbol(symbol), Side(side), Price(price), Quantity(quantity), OrderId(orderid)
{
}

Report::~Report()
{
}