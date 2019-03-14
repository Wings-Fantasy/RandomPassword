#pragma once
#include <string>

class Password
{
public:
	Password();
	std::string getPassword(bool includeNumber, bool includeUpperCaseLetter, bool includeLowerCaseLetter, unsigned int length);

private:
	const char numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
	const char upperCaseLetters[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	const char lowerCaseLetters[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	
	char getNumber();
	char getLowerCaseLetter();
	char getUpperCaseLetter();
};

