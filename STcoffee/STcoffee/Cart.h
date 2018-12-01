#pragma once
#ifndef CART_H
#define CART_H
#include <vector>
#include <cstdint>

class Product;

class Cart {
	std::vector<Product *> product;  // Cart에 담기는 product 벡터(리스트)

public:
	Cart();
	Cart(Product * _product);
	
	void add_product(Product * product);
	void copy_product(Product * product);
	void pop_product(Product * product);
	void delete_product(Product * product);
	void move_product(Product * product);
	void print_product();
	Product * get_product(std::int32_t index) const;
	std::vector<Product *> get_product_vector() const;
};

#endif // !CART_H


