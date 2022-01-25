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
using namespace std;
namespace sdds {
	char Utilities::m_delimiter = ' ';
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		string ret{};
		size_t pos = next_pos;
		next_pos = str.find(m_delimiter, pos);
		if (next_pos == string::npos) {
			ret = str.substr(pos);
			m_widthField = max(ret.length(), m_widthField);
			more = false;
		}
		else if (pos == next_pos) {
			more = false;
			throw "No token between delimiters!";
		}
		else {
			ret = str.substr(pos, next_pos - pos);
			m_widthField = max(ret.length(), m_widthField);
			more = true;
		}
		next_pos++;
		return ret;
	}
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}