#include <bitset>
#include <iostream>

int main()
{
	constexpr int a1 = 5, b1 = 4;
	std::bitset<32> a2(a1);
	std::bitset<32> b2(b1);
	std::cout << a2 << "\n"
			  << b2 << "\n";
	std::cout << (a2 & b2) << "\n";
	return 0;
}
