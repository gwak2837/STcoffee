#include <iostream>
#include "KISA_SHA256.h"
#include "Block.h"
#include "Order.h"

const std::string Block::version = "STcoffee";
BYTE Block::bits = 2;                           

// SHA256�� ������ ���ڿ��� �Է¹����� �����Ұ����� 256 bit(32 byte)�� ���� ����Ѵ�.
// ���� blockhash�� 0�� 32�� �ʰ��ϴ� ��ŭ ���� �� ����.(byte����, 16������ ����ϸ� 0�� �ִ� 64��)
Block::Block(const Block * _previous_block) : previous_block(_previous_block) {
	// bits ���� ������ üũ�Ѵ�.
	if (bits < 0 || bits > 32)
		std::cout << "error: block bits must be between 0 and 32.\n\n";
}

// ����ڷκ��� ���� order�� ��Ͽ� �߰��Ѵ�.
void Block::add_order_to_block(Order * _order) {
	order.push_back(_order);
}

// Block::order�� �ؽ��� ���� �ٽ� 2���� �ؽ��ϸ鼭 ��ŬƮ���� �����.
void Block::build_merkletree(std::vector<BYTE *> orderhash_vector, std::vector<BYTE *> orderhash_vector2) const {
	BYTE * hash_in = new BYTE[64];
	BYTE * hash_out = new BYTE[32];

	memcpy(hash_in, orderhash_vector.back(), 32);
	delete orderhash_vector.back();
	orderhash_vector.pop_back();

	memcpy(hash_in + 32, orderhash_vector.back(), 32);
	delete orderhash_vector.back();
	orderhash_vector.pop_back();

	SHA256_Encrpyt(hash_in, 64, hash_out);
	delete hash_in;
	orderhash_vector2.push_back(hash_out);
}

// ����� ��Ŭ��Ʈ�� Block::orderhash�� ���� �� ���� �����͸� �����Ѵ�.
void Block::copy_merkleroot(std::vector<BYTE *> orderhash_vector) {
	memcpy(orderhash, orderhash_vector.front(), 32);
	delete orderhash_vector.front();
}

// ���� Block::order�� �����͸� ������ SHA256 �ؽ��Ѵ�.
void Block::hashing_each_order(std::vector<BYTE *> * orderhash_vector) const {
	// ��� order�� ���ؼ�
	for (std::size_t i = 0; i < order.size(); i++) {
		if (order[i] != NULL) {
			// order�� ������(���̸�, �����̸�, ��ġ, �ֹ��ð�, �� �ݾ�, ��������)�� byte ������ �̾�ٿ��� SHA256 �ؽ��� �� vector�� push�Ѵ�.
			const int LENGTH = order[i]->orderer_name.size() + order[i]->store_name.size() + order[i]->store_location.size() + sizeof(order[i]->timestamp) + sizeof(order[i]->total_amount) + order[i]->payment_method.size();
			std::size_t j = 0, k;
			const BYTE * pb;
			BYTE * buffer = new BYTE[LENGTH];
			BYTE * orderhash = new BYTE[32];

			for (k = 0; k < order[i]->orderer_name.size(); j++, k++)
				buffer[j] = order[i]->orderer_name[k];

			for (k = 0; k < order[i]->store_name.size(); j++, k++)
				buffer[j] = order[i]->store_name[k];

			for (k = 0; k < order[i]->store_location.size(); j++, k++)
				buffer[j] = order[i]->store_location[k];

			pb = (BYTE *)&order[i]->timestamp;
			for (k = 0; k < sizeof(timestamp); j++, k++)
				buffer[j] = pb[k];

			pb = (BYTE *)&order[i]->total_amount;
			for (k = 0; k < sizeof(bits); j++, k++)
				buffer[j] = pb[k];

			for (k = 0; k < order[i]->payment_method.size(); j++, k++)
				buffer[j] = order[i]->payment_method[k];

			SHA256_Encrpyt(buffer, LENGTH, orderhash);
			delete[] buffer;
			orderhash_vector->push_back(orderhash);
		}
	}
}

// Block�� �ִ� ��� ���� order�� �ؽ��� ��ŬƮ���� ����� ��Ʈ ���� Block::orderhash�� �����Ѵ�.
void Block::update_orderhash() {
	std::vector<BYTE *> orderhash_vector;
	std::vector<BYTE *> orderhash_vector2;

	orderhash_vector.reserve(MAX_ORDER_COUNT);
	orderhash_vector2.reserve(MAX_ORDER_COUNT);

	// Block�� �ִ� ��� order�� ���� �ؽ��ؼ� �� ������� ���Ϳ� �ִ´�.
	hashing_each_order(&orderhash_vector);

	// �ؽø� 2���� ��� �ؽ��Ѵ�.(= ��ŬƮ���� �����.)
	while (orderhash_vector.size() + orderhash_vector2.size() > 1) {
		while (orderhash_vector.size() > 0)
			build_merkletree(orderhash_vector, orderhash_vector2);
		continue;

		while (orderhash_vector2.size() > 0)
			build_merkletree(orderhash_vector2, orderhash_vector);
	}
	
	// ��Ŭ��Ʈ�� ��� ���Ϳ� �ִ��� �Ǵ��ϰ� ��Ŭ��Ʈ�� orderhash�� �����Ѵ�.
	if (orderhash_vector.size() == 1)
		copy_merkleroot(orderhash_vector);
	else
		copy_merkleroot(orderhash_vector2);
}

// Block�� �ִ� version, previous block -> blockhash, orderhash, timestamp, bits, nonce ���� byte ������ �̾�ٿ� SHA256 �ؽ��� �� �� ���� blockhash�� �����Ѵ�.
void Block::hashing_blockheader() {
	const int LENGTH = version.length() + sizeof(previous_block->blockhash) + sizeof(orderhash) + sizeof(timestamp) + sizeof(bits) + sizeof(nonce);
	std::size_t i = 0, j;
	const BYTE * pb;
	BYTE * buffer = new BYTE[LENGTH];

	for (j = 0; j < version.length(); i++, j++)
		buffer[i] = version[j];

	if (previous_block != NULL) {
		pb = previous_block->blockhash;
		for (j = 0; j < sizeof(previous_block->blockhash); i++, j++)
			buffer[i] = pb[j];
	}

	for (j = 0; j < sizeof(orderhash); i++, j++)
		buffer[i] = orderhash[j];

	pb = (BYTE *)&timestamp;
	for (j = 0; j < sizeof(timestamp); i++, j++)
		buffer[i] = pb[j];

	pb = (BYTE *)&bits;
	for (j = 0; j < sizeof(bits); i++, j++)
		buffer[i] = pb[j];

	pb = (BYTE *)&nonce;
	for (j = 0; j < sizeof(nonce); i++, j++)
		buffer[i] = pb[j];

	SHA256_Encrpyt(buffer, LENGTH, blockhash);
	delete[] buffer;
}

// ����ؽÿ� 0�� byte���� bits ����ŭ �ִ��� �Ǵ��Ѵ�.(16���� ���� 2*bits��)
bool Block::is_valid_block() const {
	for (std::int32_t i = 0; i < bits; i++) {
		if (blockhash[i] != 0)
			return false;
	}
	return true;
}

// ��Ͽ� order�� ��á���� �˻��Ѵ�.
bool Block::is_full_of_orders() const {
	return (order.size() >= MAX_ORDER_COUNT) ? true : false;
}

// Proof of Work��(���� �˰���) ä���Ѵ�.
void Block::mining() {
	nonce = 0;
	do {
		timestamp = time(NULL);
		hashing_blockheader();
		nonce++;
	} while (!is_valid_block());
}

// ���� ���ü�ο� �ִ� ����� ��ȿ�� ������� �˻��Ѵ�.
bool Block::is_valid_order() const {
	std::vector<BYTE *> orderhash_vector;
	std::vector<BYTE *> orderhash_vector2;
	std::vector<BYTE *> merkleroot;
	bool is_valid_order = true;

	orderhash_vector.reserve(MAX_ORDER_COUNT);
	orderhash_vector2.reserve(MAX_ORDER_COUNT);
	merkleroot.reserve(1);

	// ���� order�� �ؽ�ȭ
	hashing_each_order(&orderhash_vector);

	// ���� order �ؽø� ������ ��ŬƮ�� ����
	while (orderhash_vector.size() + orderhash_vector2.size() > 1) {
		while (orderhash_vector.size() > 0)
			build_merkletree(orderhash_vector, orderhash_vector2);
		continue;

		while (orderhash_vector2.size() > 0)
			build_merkletree(orderhash_vector2, orderhash_vector);
	}

	// ��Ŭ��Ʈ�� ��� ���Ϳ� �ִ��� �Ǵ�
	if (orderhash_vector.size() == 1)
		merkleroot.push_back(orderhash_vector[0]);
	else
		merkleroot.push_back(orderhash_vector2[0]);		

	// ��Ŭ��Ʈ �ؽð��� ����� order �ؽð��� �� �� ������ true ��ȯ
	for (std::int32_t i = 0; i < 32; i++) {
		if (orderhash[i] != merkleroot[0][i])
			is_valid_order = false;
	}

	// ����� ��� �����Ҵ� �޸𸮸� ������
	delete merkleroot[0];

	return is_valid_order;
}

const BYTE * Block::get_blockhash() const {
	return blockhash;
}

const Block * Block::get_previous_block() const {
	return previous_block;
}

const BYTE * Block::get_orderhash() const {
	return orderhash;
}

time_t Block::get_timestamp() const {
	return timestamp;
}

std::vector<Order *> Block::get_order() const {
	return order;
}


