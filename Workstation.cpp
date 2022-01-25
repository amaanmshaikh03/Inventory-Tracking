// Name: Mohammedamaan Shaikh
// Seneca Student ID: 157304197
// Seneca email: mishaikh3@myseneca.ca
// Date of completion: 30th July
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include<iostream>
#include "Workstation.h"
using namespace std;
namespace sdds {
	deque<CustomerOrder> pending{};
	deque<CustomerOrder> completed{};
	deque<CustomerOrder> incomplete{};
	Workstation::Workstation(const string& str) :Station(str) {
	}
	void Workstation::fill(ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder() {
		bool ok = false;
		if (m_orders.empty()) {
			ok = false;
		}
		else if (m_orders.front().isItemFilled(getItemName()) == true) {
			if (m_pNextStation == nullptr) {
				completed.push_back(std::move(m_orders.front()));
			}else{
			*m_pNextStation += std::move(m_orders.front());
			}
			m_orders.pop_front();
			ok = true;
		}
		else {
			if (getQuantity() == 0) {
				if (m_pNextStation == nullptr) {
					incomplete.push_back(m_orders.front());
				}
				else {
					*m_pNextStation += std::move(m_orders.front());
				}
				m_orders.pop_front();
				ok = true;
			}
		}
		deque<CustomerOrder> temp = move(completed);
		int size = temp.size();
		for (int i = 0; i < size; i++) {
			if (temp.front().isFilled()) {
				completed.push_back(move(temp.front()));
			}
			else {
				incomplete.push_back(move(temp.front()));
			}
			temp.pop_front();
		}
		return ok;
	}
	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}
	void Workstation::display(ostream& os)const {
		if (m_pNextStation != nullptr) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << "\n";
		}
		else {
			os << getItemName() << " --> " << "End of Line\n";
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}