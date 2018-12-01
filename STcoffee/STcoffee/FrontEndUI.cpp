#include <iostream>
#include "FrontEndUI.h"

FrontEndUI::FrontEndUI() {}

void FrontEndUI::print_main() {
	std::cout << "------------------------------- M a i n -------------------------------\n";
	std::cout << "0.exit \t 1.Menu \t 2.Cart \t 3.Favorite \t 4.FAQ \t 5. MyInfo \n";
}

void FrontEndUI::print_menu() {
	std::cout << "------------------------------- M e n u -------------------------------\n";
	std::cout << "0.back \t 1.Coffee \t 2.Side dish \n";
}

void FrontEndUI::print_cart() {
	std::cout << "------------------------------- O p t i o n -------------------------------\n";
	std::cout << "0.back \t 1.Order \t 2.Add to favorite \t 3.Delete from cart \t 4.Go to favorite \n";
}

void FrontEndUI::print_favorite() {
	std::cout << "------------------------------- O p t i o n -------------------------------\n";
	std::cout << "0.back \t 1.Add to cart \t 2.Delete from favorite \t 3.Go to cart \n";
}

void FrontEndUI::print_myinfo() {
	std::cout << "------------------------------- M y I n f o -------------------------------\n";
	std::cout << "0.back \t 1.Order history \t 2.Point \t 3.Your name \n";
}

void FrontEndUI::print_your_order() {
	std::cout << "------------------------------- Y o u r  O r d e r -------------------------------\n";
	std::cout << "Move your order to? \t 0.Cancel order \t 1.Order now \t 2.Cart \t 3.Favorite \n";
}


