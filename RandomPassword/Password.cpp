#include "stdafx.h"
#include "Password.h"
#include <cstdlib>
#include <time.h>

Password::Password()
{
	srand((unsigned)time(NULL));
}

std::string Password::getPassword(bool includeNumber, bool includeUpperCaseLetter, bool includeLowerCaseLetter, unsigned int length)
{
	std::string password = "";
	while (password.length() < length)
	{
		int select = rand() % 3 + 1;
		switch (select)
		{
		case 1:
			if (includeNumber)
			{
				password += getNumber();
			}
			break;
		case 2:
			if (includeUpperCaseLetter)
			{
				password += getUpperCaseLetter();
			}
			break;
		case 3:
			if (includeLowerCaseLetter)
			{
				password += getLowerCaseLetter();
			}
			break;
		}
	}
	return password;
}

char Password::getNumber()
{
	return numbers[rand() % 10];
}

char Password::getLowerCaseLetter()
{
	return lowerCaseLetters[rand() % 26];
}

char Password::getUpperCaseLetter()
{
	return upperCaseLetters[rand() % 26];
}
