#pragma once
#include<iostream>
using namespace std;



class Quote
{
public:
	int Size;
	Quote(string exchange, string side, string symbol, int size, double price);
	string get_exchange() { return Exchange; };
	string get_side() { return Side; };
	string get_symbol() { return Symbol; };
	int get_size() { return Size; };
	double get_price() { return Price; };

private:
	string Exchange;
	string Side;
	string Symbol;
	double Price;
};


Quote::Quote(string exchange, string side, string symbol, int size, double price)
	:Exchange(exchange), Side(side), Symbol(symbol), Size(size), Price(price)
{}



