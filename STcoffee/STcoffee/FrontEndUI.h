#pragma once
#ifndef FRONTEND_UI_H
#define FRONTEND_UI_H

enum class _Main {
	exit, menu, cart, favorite, FAQ, myinfo
};

enum class _Menu {
	back, coffee, side_dish
};

enum class _Cart {
	back, order, add_to_favorite, delete_from_cart, go_to_favorite
};

enum class _Favorite {
	back, add_to_cart, delete_from_favorite, go_to_cart
};

enum class _MyInfo {
	back, order_history, point, your_name
};

enum class _YourOrder {
	cancel, order, cart, favorite
};

class FrontEndUI
{
public:
	FrontEndUI();

	void print_main();
	void print_menu();
	void print_cart();
	void print_favorite();
	void print_myinfo();
	void print_your_order();
};

#endif // !FRONTEND_UI_H




