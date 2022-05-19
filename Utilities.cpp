// Name: Jatin Hans
// Seneca Student ID: 141560201
// Seneca email: jhans2@myseneca.ca
// Date of completion: 15 November 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <algorithm>
#include "Utilities.h"

using namespace std;

namespace sdds
{
    char Utilities::m_delimiter = ' ';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    string Utilities::extractToken(const string &str, size_t &next_pos, bool &more)
    {
        string line_res = "";
        size_t start_pos = next_pos;

        next_pos = str.find(m_delimiter, start_pos);

        if (start_pos == next_pos)
        {
            more = false;
            throw "   ERROR: Nothing Recieved.\n";
        }
        else if (next_pos == string::npos)
        {
            line_res = str.substr(start_pos);
            m_widthField = max(line_res.length(), m_widthField);
            more = false;
        }
        else
        {
            line_res = str.substr(start_pos, next_pos - start_pos);
            m_widthField = max(line_res.length(), m_widthField);
            more = true;
        }

        next_pos++;

        return line_res;
    }
}
