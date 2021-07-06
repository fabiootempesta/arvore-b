#ifndef HEADER_H
#define HEADER_H

#include "serializable.h"

using namespace std;

class header : public serializable {
   public:
      header();
      header(const string t, unsigned int v);
      header(const header &h);
      virtual ~header();
      header operator=(const header &h);
      bool operator==(const header &h);
      unsigned long long int getFirstDeleted() const;
      void setFirstDeleted(unsigned long long int r);
      unsigned long long int getFirstValid() const;
      void setFirstValid(unsigned long long int r);
      string getType() const;
      void setType(string t);
      unsigned int getVersion() const;
      void setVersion(unsigned int v);
      virtual string toString();
      virtual void fromString(string repr);
      virtual string toXML() { return ""; };
      virtual void fromXML(string repr) {};
      virtual string toCSV() { return ""; };
      virtual void fromCSV(string repr){};
      virtual string toJSON() { return ""; };
      virtual void fromJSON(string repr) {};
      virtual unsigned long long int size() const;
   protected:
      string type;
      unsigned int version;
      unsigned long long int firstValid;
      unsigned long long int firstDeleted;
};

header::header() : serializable() {
   //ctor
   type = "***";
   firstDeleted = 0;
   firstValid = 0;
   version = 0;
}

header::header(const string t, unsigned int v) : serializable() {
   // ctor
   type = t.substr(0, 3);
   firstDeleted = 0;
   firstValid = 0;
   version = v;
}

header::header(const header &h) {
   // cpy ctor
   type = h.getType();
   firstDeleted = h.getFirstDeleted();
   firstValid = h.getFirstValid();
   version = h.getVersion();
}

header::~header() {
   //dtor
}

header header::operator=(const header &h) {
   header aux(h);
   if (this == &h)
      return *this;

   type = h.getType();
   firstDeleted = h.getFirstDeleted();
   firstValid = h.getFirstValid();
   version = h.getVersion();

   return aux;
}

bool header::operator==(const header &h) {
   return type == h.getType() && version == h.getVersion() &&
          firstDeleted == h.getFirstDeleted() &&
          firstValid == h.getFirstValid();
}

unsigned long long int header::getFirstDeleted() const {
   return firstDeleted;
}

void header::setFirstDeleted(unsigned long long int r) {
   firstDeleted = r;
}

unsigned long long int header::getFirstValid() const {
   return firstValid;
}

void header::setFirstValid(unsigned long long int r) {
   firstValid = r;
}

string header::getType() const {
   return type;
}

void header::setType(string t) {
   type = t.substr(0, 3);
}

unsigned int header::getVersion() const {
   return version;
}

void header::setVersion(unsigned int v) {
   version = v;
}

string header::toString() {
   string aux = "";
   aux += type;
   aux += string(reinterpret_cast<char*>(&version), sizeof(version));
   aux += string(reinterpret_cast<char*>(&firstValid), sizeof(firstValid));
   aux += string(reinterpret_cast<char*>(&firstDeleted), sizeof(firstDeleted));
   return aux;
}

void header::fromString(string repr) {
   int pos = 0;
   type = repr.substr(pos, 3);
   pos += type.length();
   repr.copy(reinterpret_cast<char*>(&version), sizeof(version), pos);
   pos += sizeof(version);
   repr.copy(reinterpret_cast<char*>(&firstValid), sizeof(firstValid), pos);
   pos += sizeof(firstValid);
   repr.copy(reinterpret_cast<char*>(&firstDeleted), sizeof(firstDeleted), pos);
}

unsigned long long int header::size() const {
   return type.length() + sizeof(version) + sizeof(firstValid) + sizeof(firstDeleted);
}

#endif // HEADER_H
