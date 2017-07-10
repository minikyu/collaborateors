#pragma once
#include<iostream>
using namespace std;

class Book
{
public:
	Book(string symbol, string side);
	void set_NYSE(int size, double price);
	void set_NASDAQ(int size, double price);
	void set_IEX(int size, double price);



private:
	string Symbol;
	string Side;
	int NYSE_size = 0;
	double NYSE_price = 0;
	int NASDAQ_size = 0;
	double NASDAQ_price = 0;
	int IEX_size = 0;
	double IEX_price = 0;
};

Book::Book(string symbol, string side)
	:Symbol(symbol), Side(side)
{
}

void Book::set_NYSE(int size, double price)
{
	NYSE_size = size;
	NYSE_price = price;

}

void Book::set_NASDAQ(int size, double price)
{
	NASDAQ_size = size;
	NASDAQ_price = price;
}

void Book::set_IEX(int size, double price)
{ 
	IEX_size = size; 
	IEX_price = price;
}