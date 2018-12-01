#pragma once
#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <cstdint>

class Menu {
	static std::vector<std::string> coffee_menu;
	static std::vector<std::int64_t> coffee_price;
	static std::vector<std::string> coffee_beans_menu;
	static std::vector<std::int64_t> coffee_beans_price;
	static std::vector<std::string> addition_menu;
	static std::vector<std::int64_t> addition_price;
	static std::vector<std::string> size_menu;
	static std::vector<std::int64_t> size_price;
	static std::int64_t shot_price;
	static std::vector<std::string> side_dish_menu;
	static std::vector<std::int64_t> side_dish_price;

public:
	Menu();

	void add_coffee_menu(std::string new_coffee, std::int64_t price);
	void add_side_dish_menu(std::string new_side_dish, std::int64_t price);
	void print_coffee_menu();
	void print_side_dish_menu();
	const std::string get_coffee_menu(std::int32_t index) const;
	const std::int64_t get_coffee_price(std::int32_t index) const;
	const std::string get_side_dish_menu(std::int32_t index) const;
	const std::int64_t get_side_dish_price(std::int32_t index) const;

};


#endif // !MENU_H



