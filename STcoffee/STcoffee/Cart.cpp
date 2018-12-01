#include <iostream>
#include "Cart.h"
#include "Product.h"

Cart::Cart() {}

// 입력된 Product의 포인터 값만 Cart에 담는다.(얕은 복사)
Cart::Cart(Product * _product) {
	product.push_back(_product);
}

// 입력된 Product의 포인터 값만 Cart에 담는다.(얕은 복사)
void Cart::add_product(Product * _product) {
	product.push_back(_product);
}

// 입력된 Product의 객체를 복사해서 Cart에 담는다.(깊은 복사)
void Cart::copy_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
}

// Cart에 담긴 Product의 포인터 값만 지운다.(얕은 삭제)
void Cart::pop_product(Product * _product) {
	for (std::size_t i = 0; i < product.size(); i++) {
		if (product[i] == _product) {
			product.erase(product.begin() + i);
		}
	}
}

// Cart에 담긴 Product의 포인터와 그 포인터가 가리키는 객체도 지운다.(깊은 삭제)
void Cart::delete_product(Product * _product) {
	for (std::size_t i = 0; i < product.size(); i++) {
		if (product[i] == _product) {
			delete product[i];
			product.erase(product.begin() + i);
		}
	}
}

// 입력된 Product 객체를 Cart로 복사한 후 입력된 Product 객체를 지운다.(깊은 복사, 깊은 삭제)
void Cart::move_product(Product * _product) {
	Product * copy_product = new Product(*_product);
	product.push_back(copy_product);
	delete _product;
}

// Cart에 담긴 Product의 내용을 출력한다.
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