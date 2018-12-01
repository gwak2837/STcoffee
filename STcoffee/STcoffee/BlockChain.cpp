#include <iostream>
#include "KISA_SHA256.h"
#include "BlockChain.h"
#include "Block.h"
#include "Order.h"

std::uint64_t BlockChain::num_of_block = 0;

// Genesis block을 생성한다.
BlockChain::BlockChain() {
	Block * _genesis_block = new Block(NULL); // blockchain 생성 -> genesis block 생성
	_genesis_block->get_order().reserve(MAX_ORDER_COUNT);
	genesis_block = _genesis_block;
	waiting_block = _genesis_block;
	last_block = NULL;
}

// Genesis block을 생성하고 그 블록에 order를 추가한다.
BlockChain::BlockChain(Order * _order) {
	BlockChain();
	waiting_block->add_order_to_block(_order);
}

// BlockChain 내부함수를 호출해 자동으로 order를 블록에 넣어주는 함수이다.
void BlockChain::add_order_to_blockchain(Order * _order) {
	waiting_block->add_order_to_block(_order); // waiting block에 order 추가

	// waiting block의 order가 꽉차면
	if (waiting_block->is_full_of_orders()) {
		waiting_block->update_orderhash();       // order를 가지고 merkletree 생성
		waiting_block->mining();                 // waiting block을 채굴
		add_block_to_blockchain(waiting_block);  // waiting block을 blockchain에 추가

		Block * new_waiting_block = new Block(last_block); // new waiting block 생성
		new_waiting_block->get_order().reserve(MAX_ORDER_COUNT);
		waiting_block = new_waiting_block;
	}
}

// 블록을 블록체인에 연결한다.
void BlockChain::add_block_to_blockchain(Block * _block) {
	last_block = _block;
	num_of_block++;
}

// 블록의 모든 order 정보를 출력한다.
void BlockChain::print_all_order() {
	if (last_block == NULL) {
		std::cout << "There is no history of your order...\n";
		return;
	}

	// 마지막 블록부터 첫 블록까지, 모든 블록에 대하여
	const Block * block = last_block;
	for (std::uint64_t i = num_of_block; i > 0; i--, block = block->get_previous_block()) {
		// 블록이 유효한 블록이면
		if (block->is_valid_block() && block->is_valid_order()) {
			std::cout << "\n\nBlockhash: ";
			SHA256_Print(block->get_blockhash());
			std::cout << "Orderhash: ";
			SHA256_Print(block->get_orderhash());

			std::size_t size = block->get_order().size();
			// 그 블록의 모든 order를 출력
			for (std::int32_t j = size - 1; j > -1; j--)
				block->get_order()[j]->print();
		}
		// 유효하지 않으면 메세지 출력
		else {
			std::cout << "Digital forgery had occured in " << i << "th block...";
			break;
		}
	}
}

// 블록의 order를 반환한다.
const Order * BlockChain::get_order(time_t _order_timestamp) const {
	if (last_block == NULL) {
		std::cout << "There is no history of your order...\n";
		return NULL;
	}

	// 마지막 블록부터 순차적으로 블록을 찾는다.
	const Block * block = last_block;
	while (block->get_timestamp() >= _order_timestamp) {
		block = block->get_previous_block();
	}

	// 찾은 블록 안에서 이진탐색으로 원하는 order를 찾는다.
	for (std::int32_t low = 0, high = block->get_order().size() - 1; low <= high;) {
		std::int32_t mid = ((unsigned int)low + (unsigned int)high) >> 1;
		time_t midVal = block->get_order()[mid]->get_timestamp();

		if (midVal < _order_timestamp)
			low = mid + 1;
		else if (midVal > _order_timestamp)
			high = mid - 1;
		else
			return block->get_order()[mid]; // order found
	}

	return NULL; // order not found.
}

// functions for saving this blockchain to computer
void save_order();
void load_order();

// 마지막 블록부터 첫 블록까지, 모든 블록의 blockhash 출력
void BlockChain::print_all_blockhash() {
	const Block * block = last_block;
	const BYTE * hash;
	for (std::uint64_t i = num_of_block; i > 0; i--, block = block->get_previous_block()) {
		hash = block->get_blockhash();
		std::cout << i << "th block's blockhash : ";
		SHA256_Print(hash);
	}
}

//마지막 블록부터 첫 블록까지, 모든 블록의 orderhash 출력
void BlockChain::print_all_orderhash() {
	const Block * block = last_block;
	const BYTE * hash;
	for (std::uint64_t i = num_of_block; i > 0; i--, block = block->get_previous_block()) {
		hash = block->get_orderhash();
		std::cout << i << "th block's orderhash : ";
		SHA256_Print(hash);
	}
}

const Block * BlockChain::get_genesis_block() const {
	return genesis_block;
}

const Block * BlockChain::get_last_block() const {
	return last_block;
}

std::uint64_t BlockChain::get_num_of_block() const {
	return num_of_block;
}
