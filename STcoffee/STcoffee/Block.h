#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#define MAX_ORDER_COUNT 1             // �� ��Ͽ� �� �� �ִ� �ִ� order�� ����
#include <vector>
#include <string>
#include <cstdint>
#include <ctime>

class Order;

class Block {
	friend class BlockChain;

	BYTE blockhash[32];               // Block�� ID
	static const std::string version; // BlockChain �̸�
	const Block * previous_block;     // ���� ���
	BYTE orderhash[32];               // ���� order �ؽð����� ���� ��ŬƮ��(�ؽ�Ʈ��)�� ��Ŭ��Ʈ
	time_t timestamp;                 // ����� ���ü�ο� ���ε� �ð�
	static BYTE bits;                 // blockhash �տ� ���;� �� 0�� ����
	std::int64_t nonce;               // ���� ���� ��
	std::vector<Order *> order;       // ����ڷκ��� ���� order��

	// Block class �ȿ����� ����ϴ� �޼ҵ�
	void build_merkletree(std::vector<BYTE *> order_vector1, std::vector<BYTE *> order_vector2) const;
	void copy_merkleroot(std::vector<BYTE *> order_vector);
	void hashing_blockheader();
	void hashing_each_order(std::vector<BYTE *> * orderhash_vector) const;

	// BlockChain class������ ����ϴ� �޼ҵ�
	Block(const Block * _previous_block);
	void add_order_to_block(Order * _order);
	void update_orderhash();
	void mining();
	bool is_valid_block() const;
	bool is_valid_order() const;
	bool is_full_of_orders() const;
	
	const BYTE * get_blockhash() const;
	const Block * get_previous_block() const;
	const BYTE * get_orderhash() const;
	time_t get_timestamp() const;
	std::vector<Order *> get_order() const;
};

#endif // !BLOCK_H



