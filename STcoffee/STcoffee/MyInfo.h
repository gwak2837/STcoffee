#pragma once
#ifndef MYINFO_H
#define MYINFO_H
#define POINT_PER_ORDER 100  // 주문 1건당 포인트 적립
#include <string>
#include <cstdint>

class BlockChain;

class MyInfo {
	std::string customer_name; // 고객 이름
	std::int64_t point;        // 주문이 완료될 때마다 일정 포인트 적립
	BlockChain * blockchain;   // 주문 기록을 저장하는 곳

public:
	MyInfo(std::string _customer_name); // 내부적으로 사용자의 주문 내역을 저장하는 블록체인을 생성함
	
	void add_point();                   // 일정 포인트 적립
	void minus_point(std::int64_t applied_point);
	const std::int64_t get_point() const;
	const std::string get_customer_name() const;
	BlockChain * get_blockchain() const;
};


#endif // !MYINFO_H



