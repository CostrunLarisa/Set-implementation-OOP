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
    arbore<T>* RecursiveCopy(arbore<T>* ob, arbore<T>* &modifElem);
    bool cautareT(arbore<T>* ,T ElementDeCautat);
    arbore<T>* getAdress(arbore<T>* radacina, T valoare);
    Set<T,key>& operator=(const Set<T,key>& s);

    template<typename V>
    friend ostream& operator<<(ostream& out, Set<V,V>& s); 
    void RecursiveDestructor(arbore<T>* start);
    ~Set();
};
template<typename T,class key>
Set<T,key>::Set() {                                     //constructorul fara parametri care imi creeaza un set gol,i.e un arbore gol=>radacina va fi NULL
    radacina = NULL;
    lungime = 0;
}
template<typename T, class key>
Set<T, key>::Set(T x) {                                 //constructorul fara parametri care imi creeaza 'radacina' arborelui
    comp=comparator<key>;
    radacina = radacina->nod(x);
    lungime++;
};                                  //imi creez un arbore de un singur nod,deoarece vom crea setul prin inserari;
template<typename T, class key>
Set<T, key>::Set(const Set<T, key>& s)
{
    arbore<T>* root = s.radacina;
    this->radacina = root;
    this->lungime = s.lungime;
    RecursiveCopy(root, this->radacina);
}
template<typename T, class key>
bool Set<T, key>::cautareT(arbore<T>* radacina,T ElementDeCautat)
{//returneaza 1 daca un element este gasit,returneaza 0 in caz contrar
    if (radacina == NULL)return 0;                            //daca setul meu este gol nu am cu ce sa compar
    if (comp(ElementDeCautat, radacina->getInfo()) == 1)return 1;
    if(radacina->getStang()!=NULL)                                      //daca am fiu stang atunci continui cautarea in subarborele stang
        return cautareT(radacina->getStang(),ElementDeCautat);
    if (radacina->getDrept() != NULL)                                   //daca am fiu drept atunci continui cautarea in subarborele drept
        return cautareT(radacina->getDrept(),ElementDeCautat);
    return 0;
}
template<typename T, class key>
arbore<T>* Set<T, key>::getAdress(arbore<T>* radacina,T ElementDeCautat)    //metoda care cauta adresa unei valori conform comparatorului
{
    if (radacina == NULL)return nullptr;                            //daca setul meu este gol 
    if (comp(ElementDeCautat, radacina->getInfo()) == 1)return radacina;
    if (radacina->getStang() != NULL)                                      //daca am fiu stang atunci continui cautarea in subarborele stang
        return getAdress(radacina->getStang(), ElementDeCautat);
    if (radacina->getDrept() != NULL)                                   //daca am fiu drept atunci continui cautarea in subarborele drept
        return getAdress(radacina->getDrept(), ElementDeCautat);
    return nullptr;
}

template<typename T, class key>
void Set<T, key>::erase(T y) {
   arbore<T>* aux= getAdress(radacina, y);          //obtin adresa elementului de sters in functie de template ul comparator
   if (aux == nullptr)
   {
       throw std::domain_error("Elementul nu exista"); //in cazul in care trebuie sa stergem ceva ce nu exista aruncam o eroare
   }
   radacina->stergere(radacina,aux->getInfo());     //sterg informatia de la adresa
}

template<typename T, class key>
bool Set<T, key>::find(T x) {
    return cautareT(this->radacina,x);                  //metoda care returneaza 1 daca un element se afla in set,0 in caz contrar
}                                                       //asemanatoare cu cautareT,redenumita 'find' pentru a se asemana cu cea din STL

template<typename T, class key>
void Set<T, key>::insert(T valoare)
{
    if (cautareT(this->radacina,valoare) == 0)   //ne asiguram ca nu avem duplicate pentru a putea insera o noua valoare
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
arbore<T>* Set<T, key>::RecursiveCopy(arbore<T>* start,arbore<T>* &modifElem)
{
    if (start == NULL) return modifElem;                //daca nu mai am nimic atunci am terminat de copiat
    if (start->getStang() != nullptr)
    {
        RecursiveCopy(start->getStang(),modifElem);       //copiez subarborele stang,pentru fiecare nod
        modifElem->inserare(modifElem, start->getStang()->getInfo());
    }

    if (start->getDrept() != nullptr)
    {
        RecursiveCopy(start->getDrept(),modifElem);         //copiez subarborele drept,pentru fiecare nod
        modifElem->inserare(modifElem, start->getDrept()->getInfo());
    }

    modifElem->inserare(modifElem, start->getInfo());
    return modifElem;
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
            return *this;
        }
        else {
            RecursiveCopy(root, this->radacina);        //copiez recursiv ce am in subarborele stang si drept
            return *this;
        }
    }
    return *this;
}

template<typename T, class key=comparator<T> >
ostream& operator<<(ostream& out,Set<T,key>& s)
{
    if (s.getRadacina() == NULL)                                 //in cazul in care setul este vid se arunca o eroare
    {
        throw domain_error("Empty set");
    }
    else {
        s.getRadacina()->SRD(s.getRadacina());                        //in caz contrar apelam parcurgerea stang-radacina-drept din arbore pentru a afisa 
    }                                                      //elementele in ordine crescatoare;
    
    return out;
}

template<typename T, class key>
void Set<T, key>::RecursiveDestructor(arbore<T>* start)
{
    if (start == nullptr)           //cat timp nu am ajung la final
        return;

    if (start->getStang() != nullptr)
    {
        RecursiveDestructor(start->getStang());       //sterg subarborele stang,pentru fiecare nod
    }

    if (start->getDrept() != nullptr)
    {
        RecursiveDestructor(start->getDrept());         //sterg subarborele drept,pentru fiecare nod

    }

    delete start->getDrept();
    delete start->getStang();
}

template<typename T, class key>
Set<T,key>::~Set() {
    if (radacina != nullptr)           //atata timp cat destructorul nu este deja gol,apelez functia recursiva de stergere si reinitializez lungimea
    {
        RecursiveDestructor(radacina);
        lungime = 0;
    }
}
#endif
