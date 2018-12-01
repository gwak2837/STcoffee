#pragma once
#ifndef FAVORITE_H
#define FAVORITE_H
#include <vector>
#include <cstdint>

class Product;

class Favorite {
	std::vector<Product *> product;  // Favorite에 담기는 product 벡터(리스트)

public:
	Favorite();
	Favorite(Product * _product);

	void add_product(Product *_product);
	void copy_product(Product * product);
	void delete_product(Product * _product);
	void move_product(Product * product);
	void print_product();
	Product * get_product(std::int32_t index) const;
};

#endif // !FAVORITE_H



