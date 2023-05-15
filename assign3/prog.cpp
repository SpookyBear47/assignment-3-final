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