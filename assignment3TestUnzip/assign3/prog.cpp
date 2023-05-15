/******************************************************
** Program: prog.cpp
** Author: Wesley Granmdmont IV
** Date: 05/15/2023
** Description: A program that simulates the basic functions of a coffee shop
** Input: User inputs numbers to navigate menus, and also other data when prompted
** Output: Program outputs relevant information that the user queries for
******************************************************/

#include "shop.h"
#include <fstream>

using namespace std;

int main()
{
	Shop myShop;
	myShop.load_data();
	myShop.load_initial_menu();

	return 0;
}