#include <iostream>
#include "MyInfo.h"
#include "BlockChain.h"

// ���������� ������� �ֹ� ������ �����ϴ� ���ü���� ������
MyInfo::MyInfo(std::string _customer_name) : customer_name(_customer_name), blockchain(new BlockChain()), point(0) { }

// �ֹ��� �Ϸ��� ������ ���� ����Ʈ�� �����ȴ�.
void MyInfo::add_point() {
	point += POINT_PER_ORDER;
}

// ����Ʈ�� ����ϸ� �׸�ŭ ����Ʈ�� �����ȴ�.
void MyInfo::minus_point(std::int64_t applied_point) {
	point -= applied_point;
}

// ����Ʈ�� ���� ���·� ��ȯ�Ѵ�.
const std::int64_t MyInfo::get_point() const {
	return point;
}

// ����Ʈ�� string ���·� ��ȯ�Ѵ�.
const std::string MyInfo::get_customer_name() const {
	return customer_name;
}

BlockChain * MyInfo::get_blockchain() const {
	return blockchain;
}