#ifndef __STRING_UTILS__
#define _STRING_UTILS__
#include <string.h>


class CTextUtils
{
public:
	CTextUtils();
	~CTextUtils();

	static void replace(string &target, const string & search, const string & replacement); 
	static void replace(wstring& target, const wstring& search, const wstring& replacement);
private:

};

#endif