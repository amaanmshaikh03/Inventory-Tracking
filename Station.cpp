// Name: Mohammedamaan Shaikh
// Seneca Student ID: 157304197
// Seneca email: mishaikh3@myseneca.ca
// Date of completion: 30th July
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Utilities.h"
#include "Station.h"
using namespace std;
namespace sdds {
	size_t Station::m_widthField = 0;
	int Station::id_generator = 1;
	Station::Station(const std::string& STRING) {
		id = id_generator;
		Utilities U;
		size_t N = 0;
		bool M = true;
		try {
			name = U.extractToken(STRING, N, M);
			serialnum = stoi(U.extractToken(STRING, N, M));
			currentnum = stoi(U.extractToken(STRING, N, M));
			m_widthField = max(U.getFieldWidth(), m_widthField);
			desc = U.extractToken(STRING, N, M);
		}
		catch (string& message) {
			cout << message;
		}
		id_generator++;
	}
	const std::string& Station::getItemName() const {
		return name;
	}
	size_t Station::getNextSerialNumber() {
		serialnum++;
		return serialnum - 1;
	}
	size_t Station::getQuantity() const {
		return currentnum;
	}
	void Station::updateQuantity() {
		currentnum--;
		if (currentnum < 0) {
			currentnum = 0;
		}
	}
	void Station::display(std::ostream& os, bool full) const {
		ios init(NULL);
		init.copyfmt(cout);
		os << right << "[";
		os.width(3);
		os.fill('0');
		os << id << "]";
		os << left;
		os << " Item: ";
		os.width(m_widthField);
		os.fill(' ');
		os << name;
		os << right;
		os << " [";
		os.width(6);
		os.fill('0');
		os << serialnum << "]";
		os << left;
		if (full == false) {
			os << endl;
		}
		else {
			os << " Quantity: ";
			os.width(m_widthField);
			os.fill(' ');
			os << currentnum << " Description: ";
			os.copyfmt(init);
			os << desc << endl;
		}
	}
}