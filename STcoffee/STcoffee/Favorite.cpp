#include <iostream>
#include "Favorite.h"
#include "Product.h"

Favorite::Favorite() {}

// �Էµ� Product�� ������ ���� Favorite�� ��´�.(���� ����)
Favorite::Favorite(Product * _product) {
	product.push_back(_product);
}

// �Էµ� Product�� ������ ���� Favorite�� ��´�.(���� ����)
void Favorite::add_product(Product *_product) {
	product.push_back(_product);
}

// �Էµ� Product�� ��ü�� �����ؼ� Favorite�� ��´�.(���� ����)
void Favorite::copy_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
}

// �Էµ� Product ��ü�� Favorite�� ������ �� �Էµ� Product ��ü�� �����.(���� ����, ���� ����)
void Favorite::move_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
	delete _product;
}

// Favorite�� ��� Product�� �����Ϳ� �� �����Ͱ� ����Ű�� ��ü�� �����.(���� ����)
void Favorite::delete_product(Product * _product) {
	for (std::size_t i = 0; i < product.size(); i++) {
		if (product[i] == _product) {
			delete product[i];
			product.erase(product.begin() + i);
		}
	}
}

// Favorite�� ��� Product�� ������ ����Ѵ�.
void Favorite::print_product() {
	std::cout << "------------------------------- F a v o r i t e -------------------------------\n";
	std::cout << "0.back\n\n";
	for (std::size_t i = 0; i < product.size(); i++)
		std::cout << i + 1 << '.' << product[i]->to_string() << "\n\n";
}

// �Էµ� index�� ���� Product �����͸� ��ȯ�Ѵ�.
Product * Favorite::get_product(std::int32_t index) const {
	return product[index];
}

