// Name: Jatin Hans
// Seneca Student ID: 141560201
// Seneca email: jhans2@myseneca.ca
// Date of completion: 15 November 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
using namespace std;

namespace sdds
{
    class Station
    {
    private:
        int m_id{0};
        string m_name{""};
        string m_desc{""};
        size_t m_next_num;
        size_t m_num_items;
        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const string &src);
        const string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(ostream &os, bool full) const;
    };
}
#endif