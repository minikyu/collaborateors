#include"orders.h"
#include"quotes.h"
#include"report.h"
#include"some_functions.h"
#include"level1_book.h"
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
//#include<algorithm>
#include<map>



/*
function get_order is for homework1 to construct order
*/
vector<Order> get_order()
{
	//cout << "Input the adress of orders file:";
	string orders_file = "E:\\C++\\MS\\FW_ MS\\Orders.csv";
	//cin >> orders_file;
	ifstream orders(orders_file);
	string order;
	vector<Order> order_box;

	orders >> order;
	while (orders >> order)
	{
		int first_point, second_point, third_point, forth_point;

		//--------------orderid------------
		first_point = order.find(',');
		int orderid = str_to_int(order.substr(0, first_point));

		order = order.substr(first_point + 1);
		//--------------side---------------
		second_point = order.find(',');
		string side = order.substr(0, second_point);

		order = order.substr(second_point + 1);
		//--------------symbol-------------
		third_point = order.find(',');
		string symbol = order.substr(0, third_point);

		order = order.substr(third_point + 1);
		//--------------price--------------
		forth_point = order.find(',');
		double price = str_to_dou(order.substr(0, forth_point));

		order = order.substr(forth_point + 1);
		//-------------quantity-------------
		int quantity = str_to_int(order);

		//========creat Orders==============
		order_box.push_back(Order(orderid, side, symbol, price, quantity));
	}

	return order_box;
}

/*
function get_quote is for homework1 to constrict quote
*/
vector<Quote> get_quote()
{
	//cout << "Input the adress of quotes file:";
	string quotes_file = "E:\\C++\\MS\\FW_ MS\\Quotes.csv";
	//cin >> quotes_file;
	ifstream quotes(quotes_file);
	string quote;
	vector<Quote> quote_box;

	quotes >> quote;
	while (quotes >> quote)
	{
		int first_point, second_point, third_point, forth_point;

		//--------------exchange------------
		first_point = quote.find(',');
		string exchange = quote.substr(0, first_point);

		quote = quote.substr(first_point + 1);
		//--------------side---------------
		second_point = quote.find(',');
		string side = quote.substr(0, second_point);

		quote = quote.substr(second_point + 1);
		//--------------symbol-------------
		third_point = quote.find(',');
		string symbol = quote.substr(0, third_point);

		quote = quote.substr(third_point + 1);
		//--------------size--------------
		forth_point = quote.find(',');
		int size = str_to_int(quote.substr(0, forth_point));

		quote = quote.substr(forth_point + 1);
		//-------------price-------------
		double price = str_to_dou(quote);

		//========creat Orders==============
		quote_box.push_back(Quote(exchange, side, symbol, size, price));
	}

	return quote_box;
}


/*
this functiom is for homework2
*/
int Aggressive_take()
{
	//******get orders and quotes*******
	vector<Order> order_box = get_order();
	vector<Quote> quote_box = get_quote();

	//*****the report*******************
	vector<Report> report_box;

	//************ read quotes ****************
	int quote_box_size = quote_box.size();
	for (int i = 0; i < quote_box_size; i++)
	{
		string quote_symbol = quote_box[i].get_symbol();
		string quote_exchange = quote_box[i].get_exchange();
		int quote_size = quote_box[i].get_size();
		double quote_price = quote_box[i].get_price();
		//=========================================

		if (quote_box[i].get_side() == "Bid")
		{
			//********  check all the current orders one by one *************  
			for (Order &order : order_box)
			{
				if (quote_size > 0)
				{
					if (order.get_side() == "Sell" && order.get_symbol() == quote_symbol && order.get_price() <= quote_price)
					{
						if (order.Quantity - quote_size > 0)
						{
							report_box.push_back(Report(quote_exchange, quote_symbol, order.get_side(), quote_price, quote_size, order.get_orderid()));
							order.Quantity = order.Quantity - quote_size;
							quote_size = 0;

						}
						else if (order.Quantity - quote_size == 0)
						{
							report_box.push_back(Report(quote_exchange, quote_symbol, order.get_side(), quote_price, quote_size, order.get_orderid()));
							quote_size = 0;
							order.Quantity = 0;
							vector<Order>::iterator it = order_box.begin();
							for (; it != order_box.end(); it++)
							{
								if (it->Quantity == 0)
								{
									order_box.erase(it);
								}
							}
						}
						else
						{
							report_box.push_back(Report(quote_exchange, quote_symbol, order.get_side(), quote_price, order.Quantity, order.get_orderid()));
							quote_size = quote_size - order.Quantity;
							order.Quantity = 0;
							vector<Order>::iterator it = order_box.begin();
							for (; it != order_box.end(); it++)
							{
								if (it->Quantity == 0)
								{
									order_box.erase(it);
								}
							}
						}

					}
				}
				else { break; }
			}
		}

		else
		{
			//********  check all the current orders one by one *************
			for (Order &order : order_box)
			{
				if (quote_size > 0)
				{
					if (order.get_side() == "Buy" && order.get_symbol() == quote_symbol && order.get_price() >= quote_price)
					{
						if (order.Quantity - quote_size > 0)
						{
							report_box.push_back(Report(quote_exchange, quote_symbol, order.get_side(), quote_price, quote_size, order.get_orderid()));
							order.Quantity = order.Quantity - quote_size;
							quote_size = 0;
						}
						else if (order.Quantity - quote_size == 0)
						{
							report_box.push_back(Report(quote_exchange, quote_symbol, order.get_side(), quote_price, quote_size, order.get_orderid()));
							quote_size = 0;
							order.Quantity = 0;
							vector<Order>::iterator it = order_box.begin();
							for (; it != order_box.end(); it++)
							{
								if (it->Quantity == 0)
								{
									order_box.erase(it);
								}
							}

						}
						else
						{
							report_box.push_back(Report(quote_exchange, quote_symbol, order.get_side(), quote_price, order.Quantity, order.get_orderid()));
							quote_size = quote_size - order.Quantity;
							order.Quantity = 0;
							vector<Order>::iterator it = order_box.begin();
							for (; it != order_box.end(); it++)
							{
								if (it->Quantity == 0)
								{
									order_box.erase(it);
								}
							}
						}
					}
				}
				else { break; }
			}
		}
	}


	//**** get information from report***********
	map<string, int> exchange_quantity;
	map<string, double> exchange_sum_price;
	map<int, int> order_quantity;
	map<int, double> order_sum_price;

	for (Report & report : report_box)
	{
		order_quantity[report.getOrderId()] += report.getQuantity();
		order_sum_price[report.getOrderId()] += report.getPrice()*report.getQuantity();
		exchange_quantity[report.getExchange()] += report.getQuantity();
		exchange_sum_price[report.getExchange()] += report.getPrice()*report.getQuantity();
	}


	//**********print report*************************************
	map<string, int>::iterator iter1 = exchange_quantity.begin();
	for (; iter1 != exchange_quantity.end(); iter1++)
	{
		cout << "Exchange:" << iter1->first << "\t\t"
			<< "quantity:" << iter1->second << "\t\t"
			<< "average price:" << exchange_sum_price[iter1->first] / iter1->second
			<< endl;
	}
	map<int, int>::iterator iter2;
	for (iter2 = order_quantity.begin(); iter2 != order_quantity.end(); iter2++)
	{
		cout << "OrderId:" << iter2->first << "\t\t"
			<< "quantity:" << iter2->second << "\t\t"
			<< "average price:" << order_sum_price[iter2->first] / iter2->second
			<< endl;
	}
	keep_window_open();
	return 0;
}

/*
int Passive_placement()
{
	//******get orders and quotes*******
	vector<Order> order_box = get_order();
	vector<Quote> quote_box = get_quote();

	//******set level book**************
	Book Bid_AAPL("AAPL", "Bid");
	Book Ask_AAPL("AAPL", "Ask");
	Book Bid_GOOG("GOOG", "Bid");
	Book Ask_GOOG("GOOG", "Ask");

	//********* read order ***************
	for (Order &order : order_box)
	{
		if (order.get_side() == "Buy")
		{
			for (Quote &quote : quote_box)
			{
				if (quote.get_side() == "Bid")
				{
					if (quote.get_symbol() == "AAPL")
					{
						if (quote.get_exchange() == "NYSE")
						{
							Bid_AAPL.set_NYSE(quote.get_size(), quote.get_price());
						}
						else if (quote.get_exchange() == "NASDAQ")
						{
							Bid_AAPL.set_NASDAQ(quote.get_size(), quote.get_price());
						}
						else
						{
							Bid_AAPL.set_IEX(quote.get_size(), quote.get_price());
						}
					}
					else
					{
						if (quote.get_exchange() == "NYSE")
						{
							Bid_GOOG.set_NYSE(quote.get_size(), quote.get_price());
						}
						else if (quote.get_exchange() == "NASDAQ")
						{
							Bid_GOOG.set_NASDAQ(quote.get_size(), quote.get_price());
						}
						else
						{
							Bid_GOOG.set_IEX(quote.get_size(), quote.get_price());
						}
					}
				}
				else
				{
					if (order.get_symbol() == "AAPL")
					{
						if (order.)
						{

						}
					}
				}
			}
		}
	}

}

*/


int main()
{
	Aggressive_take();
	return 0;
}