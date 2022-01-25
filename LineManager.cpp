// Name: Mohammedamaan Shaikh
// Seneca Student ID: 157304197
// Seneca email: mishaikh3@myseneca.ca
// Date of completion: 30th July
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include <iterator>

#include "Utilities.h"
#include "LineManager.h"
#include "Workstation.h"
using namespace std;
namespace sdds {
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
		string _station = "";
		string _nextStation = "";
		ifstream inputFile(file);
		string station_NextStation;
		if (inputFile) {
			while (!inputFile.eof()) {
				station_NextStation = "";
				getline(inputFile, station_NextStation);
				size_t positionOfdelimitor = station_NextStation.find('|');
				_station = station_NextStation.substr(0, positionOfdelimitor);
				_nextStation = station_NextStation.substr(positionOfdelimitor + 1);
				auto currentStation = find_if(begin(stations), end(stations), [&](Workstation* currentStation) {
						return currentStation->getItemName().compare(_station) == 0;
					});
				if (currentStation != std::end(stations)) {
					auto otherStation = std::find_if(begin(stations), end(stations), [&](Workstation* otherStation)
						{
							return otherStation->getItemName().compare(_nextStation) == 0;
						});
					if (otherStation != std::end(stations))
						(*currentStation)->setNextStation(*otherStation);
					else
						(*currentStation)->setNextStation(nullptr);
					activeLine.push_back(*currentStation);
				}
			}
		}
		for (auto i = activeLine.begin(); i != activeLine.end(); i++) {
			int value = count_if(activeLine.begin(), activeLine.end(), [i](Workstation* s) {
				return 	s->getNextStation() == *i;
				});
			if (value == 0) {
				m_firstStation = *i;
				break;
			}
		}
		m_cntCustomerOrder = pending.size();
	}
	bool LineManager::run(std::ostream& os) {
		static size_t localCounter = 0;
		++localCounter;
		os << "Line Manager Iteration: " << localCounter << "\n";

		if (!pending.empty())
		{
			(*m_firstStation) += std::move(pending.front());
			pending.pop_front();
		}

		std::for_each(begin(activeLine), end(activeLine), [&](Workstation* currentStation) { currentStation->fill(os); });
		std::for_each(begin(activeLine), end(activeLine), [&](Workstation* currentStation) { currentStation->attemptToMoveOrder(); });

		return (completed.size() + incomplete.size()) == m_cntCustomerOrder ? true : false;
	}

	void LineManager::linkStations()
	{
		vector<Workstation*> WORKSTATION_TEMP;
		WORKSTATION_TEMP.push_back(m_firstStation);
		WORKSTATION_TEMP.push_back(m_firstStation->getNextStation());
		auto findNextStationAndPush = [&](const Workstation* station) {
			WORKSTATION_TEMP.push_back(WORKSTATION_TEMP.back()->getNextStation());
		};
		std::for_each(begin(activeLine), end(activeLine) - 2, findNextStationAndPush);
		activeLine.erase(begin(WORKSTATION_TEMP), begin(WORKSTATION_TEMP) + WORKSTATION_TEMP.size());
		activeLine.assign(begin(WORKSTATION_TEMP), end(WORKSTATION_TEMP));
	}
	void LineManager::display(std::ostream& os)const
	{
		for (auto& currentStation : activeLine)
			currentStation->display(os);
	}
}