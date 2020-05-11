#pragma once
#ifndef SET_H
#define SET_H
#include <iostream>
#include <vector>
#include<string.h>
#include<exception>
using namespace std;

template<typename T>
class arbore
{
    T info;
    int inaltime;
    arbore* stang;
    arbore* drept;

public:
    arbore():stang(NULL),drept(NULL),info(NULL),inaltime(0) {           //constructorul fara parametri pentru arbore

    }
  
    arbore* getStang() {
        if (this == NULL)return NULL;
        return stang;
    }           //getter pentru nodul stang
    arbore* getDrept() {            //getter pentru nodul drept
        if (this == NULL)return NULL;
        return drept;
    }
    T getInfo() {                   //getter pentru valoarea din nod
        return info;
    }
    void setInfo(T val) {       //setter pentru valoarea din nod
        info = val;
    }
    void setStang(arbore* val) {            //setter pentru nod stang
        this->stang = val;
    }
    void setDrept(arbore* val) {            //setter pentru nod drept
        this->drept = val;
    }
    arbore* nod(T x)                            //metoda prin care creez un nod nou din arbore; pentru a nu mai folosi o alta clasa="nod"
                                                //am consiederat un nod drept fiind un arbore de un singur element
    {
        arbore* p = new arbore;
        p->info = x;
        p->stang = NULL;
        p->drept = NULL;
        p->inaltime = 1;
        return p;
    }
    int getInaltime() {                     //getter pentru inaltimea unei radacini,daca aceasta este null inaltime=0;deci intoarce 0
        if(this!=NULL)return inaltime;
        return 0;
    }
    arbore* inserare(arbore* &radacina, T x)
    {
        arbore* p = nod(x);
        if (radacina == NULL)        //daca arborele este gol si am apelat  constructorul fara parametri
                                               //asta inseamna ca am creat obiectul set,insa nu are nici o informati
                                               //asa ca punem informatia in setul gol creat;
        {
            radacina = nod(x);
            return radacina;
        }
        arbore* aux = radacina;
        arbore* parinte = NULL;     //retinem ultimul parinte
        while (aux != NULL)
        {
            parinte = aux;
            if (x < aux->info)      //cautam sa vedem unde trebuie sa inseram astfel incat sa pastram proprietatile:cele mai mari valori in dreapta
                                    //cele mai mici valori in stanga
                aux = aux->stang;
            else
                aux = aux->drept;
        }
        if (parinte == NULL)
            parinte = p;
        else if (x < parinte->getInfo()) {
            parinte->setStang(p);
        }
        else parinte->setDrept(p);
        if(parinte->stang!=NULL && parinte->drept!=NULL)
            {
            if (parinte->stang->inaltime > parinte->drept->inaltime)
                parinte->inaltime = 1 + parinte->stang->inaltime;
            else parinte->inaltime = 1 + parinte->drept->inaltime;
            }
        if (parinte->stang == NULL && parinte->drept != NULL)
            parinte->inaltime = 1 + parinte->drept->inaltime;
        if(parinte->drept==NULL &&parinte->stang!=NULL)
            parinte->inaltime = 1 + parinte->stang->inaltime;
        int dif_inaltime = checkHeight(parinte);
        
        if (dif_inaltime > 1 && checkHeight(parinte->stang) > 0)
            return rotatieDreapta(parinte);
        if (dif_inaltime > 1 && checkHeight(parinte->stang) < 0)
        {
            parinte->stang = rotatieStanga(parinte->stang);
            return rotatieDreapta(parinte);
        }
        if (dif_inaltime < -1 && checkHeight(parinte->drept) < 0)
            parinte = rotatieStanga(parinte);
        if (dif_inaltime < -1 && checkHeight(radacina->drept) > 0)
        {
            parinte->drept = rotatieDreapta(parinte->drept);
            return rotatieStanga(parinte);
        }
        return parinte;
    }
    bool cautare(arbore* radacina, T x)
    {
        if (radacina == NULL)
            return 0;
        if (radacina->getInfo() == x)
            return 1;
        bool st = cautare(radacina->stang, x);
        if (st)return 1;
        bool dr = cautare(radacina->drept, x);
        return dr;
    }
    void SRD(arbore* radacina)
    {
        if (radacina != NULL)
        {
            SRD(radacina->stang);
            cout << radacina->info<< " ";
            SRD(radacina->drept);
        }

    }                   //parcurgere SRD care imi afiseaza elementele arborelui in ordine crescatoare
  
    arbore* getMinim(arbore* radacina)
    {
        arbore* p = radacina;
        while (p && p->stang != NULL)
            p = p->stang;
        return p;
    }
    arbore* getMaxim(arbore* radacina)
    {
        arbore* p = radacina;
        while (p && p->getDrept() != NULL)
            p = p->getDrept();
        return p;
    }
 
    void setParent(arbore*& aux, arbore*& parinte, T x)  //metoda care imi cauta parintele valorii pe care doresc sa o sterg
    {
        while (aux != NULL && aux->info != x) //cat timp nu sunt pe nodul pe care doresc sa il sterg
        {
            parinte = aux;                 //'parinte' imi retine radacina unui nod de valoare x
            if (x < aux->info)              //daca x < valoare din nodul parinte curent,atunci ma uit in stanga
                aux = aux->stang;
            else
                aux = aux->drept;      //daca valoarea e mai mare inseamna ca nodul se afla in partea dreapta,i.e si parintele lui
        }
    }
    arbore* stergere(arbore* &radacina, T x)
    {
        arbore* y = NULL;
        arbore* aux = radacina;
        setParent(aux, y, x);
        if (aux->stang == NULL && aux->drept == NULL)       //daca nu avem nici fiu drept,nici fiu stang
        {
            if (aux != radacina)                        //daca nodul din care trebuie sa sterg valoarea nu e radacina
            {
                if (y->stang == aux)                    //daca nodul de sters este fiul stang
                    y->stang = NULL;
                else y->drept = NULL;                   //daca nodul de sters este fiul drept al parintelui
            }
            else {
                radacina = NULL;
            }
            delete aux;
        }
        else if (aux->stang && aux->drept)      //daca avem si fiu drept si fiu stang 
        {
            arbore* nou = getMinim(aux->drept);     //salvam minimul de pe subarborele drept
            T cheie = nou->info;
            stergere(radacina, nou->info);
            aux->info = cheie;
        }
        else {
            arbore* q = (aux->stang) ? aux->stang : aux->drept;
            if (aux != radacina)
            {
                if (aux == y->stang)y->stang = q;       //daca avem de sters fiul stang
                else y->drept = q;
            }
            else radacina = q;
            delete aux;
        }
        if (!radacina)return radacina;
        if (radacina->stang->getInaltime() > radacina->drept->getInaltime() && radacina->stang!=NULL)radacina->inaltime = 1 + radacina->stang->getInaltime();//noua inaltime a radacinii va fi in mod evident inaltimea cea mai mare a unui subarbore+1(nod curent)
            else if(radacina->drept!=NULL) radacina->inaltime = 1 + radacina->drept->inaltime;
            int dif_inaltime = checkHeight(radacina);
            if (dif_inaltime > 1 && checkHeight(radacina->stang) > 0)
                radacina = rotatieDreapta(radacina);
            if (dif_inaltime > 1 && checkHeight(radacina->stang) < 0)
            {
                radacina->stang = rotatieStanga(radacina->stang);
                return rotatieDreapta(radacina);
            }
            if (dif_inaltime <-1 && checkHeight(radacina->drept) < 0)
                radacina = rotatieStanga(radacina);
            if (dif_inaltime < -1 && checkHeight(radacina->drept) > 0)
            {
                radacina->drept = rotatieDreapta(radacina->drept);
                return rotatieStanga(radacina);
            }
            return radacina;
        
         
    }
    int checkHeight(arbore* radacina)  //metoda care returneaza diferenta dintre subarborele stang si subarborele drept
    {
        if (radacina != NULL)
        {
            //if (radacina->stang == NULL)return radacina->drept->inaltime;//daca unul dintre fii este null,returnam inaltimea unuia
            //if (radacina->drept == NULL)return radacina->stang->inaltime;
            //if (radacina->drept->inaltime > radacina->stang->inaltime)return radacina->drept->inaltime - radacina->stang->inaltime;
            if(radacina->stang!=NULL && radacina->drept!=NULL)
            return radacina->stang->inaltime - radacina->drept->inaltime;
            if(radacina->stang == NULL && radacina->drept != NULL)
                return radacina->drept->inaltime;
            if (radacina->stang != NULL && radacina->drept == NULL)
                return radacina->stang->inaltime;
        }
        return 0;
    }
    //pentru efectuarea rotatiilor trebuie sa avem in vedere conditia de 
    //arbore binar de cautare i.e nod stang < radacina < nod drept
    arbore* rotatieStanga(arbore* radacina)
    {
        arbore* p = radacina->drept;
        arbore* q = p->stang;

        p->stang=radacina ;
        radacina->drept = q;
        if (radacina->stang->inaltime > radacina->drept->inaltime)
        {
            radacina->inaltime = 1 + radacina->stang->inaltime;
        }
        else {
            radacina->inaltime = 1 + radacina->drept->inaltime;
        }
        if (p->stang->inaltime > p->drept->inaltime)    //modific inaltimea,inaltimea radacinii va fi in mod evident
                                                        //1+ inaltimea celui mai mare subarbore
        {
            p->inaltime = 1 + p->stang->inaltime;
        }
        else {
            p->inaltime = 1 + p->drept->inaltime;
        }
      return p;
    }
    arbore* rotatieDreapta(arbore* radacina)
    {
            arbore* p = radacina->stang;   //salvez nodul stang al radacinii
            arbore* q = p->drept;   //salvez nodul drept al fiului stang

            p->drept = radacina;    //interschimb,fiul drept al nodului stang ia valoarea radacinii
            radacina->stang = q;    //fiul stang al radacinii devine ceea ce era fiul drept al nodului stang din radacina
            if (p->stang->inaltime > p->drept->inaltime)
            {
                p->inaltime = 1 + p->stang->inaltime;
            }
            else {
                p->inaltime = 1 + p->drept->inaltime;
            }
            if (radacina->stang->inaltime > radacina->drept->inaltime)          //modific inaltimile noilor subarbori si inaltimea radacinii
            {
                radacina->inaltime = 1 + radacina->stang->inaltime;
            }
            else {
                radacina->inaltime = 1 + radacina->drept->inaltime;
            }
            return p; //deoarece p devine noua radacina
   

    }
    ~arbore()=default;
    
};

template <typename T,class key=comparator<T> >
class Set
{
    arbore<T>* radacina;
    int lungime;
public:
    Set() {                                     //constructorul fara parametri care imi creeaza un set gol,i.e un arbore gol=>radacina va fi NULL
        radacina=NULL; 
        lungime = 0;
    }
    Set(T x) {                                 //constructorul fara parametri care imi creeaza 'radacina' arborelui
        radacina = radacina->nod(x);
        lungime++;
    };                                  //imi creez un arbore de un singur nod,deoarece vom crea setul prin inserari;
   Set(const Set<T,key>& s)
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
    void erase(T y) {
        radacina->stergere(radacina, y);
        lungime--;
    }
 
    bool find(T x) {
        return radacina->cautare(radacina,x);
    }
    void insert(T valoare)
    {
        if (radacina->cautare(radacina, valoare) == 0)   //ne asiguram ca nu avem duplicate pentru a putea insera o noua valoare
        {
            radacina->inserare(radacina, valoare);
            this->lungime=lungime+1;                    //la fiecare inserare crestem marimea setului
        }
        else return;
    }
    arbore<T>* getRadacina()
    {
        return radacina;
    }
    int size()
    {
        return lungime;
    }

    Set& operator=(const Set& s)
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
                        radacina->inserare(radacina,root->getStang()->getInfo());
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
    friend ostream& operator<<(ostream& out,  Set<T,key>& s)
    {
        if (s.radacina == NULL)                                 //in cazul in care setul este vid se arunca o eroare
        {
            throw std::domain_error("Empty set");
        }
        else {
            s.radacina->SRD(s.radacina);                        //in caz contrar apelam parcurgerea stang-radacina-drept din arbore pentru a afisa 
                                                                //elementele in ordine crescatoare;
            }
        return out;
    }
    ~Set() {
         while (this->radacina->getStang() != NULL ||this->radacina->getDrept()!=NULL)  //atata timp cat am si fiu stang si fiu drept incepstergerea
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
	
};


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
    return(x%2==y%2);
}



#endif
