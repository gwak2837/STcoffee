#include <iostream>
#include "MyInfo.h"
#include "BlockChain.h"

// 내부적으로 사용자의 주문 내역을 저장하는 블록체인을 생성함
MyInfo::MyInfo(std::string _customer_name) : customer_name(_customer_name), blockchain(new BlockChain()), point(0) { }

// 주문을 완료할 때마다 일정 포인트가 적립된다.
void MyInfo::add_point() {
	point += POINT_PER_ORDER;
}

// 포인트를 사용하면 그만큼 포인트가 차감된다.
void MyInfo::minus_point(std::int64_t applied_point) {
	point -= applied_point;
}

// 포인트를 정수 형태로 반환한다.
const std::int64_t MyInfo::get_point() const {
	return point;
}

// 포인트를 string 형태로 반환한다.
const std::string MyInfo::get_customer_name() const {
	return customer_name;
}

BlockChain * MyInfo::get_blockchain() const {
	return blockchain;
}