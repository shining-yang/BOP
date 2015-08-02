// 02_BeautifulString.cpp : Defines the entry point for the console application.
//
// DESCRIPTION:
// We say a string is beautiful if it has the equal amount of 3 or more
// continuous letters(in increasing order).
// Here are some example of valid beautiful strings : "abc", "cde", "aabbcc", "aaabbbccc".
// Here are some example of invalid beautiful strings : "abd", "cba", "aabbc", "zab".
// Given a string of alphabets containing only lowercase alphabets(a - z),
// output "YES" if the string contains a be3autiful sub - string, otherwise output "NO".
//
#include "stdafx.h"
#include <Windows.h>

// Max number of different characters to form Beautiful-String. MUST greater than 2
const int BS_CHAR_NUM = 3;

struct BS_ITEM {
	TCHAR   data;
	int     offset;
	int     count;
};

class BeautifulStringParser {
	BeautifulStringParser(const BeautifulStringParser& other);
	BeautifulStringParser& operator=(const BeautifulStringParser& other);

public:
	BeautifulStringParser(int num = BS_CHAR_NUM);
	~BeautifulStringParser();

public:
    bool Find(const TCHAR* str, int& offset, int& length);

protected:
    void _Reset();
    bool _FeedChar(TCHAR ch, int offset);
    bool _Check() const;
    void _TrimHead();

private:
	BS_ITEM* m_pItems;
	int m_nCharNum;		// different character numbers we considered as BeautifulString
    int m_nIndicator;	// subscript of array for current working BS-char
};

BeautifulStringParser::BeautifulStringParser(int num) : m_nCharNum(num), m_nIndicator(-1)
{
	m_pItems = new BS_ITEM[m_nCharNum];
}

BeautifulStringParser::~BeautifulStringParser()
{
	delete[] m_pItems;
}

void BeautifulStringParser::_Reset()
{
    m_nIndicator = -1;
}

bool BeautifulStringParser::Find(const TCHAR* str, int& offset, int& length)
{
    _Reset();

    for (const TCHAR* p = str; *p != NULL; p++) {
        if (_FeedChar(*p, p - str)) {
            _TrimHead();
            offset = m_pItems[0].offset;
            length = m_pItems[0].count * m_nCharNum;
            return true;
        }
    }

    return false;
}

bool BeautifulStringParser::_FeedChar(TCHAR ch, int offset)
{
    if (m_nIndicator == -1)  {
        // 初始化第0个位置
        m_pItems[0].data = ch;
        m_pItems[0].count = 1;
        m_pItems[0].offset = offset;
        m_nIndicator = 0;
    } else {
        if (m_pItems[m_nIndicator].data == ch) {
            m_pItems[m_nIndicator].count++;
            if (_Check()) {
                return true;
            }
            if ((m_nIndicator > 0) && (m_pItems[m_nIndicator].count > m_pItems[m_nIndicator - 1].count)) {
                // 替换到第0个位置
                m_pItems[0].data = m_pItems[m_nIndicator].data;
                m_pItems[0].count = m_pItems[m_nIndicator].count;
                m_pItems[0].offset = m_pItems[m_nIndicator].offset;
                m_nIndicator = 0;
            }
        } else if (m_pItems[m_nIndicator].data + 1 == ch) {
			if ((m_nIndicator == 0) || m_pItems[m_nIndicator].count == m_pItems[m_nIndicator - 1].count) {
                m_nIndicator++;
                m_pItems[m_nIndicator].data = ch;
                m_pItems[m_nIndicator].count = 1;
                m_pItems[m_nIndicator].offset = offset;
            } else {
				// shift items
                m_pItems[0].data	= m_pItems[m_nIndicator - 1].data;
                m_pItems[0].count	= m_pItems[m_nIndicator - 1].count;
                m_pItems[0].offset	= m_pItems[m_nIndicator - 1].offset;
                m_pItems[1].data	= m_pItems[m_nIndicator].data;
                m_pItems[1].count	= m_pItems[m_nIndicator].count;
                m_pItems[1].offset	= m_pItems[m_nIndicator].offset;
                m_pItems[2].data	= ch;
                m_pItems[2].count	= 1;
                m_pItems[2].offset	= offset;
				m_nIndicator = 2;
            }
            if (_Check()) {
                return true;
            }
        } else {
            // 重新始于第0个位置
            m_pItems[0].data = ch;
            m_pItems[0].count = 1;
            m_pItems[0].offset = offset;
            m_nIndicator = 0;
        }
    }

    return false;
}

bool BeautifulStringParser::_Check() const
{
    if (m_nIndicator < m_nCharNum - 1) { // must feed all
        return false;
    }

    if (m_pItems[m_nCharNum - 1].count == m_pItems[m_nCharNum - 2].count) {
        return true;
    }

    return false;
}

// eg. 'AAAABBCC' --> 'AABBCC'
void BeautifulStringParser::_TrimHead()
{
    int deta = m_pItems[0].count - m_pItems[1].count;
    m_pItems[0].count -= deta;
    m_pItems[0].offset += deta;
}

bool FindBeautifulString(const TCHAR* str, int& offset, int& length)
{
    BeautifulStringParser parser;
    return parser.Find(str, offset, length);
}

void OutputResult(const TCHAR* text, bool found, int offset, int length)
{
	_tprintf(_T("%s\n"), found ? _T("YES") : _T("NO"));

	if (found) {
		for (int i = 0; i < length; i++) {
			_tprintf(_T("%c"), text[offset + i]);
		}
		_tprintf(_T("\n"));
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR text[] = _T("aabbbcccddeefghi");

    int offset = -1;
    int length = -1;
	bool found = false;
	
	found = FindBeautifulString(text, offset, length);
	OutputResult(text, found, offset, length);

	//===========================
	BeautifulStringParser parser(4);
	found = parser.Find(text, offset, length);
	OutputResult(text, found, offset, length);

	//===========================
	BeautifulStringParser parser2(5);
	found = parser2.Find(text, offset, length);
	OutputResult(text, found, offset, length);

	return 0;
}

