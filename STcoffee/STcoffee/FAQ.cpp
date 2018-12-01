#include <iostream>
#include "FAQ.h"

std::vector<std::string> FAQ::question = { "How to order?" };
std::vector<std::string> FAQ::answer = { "Go to main, select the menu, select the product you want, and click order" };

FAQ::FAQ() {}

// 자주 묻는 질문을 출력한다.
void FAQ::print_question() const {
	std::cout << "------------------------------- F A Q -------------------------------\n";
	std::cout << "0.back\n";
	for (std::size_t i = 0; i < question.size(); i++)
		std::cout << i + 1 << '.' << question[i] << '\n';
}

// 입력한 질문에 따른 대답을 출력한다.
void FAQ::print_answer(std::int32_t index) const {
	std::cout << index << '.' << answer[index - 1] << '\n';
}

