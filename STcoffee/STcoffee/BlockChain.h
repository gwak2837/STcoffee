#pragma once
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <cstdint>

class Block;
class Order;

class BlockChain {
	const Block * genesis_block;        // 첫번째 블록
	const Block * last_block;           // 마지막 블록
	Block * waiting_block;              // 블록체인에 포함되기 위해 검증을 기다리는 블록(아직 검증되지 않은 블록)
	static std::uint64_t num_of_block;  // 블록의 총 개수

	void add_block_to_blockchain(Block * _block);

public:
	BlockChain();
	BlockChain(Order * _order);

	void add_order_to_blockchain(Order * _order);
	const Order * get_order(time_t _order_timestamp) const;
	void print_all_order();

	// functions for saving this blockchain to computer
	void save_order();
	void load_order();

	// functions for test
	void print_all_blockhash();
	void print_all_orderhash();
	const Block * get_genesis_block() const;
	const Block * get_last_block() const;
	std::uint64_t get_num_of_block() const;
};

#endif // !BLOCKCHAIN_H




