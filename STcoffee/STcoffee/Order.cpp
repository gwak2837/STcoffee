#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Product.h"
#include "Order.h"
#include "MyInfo.h"
#include "BlockChain.h"

const std::string Order::store_name = "ST coffee";
const std::string Order::store_location = "Chung-Ang Univ main store";
const std::string Order::phone_number = "010-1234-5678";

// 주문을 받으면 Product로부터 금액을 얻어 세금이랑 총 금액을 계산한다.
Order::Order(std::string _orderer_name, std::string _payment_method, std::vector<Product *> _product, std::int64_t _discount)
	: orderer_name(_orderer_name), payment_method(_payment_method), product(_product), discount(_discount) {

	// Product로부터 금액을 받아와 total_amount에 저장한다.
	total_amount = 0;
	std::size_t product_size = product.size();
	for (std::size_t i = 0; i < product_size; i++)
		total_amount += product[i]->get_amount();
	
	// 전체 금액에서 할인 금액을 뺀 후 세금을 계산한다. 총 금액 = 공급가액 + 세금(공급가액의 10%)
	total_amount -= discount;
	vat = total_amount / 11;
}

// Product가 1개이면 vector에 넣는다. 주문이 발생하면 true, 중간에 취소하면 false를 반환한다.
bool Order::new_order(MyInfo * _myinfo, Product * _product) {
	std::vector<Product *> product_vector;
	product_vector.push_back(_product);
	return new_order(_myinfo, product_vector);
}

// Product vector를 받아서 계산, 주문을 완료한다. 주문이 발생하면 true, 중간에 취소하면 false를 반환한다.
bool Order::new_order(MyInfo * _myinfo, std::vector<Product *> _product_vector) {
	std::string payment_method;
	Order * order;
	std::int32_t click;
	std::int64_t applied_point;

	while (true) {
		std::cout << "------------------------------- C h e c k o u t -------------------------------";
		std::cout << "\nPayment method(string): ";
		std::cin >> payment_method;

		std::cout << "\n\nYour point: " + std::to_string(_myinfo->get_point());
		std::cout << "\nApply your point(int): ";
		std::cin >> applied_point;

		// 있는 포인트보다 더 사용하면 최대 포인트를 사용한다.
		if (applied_point > _myinfo->get_point()) {
			std::cout << "\nThe value you entered is more than the point you have. \nYour maximum point(" << std::to_string(_myinfo->get_point()) << ") will be applied.\n";
			applied_point = _myinfo->get_point();
			system("pause");
		}

		// 사용자가 입력한 정보를 바탕으로 주문을 생성한다.
		order = new Order(_myinfo->get_customer_name(), payment_method, _product_vector, applied_point);

		system("cls");
		order->set_timestamp();
		order->print_detail();
		std::cout << "Do you want to place your orders? \t 1.Yes \t 2.Cancel order \t 3.Write again\n";
		std::cin >> click;

		// 최종 주문을 확인하면 포인트 차감, 주문일시 생성, 블록체인에 저장, 포인트 적립을 진행한다.
		switch (click) {
		case 1:
			_myinfo->minus_point(applied_point);
			order->set_timestamp();
			_myinfo->get_blockchain()->add_order_to_blockchain(order);
			_myinfo->add_point();
			std::cout << "Your orders have been placed!\n";
			system("pause");
			return true;
		case 2: 
			delete order;
			return false;
		case 3:
			delete order;
			system("cls");
			continue;
		default:
			std::cout << "Please input again...\n";
			system("pause");
		}
	}
}

// 해싱한 데이터만(가게이름, 위치, 주문자, 상품(예외), 총 금액, 결제수단) 출력
void Order::print() {
	std::cout << "\nStore name: " << store_name << "\nStore location: " << store_location << "\nCustomer's name: " << orderer_name;
	
	struct tm tstruct;
	char order_time[80];
	tstruct = *localtime(&timestamp);
	strftime(order_time, sizeof(order_time), "%Y-%m-%d %X", &tstruct);
	std::cout << "\nOrder time: " << order_time;

	for (std::size_t i = 0; i < product.size(); i++) {
		std::cout << "\n--------------------------------" << product[i]->to_string();
	}
	std::cout << "\n--------------------------------";
	std::cout << "\nTotal amount : " << total_amount << "\nPayment method : " << payment_method;
	std::cout << "\n\n";
}

// order의 모든 정보 출력
void Order::print_detail() {
	std::cout << "------------------------------- O r d e r  D e t a i l -------------------------------\n";
	std::cout << "\nStore name: " << store_name << "\nStore location: " << store_location << "\nCustomer's name: " << orderer_name;
	std::cout << "\nStore phone number: " << phone_number;
	
	struct tm tstruct;
	char order_time[80];
	tstruct = *localtime(&timestamp);
	strftime(order_time, sizeof(order_time), "%Y-%m-%d %X", &tstruct);
	std::cout << "\nOrder time: " << order_time;

	for (std::size_t i = 0; i < product.size(); i++) {
		std::cout << "\n--------------------------------" << product[i]->to_string();
	}

	// 계산 방식 수정 필요
	std::cout << "\nDiscount: (-)" << discount<< "\n\nSupplied value: " << total_amount - vat << "\nValue Added Tax(VAT) : " << vat;
	std::cout << "\nTotal amount : " << total_amount << "\n--------------------------------" << "\nPayment method: " << payment_method;
	std::cout << "\n\n";
}
	
void Order::print_hash() {

}

time_t Order::get_timestamp() {
	return timestamp;
}

void Order::set_timestamp() {
	timestamp = time(NULL);
}