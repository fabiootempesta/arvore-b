#ifndef DBTREE_H
#define DBTREE_H

#include <fstream>
#include <type_traits>


using namespace std;

#include "node.h"
#include "serialChar.h"
#include "record.h"

const ios::openmode mode = ios::in | ios::out | ios::binary;

template <class T, const unsigned int MIN_DEGREE>
class dbtree : private fstream {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      dbtree();
      dbtree(const string name, const string type, const unsigned int ver, ios::openmode openmode = mode);
      virtual ~dbtree();
      bool isOpen();
      bool close();
      void clear();
      bool readRecord(record<node<T,MIN_DEGREE>> &r, unsigned long long int i);
      bool writeRecord(record<node<T,MIN_DEGREE>> &r, unsigned long long int i);
      bool insertRecord(record<node<T, MIN_DEGREE>> r, unsigned long long int i);
      bool deleteRecord(unsigned long long int i);
      bool insert(T k);
      unsigned long long int getFirstValid();
      unsigned long long int getFirstDeleted();
      unsigned long long int search(T data);
   protected:
      header head;
      bool readHeader(header &h);
      bool writeHeader(header &h);
      unsigned long long int index2pos(unsigned long long int i);
      unsigned long long int pos2index(unsigned long long int p);
};

template <class T, const unsigned int MIN_DEGREE>
dbtree<T,MIN_DEGREE>::dbtree() : fstream() {

}

template <class T, const unsigned int MIN_DEGREE>
dbtree<T,MIN_DEGREE>::dbtree(const string name, const string type,
                        const unsigned int ver, ios::openmode openmode) : fstream(name.c_str(), mode) {
    if (!isOpen()){
        fstream::open(name.c_str(), mode | ios::trunc);
        if (isOpen()){
            cout << "--- New file dat created! ---" << endl;
            header aux(type, ver);
            this->head = aux;
            if(writeHeader(aux)){
            cout << "--- Header wrote on file! ---" << endl;
        }
        else
            cout << "--- Error creating the file! ---" << endl;
        }
    }else{
        cout << "--- File found and opened! ---" << endl;
        if(readHeader(head) && head.getType() == type && head.getVersion() == ver){

            cout << "--- Compatible headers, access allowed! ---" << endl;
            if(readHeader(head)){
                header aux(type, ver);
                aux.setFirstValid(head.getFirstValid());
                aux.setFirstDeleted(head.getFirstDeleted());
                this->head = aux;
            }
        }else{ 
            cout << "--- Incompatible headers, access denied! ---" << endl;
            this->close();
        }
     }
}

template <class T, const unsigned int MIN_DEGREE>
dbtree<T,MIN_DEGREE>::~dbtree() {

}



template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::isOpen() {
    return fstream::is_open();
}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::close() {
    fstream::close();
    return !isOpen();
}

template <class T, const unsigned int MIN_DEGREE>
void dbtree<T,MIN_DEGREE>::clear() {

}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::readRecord(record<node<T,MIN_DEGREE>> &r, unsigned long long int i) //i => file.DAT position
{
    if (isOpen()){
        fstream::seekg(i);
        char *aux=new char[r.size()];
        fstream::read(aux,r.size());
        r.fromString(string(aux, r.size()));
        delete aux;
        return fstream::good();
    }
    else{
        cout<<"--- Reading mistake! ---"<<endl;
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::writeRecord(record<node<T,MIN_DEGREE>> &r, unsigned long long int i) //i => logic position
{
    if (isOpen()){
        fstream::seekp(pos2index(i),ios::beg);
        fstream::write(r.toString().c_str(),r.size());
        return fstream::good();
    }
    else{
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::insertRecord(record<node<T, MIN_DEGREE>> r, unsigned long long int i){ 
    r.setNext(this->getFirstValid());
    if(writeRecord(r,index2pos(i)))
        this->head.setFirstValid(i);
    return (writeHeader(this->head));
    
}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::deleteRecord(unsigned long long int i){ 
    record<node<T,MIN_DEGREE>> r1;
    record<node<T,MIN_DEGREE>> r2;
    bool re;
    if (readRecord(r1, i)){

        if(i==this->head.getFirstValid()){
            this->head.setFirstValid(r1.getNext());

        }else{
            unsigned long long int Aux=getFirstValid();
            while(Aux!=0){
                readRecord(r2, Aux);

                if(r2.getNext()==i){
                    r2.setNext(r1.getNext());
                    if(writeRecord(r2,index2pos(Aux))){
                        re=true;
                    }

                }
                Aux=r2.getNext();


            }
        }
    re= true;

    }else{
        cout<<"Error ocurred!"<<endl;
        re=false;
    }
    return re;
}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::insert(T k){ 
    unsigned long long int i = head.getFirstValid();
    
    node<T,MIN_DEGREE> aux;
    cout<<"oprass1\n";
    

    
    
    cout<<"val i: "<<i<<endl;
    if (i==0){
        fstream::seekg(0,ios::end);
        i=fstream::tellg();
    }else
        aux.clear();

    
    cout<<"testeeeeeeeeee\n";
    aux.insertKey(k);
    record<node<T,MIN_DEGREE>> r;
    cout<<"desgraca\n";
    cout<<&r<<endl;
    //r = record<node<T,MIN_DEGREE>> (aux);
    cout<<"testeeeeeeeeee\n";
    cout<<"tentando ver o que tem dentro do node do record:"<<endl;
    cout<<r.getData().sizeN()<<endl; // não sei o porquê, mas o erro está aqui
    cout<<"teste1!"<<endl;
    cout<<"teste2!"<<endl;
    return insertRecord(r,i);
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int dbtree<T,MIN_DEGREE>::getFirstValid(){
    return this->head.getFirstValid();
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int dbtree<T,MIN_DEGREE>::getFirstDeleted(){
    return this->head.getFirstDeleted();
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int dbtree<T,MIN_DEGREE>::search(T data){
    unsigned long long int i= this->head.getFirstValid();
    unsigned long long int re=0;
    record<node<T,MIN_DEGREE>> r;

    while (i != 0) {
        readRecord(r, i);
        for(int i=0;i<r.getData().sizeN();i++)
            if(T(r.getData().getKey(i))==data)
                re=i;
        i=r.getNext();
    }
    return re;

}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::readHeader(header &h)
{
    if (isOpen())
    {
        char *aux = new char[h.size()];
        fstream::seekg(0, ios::beg);
        fstream::read(aux, h.size());
        h.fromString(string(aux, h.size()));
        delete aux;
        return fstream::good();
    }
    else
    {
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
bool dbtree<T,MIN_DEGREE>::writeHeader(header &h)
{
    if (isOpen())
    {
        fstream::seekp(0, ios::beg);
        fstream::write(h.toString().c_str(), h.size());
        return fstream::good();
    }
    else
    {
        return false;
    }
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int dbtree<T,MIN_DEGREE>::index2pos(unsigned long long int i){
    record<node<T,MIN_DEGREE>> aux;
    return ((i - head.size()) / aux.size());
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int dbtree<T,MIN_DEGREE>::pos2index(unsigned long long int p){

    record<node<T,MIN_DEGREE>> aux;
    return  head.size() +(p) * aux.size();

    //return index;
}
#endif // DBTREE_H

