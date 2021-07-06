#ifndef SERIALCHAR_H
#define SERIALCHAR_H

#include "serializable.h"

class serialChar : serializable {
   public:
      serialChar();
      serialChar(char c);
      serialChar(const serialChar& other);
      virtual ~serialChar();
      serialChar operator=(const serialChar& other);
      bool operator==(const serialChar &other) const;
      bool operator<(const serialChar &other) const;
      bool operator<=(const serialChar &other) const;
      bool operator>(const serialChar &other) const;
      bool operator>=(const serialChar &other) const;
      bool operator!=(const serialChar &other) const;
      serialChar operator+(const serialChar& other) const;
      serialChar operator-(const serialChar& other) const;
      serialChar operator*(const serialChar& other) const;
      serialChar operator/(const serialChar& other) const;
      void operator++();
      void operator--();
      void setValue(char c);
      char getValue() const;
      virtual string toString();
      virtual void fromString(string repr);
      virtual string toXML();
      virtual void fromXML(string repr);
      virtual string toCSV();
      virtual void fromCSV(string repr);
      virtual string toJSON();
      virtual void fromJSON(string repr);
      virtual unsigned long long int size() const;
   protected:
      char value;
};

serialChar::serialChar() : serializable() {
    //this->value='';
}

serialChar::serialChar(char c) : serializable() {
    this->value=c;
}

serialChar::serialChar(const serialChar& other) {
    this->value=other.getValue();
}

serialChar::~serialChar() {

}

serialChar serialChar::operator=(const serialChar& other) {
    serialChar aux(other);
    if(this == &other)
        return *this;


    this->value = other.getValue();
    return aux;
}

bool serialChar::operator==(const serialChar &other) const {
    return this->value == other.getValue();
}

bool serialChar::operator<(const serialChar &other) const {
    return this->value < other.getValue();
}

bool serialChar::operator<=(const serialChar &other) const {
    return this->value <= other.getValue();
}

bool serialChar::operator>(const serialChar &other) const {
    return this->value > other.getValue();
}

bool serialChar::operator>=(const serialChar &other) const {
    return this->value >= other.getValue();
}

bool serialChar::operator!=(const serialChar &other) const {
    return this->value != other.getValue();
}

serialChar serialChar::operator+(const serialChar& other) const {
    serialChar aux;
	aux.setValue(this->value+other.getValue());
	return aux;
}

serialChar serialChar::operator-(const serialChar& other) const {
    serialChar aux;
	aux.setValue(this->value-other.getValue());
	return aux;
}

serialChar serialChar::operator*(const serialChar& other) const {
    serialChar aux;
	aux.setValue(this->value*other.getValue());
	return aux;
}

serialChar serialChar::operator/(const serialChar& other) const {
    serialChar aux;
	aux.setValue(this->value/other.getValue());
	return aux;
}

void serialChar::operator++() {
    this->value++;
}

void serialChar::operator--() {
    this->value--;
}

void serialChar::setValue(char c) {
    this->value=c;
}

char serialChar::getValue() const {
    return this->value;
}

string serialChar::toString() {
    string aux = "";
    aux += string(reinterpret_cast<char*>(&value), sizeof(value));
    return aux;
}

void serialChar::fromString(string repr) {
    repr.copy(reinterpret_cast<char*>(&value), sizeof(value));
}

string serialChar::toXML() {
    return"";
}

void serialChar::fromXML(string repr) {

}

string serialChar::toCSV() {
    return"";
}

void serialChar::fromCSV(string repr) {

}

string serialChar::toJSON() {
    return"";
}

void serialChar::fromJSON(string repr) {

}

unsigned long long int serialChar::size() const {
    return sizeof(value);
}


#endif // serialChar_H
