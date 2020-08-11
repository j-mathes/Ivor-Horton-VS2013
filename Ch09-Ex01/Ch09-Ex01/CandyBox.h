#pragma once

#include <cstring>		// for strlen() and strcpy_s()
#include "Box.h"

class CCandyBox : public CBox
{
public:
	char* m_Contents;

	explicit CCandyBox(const char* str = "Candy")
	{
		size_t length{ strlen(str) + 1 };
		m_Contents = new char[length];
		strcpy_s(m_Contents, length, str);
	}

	CCandyBox(const CCandyBox& box) = delete;		// deleted copy constructor - copy because it takes as an argument, an object of type 'itself'
	CCandyBox& operator=(const CCandyBox& box) = delete;

	~CCandyBox()
	{
		delete[] m_Contents;
	}
};