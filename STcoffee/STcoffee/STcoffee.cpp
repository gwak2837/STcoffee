#include <iostream>
#include "BlockChain.h"
#include "Menu.h"
#include "Cart.h"
#include "FAQ.h"
#include "Favorite.h"
#include "MyInfo.h"
#include "Order.h"
#include "Product.h"
#include "FrontEndUI.h"
using namespace std;

int main()
{
	cout << "ST coffee\n";
	cout << "The Life is the coffee\n\n";
	cout << "Welcome. This is ST coffee. You can enjoy more benefits as you become a member.\n";

	string customer_name;
	cout << "Please input your name: ";
	cin >> customer_name;

	cout << "Loading...";
	FrontEndUI ui;
	Menu * menu = new Menu();
	Cart * cart = new Cart();
	Favorite * favorite = new Favorite();
	FAQ * faq = new FAQ();
	MyInfo * myinfo = new MyInfo(customer_name);
	Product * p;
	Order * order = NULL;

	string coffee_beans, size, addition, nickname;
	bool art, take_out;
	int16_t  sugar, ice, shot, temperature;
	int32_t click, menu_number;
	int64_t quantity;
	
MAIN:
	system("cls");
	ui.print_main();
	cin >> click;
	switch (click)
	{
	case (int32_t)_Main::exit:
		goto EXIT;
	case (int32_t)_Main::menu:
		goto MENU;
	case (int32_t)_Main::cart:
		goto CART;
	case (int32_t)_Main::favorite:
		goto FAVORITE;
	case (int32_t)_Main::FAQ:
		goto FAQ;
	case (int32_t)_Main::myinfo:
		goto MYINFO;
	default:
		cout << "\n\nPlease input again...\n";
		system("pause");
		goto MAIN;
	}

MENU:
	system("cls");
	ui.print_menu();
	cin >> click;
	switch (click)
	{
	case (int32_t)_Menu::back:
		goto MAIN;
	case (int32_t)_Menu::coffee:
		goto COFFEE;
	case (int32_t)_Menu::side_dish:
		goto SIDE_DISH;
	default:
		cout << "\n\nPlease input again...\n";
		system("pause");
		goto MENU;
	}

COFFEE:
	system("cls");
	menu->print_coffee_menu();
	cin >> menu_number;
	if (menu_number == 0)
		goto MENU;

	cout << "Size(string): ";
	cin >> size;
	cout << "Coffee beans(string): ";
	cin >> coffee_beans;
	cout << "Topping, whipping cream, syrup(string): ";
	cin >> addition;
	cout << "Sugar(0 ~ 100): ";
	cin >> sugar;
	cout << "Ice(0 ~ 100): ";
	cin >> ice;
	cout << "Shot(int): ";
	cin >> shot;
	cout << "Temperature(int): ";
	cin >> temperature;
	cout << "Cafe Art or not(1/0): ";
	cin >> art; 
	cout << "Take out(1/0): ";
	cin >> take_out;
	cout << "Quantity(int): ";
	cin >> quantity;

	cout << "\n\nCoffee Menu: " << menu->get_coffee_menu(menu_number - 1);
	cout << "\nSize: " << size;
	cout << "\nCoffee beans(string): " << coffee_beans;
	cout << "\nAddition: " << addition;
	cout << "\nSugar: " << sugar << '%';
	cout << "\nIce: " << ice << '%';
	cout << "\nShot: " << shot;
	cout << "\nTemperature: " << temperature << "`C";
	cout << "\nCafe art : " << ((art) ? "Art" : "X");
	cout << "\nTake out : " << ((take_out) ? "Take out" : "X");
	cout << "\nQuantity: " << quantity;
	cout << "\nTotal price: " << menu->get_coffee_price(menu_number - 1) * quantity;
	cout << "\n\nConfirm order?(1/0) ";
	cin >> click;

	if (click == 1) {
		p = new Product(menu->get_coffee_menu(menu_number-1), size, coffee_beans, addition, sugar, ice, shot, temperature, art, take_out, quantity, menu->get_coffee_price(menu_number-1));

		while (true) {
			system("cls");
			ui.print_your_order();
			cin >> click;
			switch (click)
			{
			case (int32_t)_YourOrder::cancel:
				delete p;
				goto COFFEE;
			case (int32_t)_YourOrder::order:
				if (order->new_order(myinfo, p))
					goto COFFEE;
				else
					continue;
			case (int32_t)_YourOrder::cart:
				cart->add_product(p);
				cout << "\nYour order is added to cart!";
				cout << "\nDo you want to go to cart? (1/0) ";
				cin >> click;
				if (click == 1)
					goto CART;
				else
					goto COFFEE;
			case (int32_t)_YourOrder::favorite:
				cout << "Your order's nickname: ";
				cin >> nickname;
				p->add_nickname(nickname);
				favorite->add_product(p);
				cout << "\nYour order is added to Favorite!";
				cout << "\nDo you want to go to Favorite? (1/0) ";
				cin >> click;
				if (click == 1)
					goto FAVORITE;
				else
					goto COFFEE;
			default:
				cout << "\n\nPlease input again...\n";
				system("pause");
				continue;
			}
		}
	}
	else
		goto COFFEE;

SIDE_DISH:
	system("cls");
	menu->print_side_dish_menu();
	cin >> menu_number;
	if (menu_number == 0)
		goto MENU;

	cout << "Size(string): ";
	cin >> size;
	cout << "Take out(1/0): ";
	cin >> take_out;
	cout << "Quantity(int): ";
	cin >> quantity;

	cout << "\n\nSide dish: " << menu->get_side_dish_menu(menu_number - 1);
	cout << "\nSize: " << size;
	cout << "\nTake out : " << ((take_out) ? "Take out" : "X");
	cout << "\nQuantity: " << quantity;
	cout << "\nTotal price: " << menu->get_side_dish_price(menu_number - 1) * quantity;
	cout << "\nConfirm order?(1/0) ";
	cin >> click;

	if (click == 1) {
		p = new Product(menu->get_side_dish_menu(menu_number-1), size, take_out, quantity, menu->get_side_dish_price(menu_number-1));

		while (true) {
			system("cls");
			ui.print_your_order();
			cin >> click;
			switch (click)
			{
			case (int32_t)_YourOrder::order:
				if (order->new_order(myinfo, p))
					goto SIDE_DISH;
				else
					continue;
			case (int32_t)_YourOrder::cancel:
				delete p;
				goto SIDE_DISH;
			case (int32_t)_YourOrder::cart:
				cart->add_product(p);
				cout << "Your order is added to cart!\n";
				cout << "Do you want to go to cart? (1/0) ";
				cin >> click;
				if (click == 1)
					goto CART;
				else
					goto SIDE_DISH;
			case (int32_t)_YourOrder::favorite:
				favorite->add_product(p);
				cout << "Your order is added to Favorite!\n";
				cout << "Do you want to go to Favorite? (1/0) ";
				cin >> click;
				if (click == 1)
					goto FAVORITE;
				else
					goto SIDE_DISH;
			default:
				cout << "\n\nPlease input again...\n";
				system("pause");
				continue;
			}
		}
	}
	else
		goto SIDE_DISH;

CART:
	system("cls");
	cart->print_product();
	cin >> click;
	if (click == 0)
		goto MAIN;
	
	while(true) {
		system("cls");
		p = cart->get_product(click-1);
		cout << "Selected: " << p->to_string() << '\n';
		ui.print_cart();
		cin >> click;
		switch (click)
		{
		case (int32_t)_Cart::back:
			goto CART;
		case (int32_t)_Cart::order:
			if(order->new_order(myinfo, cart->get_product(click-1)))
				cart->pop_product(p);
			goto CART;
		case (int32_t)_Cart::add_to_favorite:
			favorite->copy_product(p);
			cout << "Your order is added to favorite!\n";
			cout << "Do you want to go to favorite? (1/0) ";
			cin >> click;
			if (click == 1)
				goto FAVORITE;
			else
				goto CART;
		case (int32_t)_Cart::delete_from_cart:
			cart->delete_product(p);
			cout << "Your order is deleted from cart!\n";
			goto CART;
		case (int32_t)_Cart::go_to_favorite:
			goto FAVORITE;
		default:
			cout << "\n\nPlease input again...\n";
			system("pause");
			continue;
		}
	}

FAVORITE:
	system("cls");
	favorite->print_product();
	cin >> click;
	if (click == 0)
		goto MAIN;

	while (true) {
		system("cls");
		p = favorite->get_product(click-1);
		cout << "Selected: " << p->to_string() << '\n';
		ui.print_favorite();
		cin >> click;
		switch (click)
		{
		case (int32_t)_Favorite::back:
			goto FAVORITE;
		case (int32_t)_Favorite::add_to_cart:
			cart->copy_product(p);
			cout << "Your order is added to cart!\n";
			cout << "Do you want to go to cart? (1/0) ";
			cin >> click;
			if (click == 1)
				goto CART;
			else
				goto FAVORITE;
		case (int32_t)_Favorite::delete_from_favorite:
			favorite->delete_product(p);
			cout << "Your order is deleted from favorite!\n";
			goto FAVORITE;
		case (int32_t)_Favorite::go_to_cart:
			goto CART;
		default:
			cout << "\n\nPlease input again...\n";
			system("pause");
			continue;
		}
	}

FAQ:
	system("cls");
	faq->print_question();

	while (true) {
		cin >> click;
		if (click == 0)
			goto MAIN;

		faq->print_answer(click);
		system("pause");
	}

MYINFO:
	system("cls");
	ui.print_myinfo();
	cin >> click;
	switch (click)
	{
	case (int32_t)_MyInfo::back:
		goto MAIN;
	case (int32_t)_MyInfo::order_history:
		myinfo->get_blockchain()->print_all_order();
		system("pause");
		goto MYINFO;
	case (int32_t)_MyInfo::point:
		cout << "\nYour point: " << myinfo->get_point() << '\n';
		system("pause");
		goto MYINFO;
	case (int32_t)_MyInfo::your_name:
		cout << "\nYour name: " << myinfo->get_customer_name() << '\n';
		system("pause");
		goto MYINFO;
	default:
		cout << "\n\nPlease input again...\n";
		system("pause");
		goto MYINFO;
	}

EXIT:
	return 0;
}
