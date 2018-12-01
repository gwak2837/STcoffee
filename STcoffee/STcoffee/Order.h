#pragma once
#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <vector>
#include <cstdint>
#include <ctime>

class Product;
class MyInfo;

// transaction of blockchain
class Order {
	friend class Block;

	std::string orderer_name;                  // 고객 이름
	static const std::string store_name;       // 가게 이름
	static const std::string store_location;   // 가게 위치
	static const std::string phone_number;     // 가게 연락처
	time_t timestamp;                          // 주문한 시각
	std::string payment_method;                // 결제 수단
	std::vector<Product *> product;            // 결제한 상품들
	std::int64_t vat;                          // 부가가치세
	std::int64_t discount;                     // 포인트, 쿠폰 등 할인
	std::int64_t total_amount;                 // 상품들의 총 금액
	
	Order(std::string orderer_name, std::string payment_method, std::vector<Product *> product, std::int64_t discount);

public:
	bool new_order(MyInfo * myinfo, Product * product);
	bool new_order(MyInfo * myinfo, std::vector<Product *> product_vector);

	void print();
	void print_detail();
	void print_hash();

	time_t get_timestamp();
	void set_timestamp();
};

#endif // !ORDER_H
