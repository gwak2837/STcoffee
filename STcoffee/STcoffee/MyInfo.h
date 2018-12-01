#pragma once
#ifndef MYINFO_H
#define MYINFO_H
#define POINT_PER_ORDER 100  // �ֹ� 1�Ǵ� ����Ʈ ����
#include <string>
#include <cstdint>

class BlockChain;

class MyInfo {
	std::string customer_name; // �� �̸�
	std::int64_t point;        // �ֹ��� �Ϸ�� ������ ���� ����Ʈ ����
	BlockChain * blockchain;   // �ֹ� ����� �����ϴ� ��

public:
	MyInfo(std::string _customer_name); // ���������� ������� �ֹ� ������ �����ϴ� ���ü���� ������
	
	void add_point();                   // ���� ����Ʈ ����
	void minus_point(std::int64_t applied_point);
	const std::int64_t get_point() const;
	const std::string get_customer_name() const;
	BlockChain * get_blockchain() const;
};


#endif // !MYINFO_H



