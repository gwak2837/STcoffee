#include <iostream>
#include "Favorite.h"
#include "Product.h"

Favorite::Favorite() {}

// 입력된 Product의 포인터 값만 Favorite에 담는다.(얕은 복사)
Favorite::Favorite(Product * _product) {
	product.push_back(_product);
}

// 입력된 Product의 포인터 값만 Favorite에 담는다.(얕은 복사)
void Favorite::add_product(Product *_product) {
	product.push_back(_product);
}

// 입력된 Product의 객체를 복사해서 Favorite에 담는다.(깊은 복사)
void Favorite::copy_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
}

// 입력된 Product 객체를 Favorite로 복사한 후 입력된 Product 객체를 지운다.(깊은 복사, 깊은 삭제)
void Favorite::move_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
	delete _product;
}

// Favorite에 담긴 Product의 포인터와 그 포인터가 가리키는 객체도 지운다.(깊은 삭제)
void Favorite::delete_product(Product * _product) {
	for (std::size_t i = 0; i < product.size(); i++) {
		if (product[i] == _product) {
			delete product[i];
			product.erase(product.begin() + i);
		}
	}
}

// Favorite에 담긴 Product의 내용을 출력한다.
void Favorite::print_product() {
	std::cout << "------------------------------- F a v o r i t e -------------------------------\n";
	std::cout << "0.back\n\n";
	for (std::size_t i = 0; i < product.size(); i++)
		std::cout << i + 1 << '.' << product[i]->to_string() << "\n\n";
}

// 입력된 index에 따른 Product 포인터를 반환한다.
Product * Favorite::get_product(std::int32_t index) const {
	return product[index];
}

