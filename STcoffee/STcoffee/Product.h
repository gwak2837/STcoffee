#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <cstdint>

class Menu;

class Product {
	std::string name;
	std::string size;
	std::string coffee_beans;
	std::string addition;
	std::string nickname;
	std::int16_t sugar;
	std::int16_t ice;
	std::int16_t shot;
	std::int16_t temperature;
	bool art;
	bool take_out;
	std::int64_t quantity;
	std::int64_t unit_price;
	std::int64_t amount;

	Menu * menu;
	
public:
	// for coffee product
	Product(std::string name, std::string size, std::string coffee_beans, std::string addition, std::int16_t sugar, std::int16_t ice, 
		std::int16_t shot, std::int16_t temparature, bool art, bool take_out, std::int64_t quantity, std::int64_t unit_price);
	// for side dish product
	Product(std::string name, std::string size, bool take_out, std::int64_t quantity, std::int64_t unit_price);

	void add_nickname(std::string nickname);
	const std::int64_t get_amount();
	const std::string to_string();
};

#endif // !PRODUCT_H




