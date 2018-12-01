#pragma once
#ifndef FAQ_H
#define FAQ_H
#include <vector>
#include <string>
#include <cstdint>

// singletone class
class FAQ
{
	static std::vector<std::string> question;  // 자주 물어보는 질문 벡터(리스트)
	static std::vector<std::string> answer;    // 질문에 따른 대답 벡터

public:
	FAQ();

	void print_question() const;
	void print_answer(std::int32_t index) const;
};


#endif // !FAQ_H


