#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#define MAX_ORDER_COUNT 1             // 한 블록에 들어갈 수 있는 최대 order의 개수
#include <vector>
#include <string>
#include <cstdint>
#include <ctime>

class Order;

class Block {
	friend class BlockChain;

	BYTE blockhash[32];               // Block의 ID
	static const std::string version; // BlockChain 이름
	const Block * previous_block;     // 이전 블록
	BYTE orderhash[32];               // 개별 order 해시값으로 만든 머클트리(해시트리)의 머클루트
	time_t timestamp;                 // 블록이 블록체인에 승인된 시각
	static BYTE bits;                 // blockhash 앞에 나와야 할 0의 개수
	std::int64_t nonce;               // 임의 대입 수
	std::vector<Order *> order;       // 사용자로부터 받은 order들

	// Block class 안에서만 사용하는 메소드
	void build_merkletree(std::vector<BYTE *> order_vector1, std::vector<BYTE *> order_vector2) const;
	void copy_merkleroot(std::vector<BYTE *> order_vector);
	void hashing_blockheader();
	void hashing_each_order(std::vector<BYTE *> * orderhash_vector) const;

	// BlockChain class에서도 사용하는 메소드
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



