// Name: Jatin Hans
// Seneca Student ID: 141560201
// Seneca email: jhans2@myseneca.ca
// Date of completion: 28 November 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include "Workstation.h"
#include "LineManager.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
    LineManager::LineManager(const string &file, const vector<Workstation *> &stations)
    {

        Utilities util;
        string local_str;
        fstream f(file);
        m_cntCustomerOrder = pending.size();
        m_firstStation = nullptr;

        if (!f)
        {
            throw string("File can't be read");
        }

        while (getline(f, local_str))
        {
            size_t further_pos = 0;
            string curr_line = "";
            string next_line = "";
            bool flag;

            curr_line = util.extractToken(local_str, further_pos, flag);

            if (flag)
            {
                next_line = util.extractToken(local_str, further_pos, flag);
            }
            for_each(stations.begin(), stations.end(), [&](Workstation *station)
                     {
                         if (station->getItemName() == curr_line)
                         {
                             for_each(stations.begin(), stations.end(), [&](Workstation *nextStation)
                                      {
                                          if (nextStation->getItemName() == next_line)
                                          {
                                              station->setNextStation(nextStation);
                                          }
                                      });
                             activeLine.push_back(station);
                         }
                     });
            m_firstStation = activeLine.front();
        }
    }

    void LineManager::linkStations()
    {
        const Workstation *active_stn = m_firstStation;
        size_t i = 0;
        while (active_stn)
        {
            activeLine[i++] = const_cast<Workstation *>(active_stn);
            active_stn = active_stn->getNextStation();
        }
    }

    bool LineManager::run(ostream &os)
    {
        static size_t counter = 0;
        bool flag = false;

        os << "Line Manager Iteration: " << ++counter << endl;

        if (!pending.empty())
        {
            *activeLine.front() += move(pending.front());
            pending.pop_front();
        }

        for (auto src : activeLine)
        {
            src->fill(os);
        }

        for (auto src : activeLine)
        {
            src->attemptToMoveOrder();
        }

        if (m_cntCustomerOrder == completed.size() + incomplete.size())
        {
            flag = true;
        }
        return flag;
    }

    void LineManager::display(ostream &os) const
    {
        for (auto &curr_stn : activeLine)
        {
            if (curr_stn)
            {
                curr_stn->display(os);
            }
        }
    }
}