// Name: Mohammedamaan Shaikh
// Seneca Student ID: 157304197
// Seneca email: mishaikh3@myseneca.ca
// Date of completion: 30th July
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder() {
	}
	CustomerOrder::CustomerOrder(const std::string& record) {
		Utilities u;
		bool ok;
		string line;
		size_t start = 0;
		Item** extra{};
		m_name = u.extractToken(record, start, ok);
		if (ok == true) {
			m_product = u.extractToken(record, start, ok);
		}
		if (m_widthField < u.getFieldWidth()) {
			m_widthField = u.getFieldWidth();
		}
		while (ok) {
			Item* newItem = nullptr;
			if (m_cntItem == 0) {
				line = u.extractToken(record, start, ok);
				delete[] m_lstItem;
				m_lstItem = new Item * [m_cntItem + 1];
				delete newItem;
				newItem = new Item(line);
				m_lstItem[0] = newItem;
			}
			else {
				line = u.extractToken(record, start, ok);
				delete newItem;
				newItem = nullptr;
				newItem = new Item(line);
				delete[] extra;
				extra = new Item * [m_cntItem];
				for (size_t i = 0; i < m_cntItem; i++) {
					extra[i] = m_lstItem[i];
				}
				delete[] m_lstItem;
				m_lstItem = new Item * [m_cntItem + 1];
				for (size_t i = 0; i < m_cntItem; i++) {
					m_lstItem[i] = extra[i];
				}
				m_lstItem[m_cntItem] = newItem;
			}
			m_cntItem++;
		}
		delete[] extra;
		extra = nullptr;
	}
	CustomerOrder::~CustomerOrder() {
		for (auto i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	bool CustomerOrder::isFilled()const {
		bool retval = true;
		bool ok = false;
		for (auto i = 0u; i < m_cntItem; i++ && ok == false) {
			if (!m_lstItem[i]->m_isFilled) {
				retval  = false;
				ok = true;
			}
		}
		return retval;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName)const {
		bool retval = false;
		size_t i = 0;
		for (i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				retval = m_lstItem[i]->m_isFilled;
				break;
			}
		}
		if (i == m_cntItem){
			retval = true;
		}
		return retval;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os){
		if (!isItemFilled(station.getItemName()) && station.getQuantity() > 0) {
			for (auto i = 0u; i < m_cntItem; i++) {
				if (m_lstItem[i]->m_itemName == station.getItemName()) {
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os<< right << "    Filled " << left << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					station.updateQuantity();
				}
			}
		}
		else if (station.getQuantity() == 0 && !isItemFilled(station.getItemName())) {
			for (auto i = 0u; i < m_cntItem; i++) {
				if (m_lstItem[i]->m_itemName == station.getItemName()) {
					os << right << "    Unable to fill " << left << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& cusor) {
		throw "copy not allowed for customerorder!\n";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& cusor)noexcept {
		*this = move(cusor);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cusor)noexcept {
		if (this != &cusor) {
			swap(m_lstItem, cusor.m_lstItem);
			m_name = cusor.m_name;
			m_product = cusor.m_product;
			m_cntItem = cusor.m_cntItem;
			cusor.m_name.clear();
			cusor.m_product.clear();
			cusor.m_cntItem = 0;
			delete[] cusor.m_lstItem;
			cusor.m_lstItem = nullptr;
		}
		return *this;
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (auto j = 0u; j < m_cntItem; j++) {
			os << "[";
			os.fill('0');
			os.width(6);
			os << right << m_lstItem[j]->m_serialNumber << "] ";
			os.fill(' ');
			os.width(m_widthField);
			os << left << m_lstItem[j]->m_itemName << " - " << (m_lstItem[j]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}
}