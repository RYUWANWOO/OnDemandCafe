#include "CliCustomer.h"
#include <iostream>

ostream & operator<<(ostream & os, const Recipe & recipe)
{
	os << "Coffee Name :"
		<< recipe.getCoffeeName()
		<< "\t\t"
		<< "Cost :"
		<< recipe.getCoffeePrice();
	return os;
}

ostream & operator<<(ostream & os, const Menu & menu)
{
	for (unsigned int i = 0; i < menu.size(); i++) {
		os << i << "."
			<< menu[i]
			<< endl;
	}
	return os;
}

OrderType::OrderType(const string & name, function<void(void)> func)
{
	m_name = name;
	m_func = func;
}

ostream & operator<<(ostream & os, OrderType & ot)
{
	os << ot.m_name;
	return os;
}

void CliCustomer::orderCommon() const
{
	cout << "�Ʒ� �޴� �� ���Ͻô� �� �������ּ���"
		<< endl
		<< m_cafe.getMenu();
	string order;
	getline(cin, order);
}

void CliCustomer::orderCustom() const
{
}

OrderType CliCustomer::askOrder() const
{
	cout << "���Ͻô� �ֹ���ĸ� �Է����ּ���("
		<< 0 << "~" << orderMap.size() - 1 << ")" << endl;
	for (auto orderOption : orderMap) {
		cout << orderOption.first << "." << orderOption.second << endl;
	}
	int inputOrder;
	cin >> inputOrder;
	return orderMap.at(inputOrder);
}

CliCustomer::CliCustomer(Cafe & cafe)
	:Customer(cafe),
	orderMap({ 
		{0, OrderType("COMMON", bind(&CliCustomer::orderCommon, this))},
		{1, OrderType("CUSTOM", bind(&CliCustomer::orderCustom, this))}
	})
{
}


CliCustomer::~CliCustomer()
{
}

void CliCustomer::run() {
	OrderType& orderType = askOrder();
	orderType.m_func();
}
