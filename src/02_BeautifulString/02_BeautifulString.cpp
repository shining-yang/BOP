// 02_BeautifulString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

// Max number of different characters to form Beautiful-String
// MUST greater than 2
const int BS_CHAR_NUM = 3;

class BeautifulStringParser {
    struct BS_ITEM {
        TCHAR   data;
        int     offset;
        int     count;
    } m_arrItems[BS_CHAR_NUM];

    int m_nIndicator; // subscript of array for current working BS-char

public:
    BeautifulStringParser() { _Reset(); }
    ~BeautifulStringParser() {}

protected:
    void _Reset();
    bool _FeedCharToFindBeautifulString(TCHAR ch, int offset);
    bool _CheckForBeautifulString() const;
    void _TrimHead();

public:
    bool FindBeautifulString(const TCHAR* str, int& offset, int& length);
};

void BeautifulStringParser::_Reset()
{
    ZeroMemory(&m_arrItems, sizeof(m_arrItems));
    m_nIndicator = -1;
}

bool BeautifulStringParser::FindBeautifulString(const TCHAR* str, int& offset, int& length)
{
    _Reset();

    for (const TCHAR* p = str; *p != NULL; p++) {
        if (_FeedCharToFindBeautifulString(*p, p - str)) {
            _TrimHead();
            offset = m_arrItems[0].offset;
            length = m_arrItems[0].count * BS_CHAR_NUM;
            return true;
        }
    }

    return false;
}

bool BeautifulStringParser::_FeedCharToFindBeautifulString(TCHAR ch, int offset)
{
    if (m_nIndicator == -1)  {
        // 初始化第0个位置
        m_arrItems[0].data = ch;
        m_arrItems[0].count = 1;
        m_arrItems[0].offset = offset;
        m_nIndicator = 0;
    } else {
        if (m_arrItems[m_nIndicator].data == ch) {
            m_arrItems[m_nIndicator].count++;
            if (_CheckForBeautifulString()) {
                return true;
            }
            if ((m_nIndicator > 0) && (m_arrItems[m_nIndicator].count > m_arrItems[m_nIndicator - 1].count)) {
                // 替换到第0个位置
                m_arrItems[0].data = m_arrItems[m_nIndicator].data;
                m_arrItems[0].count = m_arrItems[m_nIndicator].count;
                m_arrItems[0].offset = m_arrItems[m_nIndicator].offset;
                m_nIndicator = 0;
            }
        } else if (m_arrItems[m_nIndicator].data + 1 == ch) {
            if ((m_nIndicator == 0) || (m_nIndicator == 1)) {
                m_nIndicator++;
                m_arrItems[m_nIndicator].data = ch;
                m_arrItems[m_nIndicator].count = 1;
                m_arrItems[m_nIndicator].offset = offset;
            } else { // indicator is 2
                m_arrItems[0].data = m_arrItems[1].data;
                m_arrItems[0].count = m_arrItems[1].count;
                m_arrItems[0].offset = m_arrItems[1].offset;
                m_arrItems[1].data = m_arrItems[2].data;
                m_arrItems[1].count = m_arrItems[2].count;
                m_arrItems[1].offset = m_arrItems[2].offset;
                m_arrItems[2].data = ch;
                m_arrItems[2].count = 1;
                m_arrItems[2].offset = offset;
                if (_CheckForBeautifulString()) {
                    return true;
                }
            }
        } else {
            // 重新始于第0个位置
            m_arrItems[0].data = ch;
            m_arrItems[0].count = 1;
            m_arrItems[0].offset = offset;
            m_nIndicator = 0;
        }
    }

    return false;
}

bool BeautifulStringParser::_CheckForBeautifulString() const
{
    if (m_nIndicator < BS_CHAR_NUM - 1) { // must feed all
        return false;
    }

#if 1 // Redundant verification
    for (int i = 0; i < BS_CHAR_NUM - 1; i++) {
        if (m_arrItems[i + 1].data - m_arrItems[i].data != 1) { // increasing
            return false;
        }
    }
#endif

    if (m_arrItems[BS_CHAR_NUM - 1].count == m_arrItems[BS_CHAR_NUM - 2].count) {
        return true;
    }

    return false;
}

// eg. 'AAAABBCC' --> 'AABBCC'
void BeautifulStringParser::_TrimHead()
{
    int deta = m_arrItems[0].count - m_arrItems[1].count;
    m_arrItems[0].count -= deta;
    m_arrItems[0].offset += deta;
}

bool FindBeautifulString(const TCHAR* str, int& offset, int& length)
{
    BeautifulStringParser parser;
    return parser.FindBeautifulString(str, offset, length);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR text[] = _T("aabbbcccdddefg");

    int offset = -1;
    int length = -1;
    bool found = FindBeautifulString(text, offset, length);
    _tprintf(_T("%s\n"), found ? _T("YES") : _T("NO"));

    if (found) {
        for (int i = 0; i < length; i++) {
            _tprintf(_T("%c"), text[offset + i]);
        }
        _tprintf(_T("\n"));
    }

    return 0;
}

