#include <iostream>
#include "Cart.h"
#include "Product.h"

Cart::Cart() {}

// �Էµ� Product�� ������ ���� Cart�� ��´�.(���� ����)
Cart::Cart(Product * _product) {
	product.push_back(_product);
}

// �Էµ� Product�� ������ ���� Cart�� ��´�.(���� ����)
void Cart::add_product(Product * _product) {
	product.push_back(_product);
}

// �Էµ� Product�� ��ü�� �����ؼ� Cart�� ��´�.(���� ����)
void Cart::copy_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
}

// Cart�� ��� Product�� ������ ���� �����.(���� ����)
void Cart::pop_product(Product * _product) {
	for (std::size_t i = 0; i < product.size(); i++) {
		if (product[i] == _product) {
			product.erase(product.begin() + i);
		}
	}
}

// Cart�� ��� Product�� �����Ϳ� �� �����Ͱ� ����Ű�� ��ü�� �����.(���� ����)
void Cart::delete_product(Product * _product) {
	for (std::size_t i = 0; i < product.size(); i++) {
		if (product[i] == _product) {
			delete product[i];
			product.erase(product.begin() + i);
		}
	}
}

// �Էµ� Product ��ü�� Cart�� ������ �� �Էµ� Product ��ü�� �����.(���� ����, ���� ����)
void Cart::move_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
	delete _product;
}

// Cart�� ��� Product�� ������ ����Ѵ�.
void Cart::print_product() {
	std::cout << "------------------------------- C a r t -------------------------------\n";
	std::cout << "0.back\n\n";
	for (std::size_t i = 0; i < product.size(); i++)
		std::cout << i + 1 << '.' << product[i]->to_string() << "\n\n";
}

Product * Cart::get_product(std::int32_t index) const {
	return product[index];
}

std::vector<Product *> Cart::get_product_vector() const {
	return product;
}