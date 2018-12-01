#include <iostream>
#include "KISA_SHA256.h"
#include "Block.h"
#include "Order.h"

const std::string Block::version = "STcoffee";
BYTE Block::bits = 2;                           

// SHA256은 임의의 문자열을 입력받으면 예측불가능한 256 bit(32 byte)의 값을 출력한다.
// 따라서 blockhash에 0이 32개 초과하는 만큼 나올 수 없다.(byte기준, 16진수로 출력하면 0이 최대 64개)
Block::Block(const Block * _previous_block) : previous_block(_previous_block) {
	// bits 값의 범위를 체크한다.
	if (bits < 0 || bits > 32)
		std::cout << "error: block bits must be between 0 and 32.\n\n";
}

// 사용자로부터 받은 order를 블록에 추가한다.
void Block::add_order_to_block(Order * _order) {
	order.push_back(_order);
}

// Block::order를 해시한 값을 다시 2개씩 해시하면서 머클트리를 만든다.
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

// 계산한 머클루트를 Block::orderhash에 복사 후 기존 포인터를 해제한다.
void Block::copy_merkleroot(std::vector<BYTE *> orderhash_vector) {
	memcpy(orderhash, orderhash_vector.front(), 32);
	delete orderhash_vector.front();
}

// 개별 Block::order의 데이터를 가지고 SHA256 해싱한다.
void Block::hashing_each_order(std::vector<BYTE *> * orderhash_vector) const {
	// 모든 order에 대해서
	for (std::size_t i = 0; i < order.size(); i++) {
		if (order[i] != NULL) {
			// order의 데이터(고객이름, 가게이름, 위치, 주문시간, 총 금액, 결제수단)를 byte 단위로 이어붙여서 SHA256 해싱한 후 vector에 push한다.
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

// Block에 있는 모든 개별 order를 해시해 머클트리를 만들어 루트 값을 Block::orderhash에 복사한다.
void Block::update_orderhash() {
	std::vector<BYTE *> orderhash_vector;
	std::vector<BYTE *> orderhash_vector2;

	orderhash_vector.reserve(MAX_ORDER_COUNT);
	orderhash_vector2.reserve(MAX_ORDER_COUNT);

	// Block에 있는 모든 order를 각각 해시해서 그 결과값을 벡터에 넣는다.
	hashing_each_order(&orderhash_vector);

	// 해시를 2개씩 묶어서 해시한다.(= 머클트리를 만든다.)
	while (orderhash_vector.size() + orderhash_vector2.size() > 1) {
		while (orderhash_vector.size() > 0)
			build_merkletree(orderhash_vector, orderhash_vector2);
		continue;

		while (orderhash_vector2.size() > 0)
			build_merkletree(orderhash_vector2, orderhash_vector);
	}
	
	// 머클루트가 어느 벡터에 있는지 판단하고 머클루트를 orderhash에 복사한다.
	if (orderhash_vector.size() == 1)
		copy_merkleroot(orderhash_vector);
	else
		copy_merkleroot(orderhash_vector2);
}

// Block에 있는 version, previous block -> blockhash, orderhash, timestamp, bits, nonce 값을 byte 단위로 이어붙여 SHA256 해시한 후 그 값을 blockhash에 저장한다.
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

// 블록해시에 0이 byte기준 bits 개만큼 있는지 판단한다.(16진수 기준 2*bits개)
bool Block::is_valid_block() const {
	for (std::int32_t i = 0; i < bits; i++) {
		if (blockhash[i] != 0)
			return false;
	}
	return true;
}

// 블록에 order가 꽉찼는지 검사한다.
bool Block::is_full_of_orders() const {
	return (order.size() >= MAX_ORDER_COUNT) ? true : false;
}

// Proof of Work로(합의 알고리즘) 채굴한다.
void Block::mining() {
	nonce = 0;
	do {
		timestamp = time(NULL);
		hashing_blockheader();
		nonce++;
	} while (!is_valid_block());
}

// 기존 블록체인에 있는 블록이 유효한 블록인지 검사한다.
bool Block::is_valid_order() const {
	std::vector<BYTE *> orderhash_vector;
	std::vector<BYTE *> orderhash_vector2;
	std::vector<BYTE *> merkleroot;
	bool is_valid_order = true;

	orderhash_vector.reserve(MAX_ORDER_COUNT);
	orderhash_vector2.reserve(MAX_ORDER_COUNT);
	merkleroot.reserve(1);

	// 개별 order를 해시화
	hashing_each_order(&orderhash_vector);

	// 개별 order 해시를 가지고 머클트리 제작
	while (orderhash_vector.size() + orderhash_vector2.size() > 1) {
		while (orderhash_vector.size() > 0)
			build_merkletree(orderhash_vector, orderhash_vector2);
		continue;

		while (orderhash_vector2.size() > 0)
			build_merkletree(orderhash_vector2, orderhash_vector);
	}

	// 머클루트가 어느 벡터에 있는지 판단
	if (orderhash_vector.size() == 1)
		merkleroot.push_back(orderhash_vector[0]);
	else
		merkleroot.push_back(orderhash_vector2[0]);		

	// 머클루트 해시값과 블록의 order 해시값을 비교 후 같으면 true 반환
	for (std::int32_t i = 0; i < 32; i++) {
		if (orderhash[i] != merkleroot[0][i])
			is_valid_order = false;
	}

	// 사용한 모든 동적할당 메모리를 해제함
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


