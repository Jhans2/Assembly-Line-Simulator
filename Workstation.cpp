// Name: Jatin Hans
// Seneca Student ID: 141560201
// Seneca email: jhans2@myseneca.ca
// Date of completion: 28 November 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Workstation.h"

using namespace std;

namespace sdds
{
    deque<CustomerOrder> pending;
    deque<CustomerOrder> completed;
    deque<CustomerOrder> incomplete;

    void Workstation::fill(ostream &os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        bool flag = false;

        if (m_orders.empty())
        {
            flag = false;
        }
        else if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)
        {
            if (m_pNextStation != nullptr)
            {
                *m_pNextStation += move(m_orders.front());
            }
            else if (m_orders.front().isFilled())
            {
                completed.push_back(move(m_orders.front()));
            }
            else
            {
                incomplete.push_back(move(m_orders.front()));
            }

            m_orders.erase(m_orders.begin());
            flag = true;
        }
        else
        {
            flag = false;
        }
        return flag;
    }

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(ostream &os) const
    {
        os << getItemName();
        os << " --> ";

        if (m_pNextStation != nullptr)
        {
            os << m_pNextStation->getItemName() << endl;
        }
        else
        {
            os << "End of Line" << endl;
        }
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(move(newOrder));
        return *this;
    }
}