#ifndef SET_H
#define SET_H
#include <iostream>
#include "Arbore.h"
#include <vector>
#include<string.h>
#include<exception>
using namespace std;

template <typename F1>                  //template care verifica daca doua tipuri
                                        //de date sunt egale
class comparator {
public:
    bool operator()(F1 x, F1 y) {
        return x == y;
    }

};
template<>
bool comparator<int>::operator ()(int x, int y) //specializarea template-ului pentru
                                                //verificarea paritatii a doi intregi
{
    return(x % 2 == y % 2);
}


template <typename T,class key=comparator<T> >
class Set
{
    arbore<T>* radacina;
    key comp;
    int lungime;
public:

	
    Set();

    Set(T x);

    Set(const Set& s);

    void erase(T y);

    bool find(T x);

    void insert(T valoare);

    arbore<T>* getRadacina();

    int size();

    Set<T,key>& operator=(const Set<T,key>& s);
    //friend ostream& operator<<(ostream& out, Set<T,key>& s);
    ~Set();
};
template<typename T,class key>
Set<T,key>::Set() {                                     //constructorul fara parametri care imi creeaza un set gol,i.e un arbore gol=>radacina va fi NULL
    radacina = NULL;
    lungime = 0;
}
template<typename T, class key>
Set<T, key>::Set(T x) {                                 //constructorul fara parametri care imi creeaza 'radacina' arborelui
    radacina = radacina->nod(x);
    lungime++;
};                                  //imi creez un arbore de un singur nod,deoarece vom crea setul prin inserari;
template<typename T, class key>
Set<T, key>::Set(const Set<T, key>& s)
{
    arbore<T>* root = s.radacina;
    this->lungime = s.lungime;
    while (true)
    {
        if (root->getStang() != NULL)
        {
            this->radacina->setStang(root->getStang());
            root = root->getStang();
        }
        else if (root->getDrept() != NULL)
        {
            this->radacina->setDrept(root->getDrept());
            root = root->getDrept();
        }
        return;
    }
}

template<typename T, class key>
void Set<T, key>::erase(T y) {
    radacina->stergere(radacina, y);
    lungime--;
}

template<typename T, class key>
bool Set<T, key>::find(T x) {
    return radacina->cautare(radacina, x);
}

template<typename T, class key>
void Set<T, key>::insert(T valoare)
{
    if (radacina->cautare(radacina, valoare) == 0)   //ne asiguram ca nu avem duplicate pentru a putea insera o noua valoare
    {
        radacina->inserare(radacina, valoare);
        this->lungime = lungime + 1;                    //la fiecare inserare crestem marimea setului
    }
    else return;
}

template<typename T, class key>
arbore<T>* Set<T, key>::getRadacina()
{
    return radacina;
}

template<typename T, class key>
int Set<T, key>::size()
{
    if (this->radacina == NULL)return 0;  //in cazul in care am un set gol;
    return lungime;
}

template<typename T, class key>
Set<T,key>& Set<T,key>:: operator=(const Set<T,key>& s)
{
    arbore<T>* root = s.radacina;
    if (this != &s)
    {
        this->~Set();                               //distrug ceea ce era inainte in obiectul pe care vreau sa il modific
        this->lungime = s.lungime;

        if (root->getStang() == NULL && root->getDrept() == NULL)       //daca nu exista fii,atunci avem doar radacina si o copiem
        {
            this->radacina = root;
        }
        else {
            while (true)                                                    //in caz contrar,cat timp nu am ramas fara fii,inserezin obiectul meu curent
                                                                            //nodurile obiectului primit
            {
                if (root->getStang() != NULL)
                {
                    radacina->inserare(radacina, root->getStang()->getInfo());
                    root = root->getStang();
                }
                else if (root->getDrept() != NULL)
                {
                    radacina->inserare(radacina, root->getDrept()->getInfo());
                    root = root->getDrept();
                }
                return *this;
            }
        }
    }
    return *this;
}

template<typename T, class key>
ostream& operator<<(ostream& out,Set<T,key>& s)
{
    if (s.getRadacina() == NULL)                                 //in cazul in care setul este vid se arunca o eroare
    {
        throw std::domain_error("Empty set");
    }
    else {
        s.getRadacina()->SRD(s.getRadacina());                        //in caz contrar apelam parcurgerea stang-radacina-drept din arbore pentru a afisa 
                                                            //elementele in ordine crescatoare;
    }
    return out;
}

template<typename T, class key>
Set<T,key>::~Set() {
    while (this->radacina->getStang() != NULL || this->radacina->getDrept() != NULL)  //atata timp cat am si fiu stang si fiu drept incepstergerea
    {
        if (radacina->getStang() != NULL)
        {
            arbore<T>* aux = radacina;
            radacina = radacina->getStang();
            delete aux;
        }
        if (radacina->getDrept() != NULL)
        {
            arbore<T>* auxx = radacina;
            radacina = radacina->getDrept();
            delete auxx;
        }
    }
    lungime = 0;
    arbore<T>* aux = radacina;                      //daca nu am fii sau daca am sters toti fiii,radacina este stearsa si ea si devina null
    delete aux;
    radacina = NULL;
}
#endif
