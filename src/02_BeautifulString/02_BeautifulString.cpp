// 02_BeautifulString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>


const int BS_NUM = 3; // Max number of different characters to form Beautiful-String

class BeautifulStringParser {
    struct BS_ITEM {
        TCHAR   data;
        int     offset;
        int     count;
    } m_bs[BS_NUM];

protected:
    void _Reset();
    bool _FeedCharToFindBeautifulString(TCHAR ch, int offset);

public:
    bool FindBeautifulString(const TCHAR* str, int& offset, int& length);
};

void BeautifulStringParser::_Reset()
{
    ZeroMemory(&m_bs, sizeof(m_bs));
}

bool BeautifulStringParser::FindBeautifulString(const TCHAR* str, int& offset, int& length)
{
    _Reset();

    for (const TCHAR* p = str; *p != NULL; p++) {
        if (_FeedCharToFindBeautifulString(*p, p - str)) {
            offset = m_bs[0].offset;
            length = m_bs[0].count * BS_NUM;
            return true;
        }
    }

    return false;
}

bool BeautifulStringParser::_FeedCharToFindBeautifulString(TCHAR ch, int offset)
{
    return true;
}


bool FindBeautifulString(const TCHAR* str, int& offset, int& length)
{
    BeautifulStringParser parser;
    return parser.FindBeautifulString(str, offset, length);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR text[] = _T("aabbbccddefg");
    int offset = -1;
    int length = -1;
    bool res = FindBeautifulString(text, offset, length);

    return 0;
}

