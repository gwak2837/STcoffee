#pragma once
#ifndef FAQ_H
#define FAQ_H
#include <vector>
#include <string>
#include <cstdint>

// singletone class
class FAQ
{
	static std::vector<std::string> question;  // ���� ����� ���� ����(����Ʈ)
	static std::vector<std::string> answer;    // ������ ���� ��� ����

public:
	FAQ();

	void print_question() const;
	void print_answer(std::int32_t index) const;
};


#endif // !FAQ_H


