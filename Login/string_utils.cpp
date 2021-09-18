#include "stdafx.h"
#include "string_utils.h"

void CTextUtils::replace(string &target, const string & search, const string & replacement) 
{
	if (search.compare(replacement) == 0)
		return;

	else if (search.compare("") == 0)
		return;

	string::size_type i = string::npos;
	string::size_type lastPos = 0;
	while ((i = target.find(search, lastPos)) != string::npos) {
		target.replace(i, search.length(), replacement);
		lastPos = i + replacement.length();
	}
}

void CTextUtils::replace(wstring& target, const wstring& search, const wstring& replacement)
{
    if (search.compare(replacement) == 0)
        return;

    else if (search.compare(L"") == 0)
        return;

    string::size_type i = string::npos;
    string::size_type lastPos = 0;
    while ((i = target.find(search, lastPos)) != string::npos) {
        target.replace(i, search.length(), replacement);
        lastPos = i + replacement.length();
    }
}