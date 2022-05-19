// Name: Jatin Hans
// Seneca Student ID: 141560201
// Seneca email: jhans2@myseneca.ca
// Date of completion: 15 November 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;

namespace sdds
{
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    const string &Station::getItemName() const
    {
        return m_name;
    }

    size_t Station::getNextSerialNumber()
    {
        m_next_num++;
        return m_next_num - 1;
    }

    size_t Station::getQuantity() const
    {
        return m_num_items;
    }

    void Station::updateQuantity()
    {
        if (m_num_items == 0 || m_num_items < 0)
        {
            m_num_items = 0;
        }
        else
        {
            --m_num_items;
        }
    }

    Station::Station(const string &src)
    {
        Utilities obj;
        size_t position = 0;
        bool flag = true;
        m_id = ++id_generator;

        try
        {
            m_name = obj.extractToken(src, position, flag);
            m_next_num = stoi(obj.extractToken(src, position, flag));
            m_num_items = stoi(obj.extractToken(src, position, flag));
            m_widthField = max(obj.getFieldWidth(),m_widthField);
            m_desc = obj.extractToken(src, position, flag);
        }
        catch (string err)
        {
            cout << err;
        }
    }

    void Station::display(std::ostream &os, bool full) const
    {
        os << "[" << right << setw(3) << setfill('0') << m_id << "]";
        os << " Item: " << left << setw(m_widthField) << setfill(' ') << m_name;
        os << " [" << right << setw(6) << setfill('0') << m_next_num << "]";

        if (full==false)
        {
            os << endl;
        }
        else
        {
            os << " Quantity: " << left << setw(m_widthField) << setfill(' ') << m_num_items;
            os << " Description: " << m_desc << endl;
        }
    }
}