// Name: Mohammedamaan Shaikh
// Seneca Student ID: 157304197
// Seneca email: mishaikh3@myseneca.ca
// Date of completion: 30th July
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#pragma once
#include <iostream>
using namespace std;
namespace sdds {
	class Station {
		int id{};
		std::string name{};
		std::string desc{};
		size_t serialnum{};
		size_t currentnum{};
		static size_t m_widthField;
		static int id_generator;
	public:
		Station() {};
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream&, bool) const;
	};
}