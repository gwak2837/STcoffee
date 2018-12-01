#include "Product.h"
#include "Menu.h"

// for coffee product
Product::Product(std::string _name, std::string _size, std::string _coffee_beans, std::string _addition, std::int16_t _sugar, std::int16_t _ice, std::int16_t _shot, std::int16_t _temperature  , bool _art, bool _take_out, std::int64_t _quantity, std::int64_t _unit_price)
	: name(_name), size(_size), coffee_beans(_coffee_beans), addition(_addition), sugar(_sugar), ice(_ice), shot(_shot), temperature(_temperature), art(_art), take_out(_take_out), quantity(_quantity), unit_price(_unit_price), amount(_unit_price * _quantity) { }

// for side dish product
Product::Product(std::string _name, std::string _size, bool _take_out, std::int64_t _quantity, std::int64_t _unit_price)
	: name(_name), size(_size), take_out(_take_out), quantity(_quantity), unit_price(_unit_price), amount(_unit_price * _quantity) { }
	
const std::int64_t Product::get_amount() {
	return amount;
}

// Product ������ string ���·� ��ȯ�Ѵ�.
const std::string Product::to_string() {
	return "\nProduct: " + name + (nickname.compare("") ? "\nNickname: " + nickname : "") + "\nSize: " + size
		+ "\nQuantity: " + std::to_string(quantity)	+ "\nUnit price: " + std::to_string(unit_price) + "\nAmount: " + std::to_string(amount);
}

// Product�� ������ �̸��� �����Ѵ�.
void Product::add_nickname(std::string _nickname) {
	nickname = _nickname;
}