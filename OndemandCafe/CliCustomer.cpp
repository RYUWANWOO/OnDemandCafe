#include "CliCustomer.h"
#include <iostream>
#include <iomanip>

ostream & operator<<(ostream & os, const Ingredient & ingredient)
{
		os.setf(ios::left);
		os<<setw(30)
		 << ingredient.getName()
		 << setw(3)
		 << "Unit Price : "
		<< ingredient.getUnitPrice();
	return os;
}

ostream & operator<<(ostream & os, const RecipeData & recipeData) 
{
	const Ingredient& ingredient = recipeData.getIngredient();

	os.setf(ios::left);
	os << setw(30)
	 << ingredient.getName()
		<< "Amount : "
		<< setw(3)
		<< recipeData.getAmount();
	return os;
}

ostream & operator<<(ostream & os, const Recipe & recipe)
{
	cout << setw(35);
	os << recipe.getCoffeeName()
		<< "Price :"
		<< recipe.getCoffeePrice();
	return os;
}

ostream & operator<<(ostream & os, const Menu & menu)
{
	for (unsigned int i = 0; i < menu.size(); i++) {
		os << i << ". "
			<< menu[i]
			<< endl;
	}
	return os;
}

ostream & operator<<(ostream & os, const Coffee & coffee)
{
	os << setw(10);
	os << "Coffee Name: "
		<< setw(25)
		<< coffee.getName()
		
		<< "Price :"
		<< setw(20)
		<< coffee.getPrice();

	return os;
}

ostream & operator<<(ostream & os, const IngredientList& ingredients)
{
	os << "< Ingredient List >"
		<< endl
		<< endl;
	for (unsigned int i = 0; i < ingredients.size(); i++) {
		os << i << ". "
			<< ingredients[i]
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
	cout << "�Ʒ� �޴� �� ���Ͻô� �� �������ּ���" << endl;
	cout << "=================================================="<<endl;
	cout << " <  Menu  >" << endl<<endl;
	cout.setf(ios::left);
	cout <<m_cafe.getMenu()<< endl;
	int order;
	cin >> order;
	cout << endl<<m_cafe.orderMenu(order) << endl<<endl;;
}

void CliCustomer::orderCustom() const
{
	vector<RecipeData> data;
	const IngredientList& ingredients = m_cafe.getIngredientList();
	int order;
	Amount amount;
	while (true) {
		cout << "������ ��Ḧ ������"
			<< endl
			<< "============================================================"
			<< endl
			<< ingredients
			<< endl
			<< ingredients.size()
		
			<< ". ���� ������"
			<< endl;
		cin >> order;
		if (order == ingredients.size()) break;
		cout << "������ ���� ��������" << endl;
		cin >> amount;
		cout << "===========================================================" << endl;
		data.push_back(RecipeData(ingredients[order], amount));
		cout << "���ݱ��� ���յ� ����Ʈ" << endl;
		for (unsigned int i = 0; i < data.size(); i++) {
			cout << data[i] << endl;
		}
	}
	Coffee& coffee = m_cafe.orderCustom(data);
	if (coffee.getName() == "") {
		cout << "�̸��� �����ðڽ��ϱ�?(Y/n) : ";
		char c;
		cin >> c;
		if (tolower(c) == 'y') {
			cout << "���ο� �޴��� �̸��� �Է����ּ��� : ";
			cin.ignore();
			string name;
			getline(cin, name);
			Recipe recipe(name, data);
			m_cafe.getMenu().addMenuItem(recipe);
			coffee.setName(name);
		}
	}
	cout << coffee << endl;
}

void CliCustomer::exit()
{
	cout << "Good Bye" << endl;
	bAgain = false;
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
		{0, OrderType("Common", bind(&CliCustomer::orderCommon, this))},
		{1, OrderType("Custom", bind(&CliCustomer::orderCustom, this))},
		{2, OrderType("Exit", bind(&CliCustomer::exit, this))}
		}),
	bAgain(true)
{
}


CliCustomer::~CliCustomer()
{
}

void CliCustomer::run() {
	while (bAgain) {
		OrderType& orderType = askOrder();
		orderType.m_func();
	}
}
