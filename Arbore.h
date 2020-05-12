#pragma once
#ifndef ARBORE_H
#define ARBORE_H
#include<iostream>
using namespace std;


template<typename T>
class arbore
{
    T info;
    int inaltime;
    arbore* stang;
    arbore* drept;

public:
	~arbore() = default;
    arbore();
    arbore* getStang();
    arbore* getDrept();
    T getInfo();
    void setInfo(T val);
    void setStang(arbore* val);
    void setDrept(arbore* val);
    arbore<T>* nod(T x);
    int getInaltime();
    arbore<T>* inserare(arbore*& radacina, T x);
    bool cautare(arbore* radacina, T x);
    void SRD(arbore* radacina);
    arbore<T>* getMinim(arbore* radacina);
    arbore<T>* getMaxim(arbore* radacina);
    void setParent(arbore*& aux, arbore*& parinte, T x);
    arbore<T>* stergere(arbore*& radacina, T x);
    int checkHeight(arbore* radacina);
    arbore<T>* rotatieStanga(arbore* radacina);
    arbore<T>* rotatieDreapta(arbore* radacina);
};


template<typename T>
arbore<T>::arbore() :stang(NULL), drept(NULL), info(NULL), inaltime(0) {           //constructorul fara parametri pentru arbore

}

template<typename T>
arbore<T>* arbore<T>::getStang() {
    if (this == NULL)return NULL;
    return stang;
}           //getter pentru nodul stang

template<typename T>
arbore<T>* arbore<T>::getDrept() {            //getter pentru nodul drept
    if (this == NULL)return NULL;
    return drept;
}

template<typename T>
T arbore<T>::getInfo() {                   //getter pentru valoarea din nod
    return info;
}

template<typename T>
void arbore<T>::setInfo(T val) {       //setter pentru valoarea din nod
    info = val;
}

template<typename T>
void arbore<T>::setStang(arbore* val) {            //setter pentru nod stang
    this->stang = val;
}

template<typename T>
void arbore<T>::setDrept(arbore* val) {            //setter pentru nod drept
    this->drept = val;
}

template<typename T>
arbore<T>* arbore<T>::nod(T x)                            //metoda prin care creez un nod nou din arbore; pentru a nu mai folosi o alta clasa="nod"
                                            //am consiederat un nod drept fiind un arbore de un singur element
{
    arbore* p = new arbore;
    p->info = x;
    p->stang = NULL;
    p->drept = NULL;
    p->inaltime = 1;
    return p;
}

template<typename T>
int arbore<T>::getInaltime() {                     //getter pentru inaltimea unei radacini,daca aceasta este null inaltime=0;deci intoarce 0
    if (this != NULL)return inaltime;
    return 0;
}

template<typename T>
arbore<T>* arbore<T>::inserare(arbore*& radacina, T x)
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
    if (parinte->stang != NULL && parinte->drept != NULL)
    {
        if (parinte->stang->inaltime > parinte->drept->inaltime)
            parinte->inaltime = 1 + parinte->stang->inaltime;
        else parinte->inaltime = 1 + parinte->drept->inaltime;
    }
    if (parinte->stang == NULL && parinte->drept != NULL)
        parinte->inaltime = 1 + parinte->drept->inaltime;
    if (parinte->drept == NULL && parinte->stang != NULL)
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

template<typename T>
bool arbore<T>::cautare(arbore* radacina, T x)
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

template<typename T>
void arbore<T>::SRD(arbore* radacina)
{
    if (radacina != NULL)
    {
        SRD(radacina->stang);
        cout << radacina->info << " ";
        SRD(radacina->drept);
    }

}                   //parcurgere SRD care imi afiseaza elementele arborelui in ordine crescatoare

template<typename T>
arbore<T>* arbore<T>::getMinim(arbore* radacina)
{
    arbore* p = radacina;
    while (p && p->stang != NULL)
        p = p->stang;
    return p;
}

template<typename T>
arbore<T>* arbore<T>::getMaxim(arbore* radacina)
{
    arbore* p = radacina;
    while (p && p->getDrept() != NULL)
        p = p->getDrept();
    return p;
}

template<typename T>
void arbore<T>::setParent(arbore*& aux, arbore*& parinte, T x)  //metoda care imi cauta parintele valorii pe care doresc sa o sterg
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

template<typename T>
arbore<T>* arbore<T>::stergere(arbore*& radacina, T x)
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
    if (radacina->stang->getInaltime() > radacina->drept->getInaltime() && radacina->stang != NULL)radacina->inaltime = 1 + radacina->stang->getInaltime();//noua inaltime a radacinii va fi in mod evident inaltimea cea mai mare a unui subarbore+1(nod curent)
    else if (radacina->drept != NULL) radacina->inaltime = 1 + radacina->drept->inaltime;
    int dif_inaltime = checkHeight(radacina);
    if (dif_inaltime > 1 && checkHeight(radacina->stang) > 0)
        radacina = rotatieDreapta(radacina);
    if (dif_inaltime > 1 && checkHeight(radacina->stang) < 0)
    {
        radacina->stang = rotatieStanga(radacina->stang);
        return rotatieDreapta(radacina);
    }
    if (dif_inaltime < -1 && checkHeight(radacina->drept) < 0)
        radacina = rotatieStanga(radacina);
    if (dif_inaltime < -1 && checkHeight(radacina->drept) > 0)
    {
        radacina->drept = rotatieDreapta(radacina->drept);
        return rotatieStanga(radacina);
    }
    return radacina;


}

template<typename T>
int arbore<T>::checkHeight(arbore* radacina)  //metoda care returneaza diferenta dintre subarborele stang si subarborele drept
{
    if (radacina != NULL)
    {
        //if (radacina->stang == NULL)return radacina->drept->inaltime;//daca unul dintre fii este null,returnam inaltimea unuia
        //if (radacina->drept == NULL)return radacina->stang->inaltime;
        //if (radacina->drept->inaltime > radacina->stang->inaltime)return radacina->drept->inaltime - radacina->stang->inaltime;
        if (radacina->stang != NULL && radacina->drept != NULL)
            return radacina->stang->inaltime - radacina->drept->inaltime;
        if (radacina->stang == NULL && radacina->drept != NULL)
            return radacina->drept->inaltime;
        if (radacina->stang != NULL && radacina->drept == NULL)
            return radacina->stang->inaltime;
    }
    return 0;
}
//pentru efectuarea rotatiilor trebuie sa avem in vedere conditia de 
//arbore binar de cautare i.e nod stang < radacina < nod drept
template<typename T>
arbore<T>* arbore<T>::rotatieStanga(arbore* radacina)
{
    arbore* p = radacina->drept;
    arbore* q = p->stang;

    p->stang = radacina;
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

template<typename T>
arbore<T>* arbore<T>::rotatieDreapta(arbore* radacina)
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



#endif