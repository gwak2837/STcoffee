#include <iostream>
#include "Menu.h"

std::vector<std::string> Menu::coffee_menu = { "Americano", "Espresso", "Cappuccino", "Cafe Latte", "Cafe Mocha", "Hot Choco", "Milk Tea", "Grapefruit Ade", "Sweet Potato Latte" };
std::vector<std::int64_t> Menu::coffee_price = { 1500, 1000, 2000, 2000, 2500, 2500, 3000, 3000, 3000 };
std::vector<std::string> coffee_beans_menu = { "Brazil Santos", "Kenya AA" };
std::vector<std::int64_t> coffee_beans_price = { 0, 0 };
std::vector<std::string> addition_menu = { "Caramel syrup" };
std::vector<std::int64_t> addition_price = { 300 };
std::vector<std::string> size_menu = { "M", "L", "J" };
std::vector<std::int64_t> size_price = { 0, 500, 1000 };
std::int64_t shot_price = 300;
std::vector<std::string> Menu::side_dish_menu = { "Honey Bread", "Sandwitch", "Brownie", "Macaroon", "Mango Mousse Cake" };
std::vector<std::int64_t> Menu::side_dish_price = { 3000, 2000, 4000, 2000, 4000 };

// �޴����̿� ���ݱ��̰� �������� Ȯ���Ѵ�.
Menu::Menu() {
	if (coffee_menu.size() != coffee_price.size())
		std::cout << "Warning: Size of coffee menu and coffee price are different!";
	if (side_dish_menu.size() != side_dish_price.size())
		std::cout << "Warning: Size of side dish menu and side dish price are different!";
}

// ��Ÿ�ӿ� Ŀ�� �޴��� ������ �߰��Ѵ�.
void Menu::add_coffee_menu(std::string new_coffee, std::int64_t price) {
	coffee_menu.push_back(new_coffee);
	coffee_price.push_back(price);
}

// ��Ÿ�ӿ� ���̵��� �޴��� ������ �߰��Ѵ�.
void Menu::add_side_dish_menu(std::string new_side_dish, std::int64_t price) {
	side_dish_menu.push_back(new_side_dish);
	side_dish_price.push_back(price);
}

// Ŀ�� �޴��� ��� ����Ѵ�.
void Menu::print_coffee_menu() {
	std::cout << "------------------------------- C o f f e e -------------------------------\n";
	std::cout << "0.back\n";
	std::size_t size = coffee_menu.size();
	for (std::size_t i = 0; i < size; i++)
		std::cout << i + 1 << '.' << coffee_menu[i] << " \t\t " << coffee_price[i] << " KRW\n";
	std::cout << '\n';
}

// ���̵��� �޴��� ��� ����Ѵ�.
void Menu::print_side_dish_menu() {
	std::cout << "------------------------------- S i d e D i s h -------------------------------\n";
	std::cout << "0.back\n";
	std::size_t size = side_dish_menu.size();
	for (std::size_t i = 0; i < size; i++)
		std::cout << i + 1 << '.' << side_dish_menu[i] << " \t\t " << side_dish_price[i] << " KRW\n";
	std::cout << '\n';
}

const std::string Menu::get_coffee_menu(std::int32_t index) const {
	return coffee_menu[index];
}

const std::int64_t Menu::get_coffee_price(std::int32_t index) const {
	return coffee_price[index];
}

const std::string Menu::get_side_dish_menu(std::int32_t index) const {
	return side_dish_menu[index];
}

const std::int64_t Menu::get_side_dish_price(std::int32_t index) const {
	return side_dish_price[index];
}
