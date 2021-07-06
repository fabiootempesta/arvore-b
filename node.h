#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include "serializable.h"
#include "serialChar.h"

template <class T, const unsigned int MIN_DEGREE>
class node : public serializable {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      node<T, MIN_DEGREE>();
      node<T, MIN_DEGREE>(T c);
      node<T, MIN_DEGREE>(const node<T, MIN_DEGREE> &other);
      virtual ~node();
      void clear();
      bool isLeaf() const;
      unsigned int sizeN() const;
      void insertKey(T k);
      unsigned int hasKey(T k);
      T getKey(int i) const;
      void setKey(T k, unsigned int i);
      unsigned long long int getChild(unsigned int i) const;
      void setChild(unsigned long long int c, unsigned int i);
      int tamVet();
      node<T, MIN_DEGREE> operator=(const node<T, MIN_DEGREE> &other);
      virtual string toCSV() { return ""; }
      virtual void fromCSV(string repr) {}
      virtual string toJSON() { return ""; }
      virtual void fromJSON(string repr) {}
      virtual string toXML() { return ""; }
      virtual void fromXML(string repr) {}
      virtual string toString();
      virtual void fromString(string repr);
      virtual unsigned long long int size() const;
      static const unsigned int MAX = 2 * MIN_DEGREE - 1;
      static const unsigned int MIN = MIN_DEGREE - 1;
      static const unsigned int NOT_FOUND = -1;
   protected:
      unsigned int n; //number of elements
      vector<T> value;
      vector<unsigned long long int> children;
      bool leaf;
};

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node() : serializable() {
    this->leaf=true;
    this->n=0;
    this->value.resize(MAX);
    this->children.resize(MAX+1);
    for (int i=0; i<MAX;i++){
        value[i] = T(0);
        children[i] = 0;
    }
    children[MAX] = 0;
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(T c) : serializable() {
    //this->value=c;
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(const node<T, MIN_DEGREE> &other) {
    for(int i=0;i<other.sizeN();i++){
        value[i]=other.getKey(i);
        children[i]=other.getChild(i);        
    }
    children[other.sizeN()]=other.getChild(other.sizeN());
    leaf=other.isLeaf();
    n=other.sizeN();
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::~node() {

}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::clear(){
    this->leaf=true;
    this->n=0;
    this->value.resize(MAX);
    this->children.resize(MAX+1);
    for (int i=0; i<MAX;i++){
        value[i] = T(0);
        children[i] = 0;
    }
    children[MAX] = 0;
}

template <class T, const unsigned int MIN_DEGREE>
bool node<T, MIN_DEGREE>::isLeaf() const {
    return leaf;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int node<T, MIN_DEGREE>::sizeN() const {
   return n;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::insertKey(T k) {
    int i = n - 1;
    while (i >= 0 && k < value[i]) {
        value[i + 1] = value[i];
        i--;
    }
    value[i + 1] = k;
    n=n+1;
    cout<<"valor de n dentro de insertKey: "<<n<<endl;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int node<T, MIN_DEGREE>::hasKey(T k) {
    unsigned int i = 0;
    int pos = -1;

    while (i < n && pos == -1) {
        if (value[i] == k) {
            pos = i;
        }
        i++;
    }

    return pos;
}

template <class T, const unsigned int MIN_DEGREE>
T node<T, MIN_DEGREE>::getKey(int i) const {
   return value[i];
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setKey(T k, unsigned int i) {
   value[i] = k;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int node<T, MIN_DEGREE>::getChild(unsigned int i) const  {
   return children[i];
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setChild(unsigned long long int c, unsigned int i) {
   if (c) {
      children[i] = c;
      leaf = false;
   }
}

template <class T, const unsigned int MIN_DEGREE>
int node<T, MIN_DEGREE>::tamVet(){
    return value.size();
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE> node<T, MIN_DEGREE>:: operator=(const node<T, MIN_DEGREE> &other){
    node<T, MIN_DEGREE> aux(other);
    if(this == &other)
        return *this;

    this->value.resize(other.MAX);
    this->children.resize(other.MAX+1);
    this->n = other.sizeN();
    this->leaf = other.isLeaf();
    for(int i = 0; i < other.sizeN(); i++){
        this->value[i] = other.getKey(i);
        this->children[i] = other.getChild(i);
    }
    this->children[other.sizeN()]=other.getChild(other.sizeN());

    return aux;
}

template <class T, const unsigned int MIN_DEGREE>
string node<T, MIN_DEGREE>::toString() {
    string aux = "";
    aux += string(reinterpret_cast<char*>(&n), sizeof(n));
    for(int i=0;i<n;i++)
        aux += string(reinterpret_cast<char*>(&value[i]), sizeof(value[i]));
    
    for(int i=0;i<n+1;i++)
        aux += string(reinterpret_cast<char*>(&children[i]), sizeof(children[i]));

    aux += string(reinterpret_cast<char*>(&leaf), sizeof(leaf));
    return aux;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::fromString(string repr) {
    int pos=0;
    repr.copy(reinterpret_cast<char*>(&n), sizeof(n),pos);
    pos+=sizeof(n);

    for(int i=0;i<n;i++){
        repr.copy(reinterpret_cast<char*>(&value[i]), sizeof(value[i]),pos);
        pos+=sizeof(value[i]);
    }

    for(int i=0;i<n+1;i++){
    repr.copy(reinterpret_cast<char*>(&children[i]), sizeof(children[i]),pos);
    pos+=sizeof(children[i]);
    }

    repr.copy(reinterpret_cast<char*>(&children[n]), sizeof(children[n]),pos);
    pos+=sizeof(children[n]);

    repr.copy(reinterpret_cast<char*>(&leaf), sizeof(leaf),pos);
    pos+=sizeof(leaf);
    
}



template <class T, const unsigned int MIN_DEGREE>
unsigned long long int node<T, MIN_DEGREE>::size() const {
    return (sizeof(value[0])*n+sizeof(children[0])*(n+1)+sizeof(leaf)+sizeof(n));
}


#endif // NODE_H
