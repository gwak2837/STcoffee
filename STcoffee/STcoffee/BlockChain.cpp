#include <iostream>
#include "KISA_SHA256.h"
#include "BlockChain.h"
#include "Block.h"
#include "Order.h"

std::uint64_t BlockChain::num_of_block = 0;

// Genesis block�� �����Ѵ�.
BlockChain::BlockChain() {
	Block * _genesis_block = new Block(NULL); // blockchain ���� -> genesis block ����
	_genesis_block->get_order().reserve(MAX_ORDER_COUNT);
	genesis_block = _genesis_block;
	waiting_block = _genesis_block;
	last_block = NULL;
}

// Genesis block�� �����ϰ� �� ��Ͽ� order�� �߰��Ѵ�.
BlockChain::BlockChain(Order * _order) {
	BlockChain();
	waiting_block->add_order_to_block(_order);
}

// BlockChain �����Լ��� ȣ���� �ڵ����� order�� ��Ͽ� �־��ִ� �Լ��̴�.
void BlockChain::add_order_to_blockchain(Order * _order) {
	waiting_block->add_order_to_block(_order); // waiting block�� order �߰�

	// waiting block�� order�� ������
	if (waiting_block->is_full_of_orders()) {
		waiting_block->update_orderhash();       // order�� ������ merkletree ����
		waiting_block->mining();                 // waiting block�� ä��
		add_block_to_blockchain(waiting_block);  // waiting block�� blockchain�� �߰�

		Block * new_waiting_block = new Block(last_block); // new waiting block ����
		new_waiting_block->get_order().reserve(MAX_ORDER_COUNT);
		waiting_block = new_waiting_block;
	}
}

// ����� ���ü�ο� �����Ѵ�.
void BlockChain::add_block_to_blockchain(Block * _block) {
	last_block = _block;
	num_of_block++;
}

// ����� ��� order ������ ����Ѵ�.
void BlockChain::print_all_order() {
	if (last_block == NULL) {
		std::cout << "There is no history of your order...\n";
		return;
	}

	// ������ ��Ϻ��� ù ��ϱ���, ��� ��Ͽ� ���Ͽ�
	const Block * block = last_block;
	for (std::uint64_t i = num_of_block; i > 0; i--, block = block->get_previous_block()) {
		// ����� ��ȿ�� ����̸�
		if (block->is_valid_block() && block->is_valid_order()) {
			std::cout << "\n\nBlockhash: ";
			SHA256_Print(block->get_blockhash());
			std::cout << "Orderhash: ";
			SHA256_Print(block->get_orderhash());

			std::size_t size = block->get_order().size();
			// �� ����� ��� order�� ���
			for (std::int32_t j = size - 1; j > -1; j--)
				block->get_order()[j]->print();
		}
		// ��ȿ���� ������ �޼��� ���
		else {
			std::cout << "Digital forgery had occured in " << i << "th block...";
			break;
		}
	}
}

// ����� order�� ��ȯ�Ѵ�.
const Order * BlockChain::get_order(time_t _order_timestamp) const {
	if (last_block == NULL) {
		std::cout << "There is no history of your order...\n";
		return NULL;
	}

	// ������ ��Ϻ��� ���������� ����� ã�´�.
	const Block * block = last_block;
	while (block->get_timestamp() >= _order_timestamp) {
		block = block->get_previous_block();
	}

	// ã�� ��� �ȿ��� ����Ž������ ���ϴ� order�� ã�´�.
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

// ������ ��Ϻ��� ù ��ϱ���, ��� ����� blockhash ���
void BlockChain::print_all_blockhash() {
	const Block * block = last_block;
	const BYTE * hash;
	for (std::uint64_t i = num_of_block; i > 0; i--, block = block->get_previous_block()) {
		hash = block->get_blockhash();
		std::cout << i << "th block's blockhash : ";
		SHA256_Print(hash);
	}
}

//������ ��Ϻ��� ù ��ϱ���, ��� ����� orderhash ���
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
