// Name: Jatin Hans
// Seneca Student ID: 141560201
// Seneca email: jhans2@myseneca.ca
// Date of completion: 22 November 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder()
    {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    }

    CustomerOrder::CustomerOrder(const string &src) : CustomerOrder()
    {
        if (src != "")
        {
            Utilities util;
            auto flag = true;
            size_t curr_pos = 0;

            m_name = util.extractToken(src, curr_pos, flag);
            m_product = util.extractToken(src, curr_pos, flag);
            m_lstItem = new Item *[m_cntItem + 1];
            m_lstItem[m_cntItem] = new Item(util.extractToken(src, curr_pos, flag));
            m_cntItem++;

            while (flag)
            {
                Item **obj = new Item *[m_cntItem + 1];
                for (size_t i = 0; i < m_cntItem; i++)
                {
                    obj[i] = m_lstItem[i];
                }
                obj[m_cntItem] = new Item(util.extractToken(src, curr_pos, flag));
                delete[] m_lstItem;
                m_lstItem = obj;
                m_cntItem++;
                if (util.getFieldWidth() > m_widthField)
                {
                    m_widthField = util.getFieldWidth();
                }
            }
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder &src)
    {
        throw "Copy operation is not allowed";
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept 
    {
        if (this != &src)
        {
            *this = move(src);
        }
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept
    {
       if (this != &src)
        {
            if (m_lstItem)
            {
                for (size_t i = 0; i < m_cntItem; i++)
                {
                    delete m_lstItem[i];
                    m_lstItem[i] = nullptr;
                }
                delete[] m_lstItem;
                m_lstItem = nullptr;
            }

            m_lstItem = src.m_lstItem;
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;

            src.m_lstItem = nullptr;
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
        }
        return *this;
    }

   bool CustomerOrder::isFilled() const
    {
        bool res = true;

        for (size_t i = 0; i < m_cntItem; ++i)
        {
            if (!m_lstItem[i]->m_isFilled)
            {
                res = false;
            }
        }
        return res;
    }

    bool CustomerOrder::isItemFilled(const string &itemName) const
    {
        bool res = false;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName)
            {
                return m_lstItem[i]->m_isFilled;
            }
            else
            {
                res = true;
            }
        }
        return res;
    }
	
    void CustomerOrder::fillItem(Station &station, ostream &os)
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName())
            {
                if (station.getQuantity() > 0)
                {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    station.updateQuantity();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled ";
                }
                else
                {
                    os << "    Unable to fill ";
                }

                os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
        }
    }

    void CustomerOrder::display(ostream &os) const
    {
        os << m_name << " - " << m_product << endl;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << setfill('0') << right << setw(6);
            os << m_lstItem[i]->m_serialNumber;
            os << "] " << setfill(' ');
            os << setw(m_widthField);
            os << left << m_lstItem[i]->m_itemName << setfill(' ') << " - ";
            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
        }
    }

    CustomerOrder::~CustomerOrder()
    {
        if (m_lstItem)
        {
            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            m_lstItem = nullptr;
        }
    }
}