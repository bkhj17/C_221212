#include "CPlus.h"
#include <iostream>
using namespace std;

void CPlus::String()
{

	string str1, str2;
	cin >> str1 >> str2;

	cout << (str1 == str2 ? "같다" : "다르다") << "\n";

	cout << str1 + str2 << "\n";
}

void CPlus::Run()
{
	//int n;
	//std::cin >> n;
	//std::cout << "n : " << n << "\n";
	
	//String();

	int arr[] = { 1, 2, 3, 4, 5 };
	for (int a : arr)
		cout << ++a << " ";
	cout << "\n";

	for (const int& a : arr)
		cout << a << " ";
	cout << "\n";
}
