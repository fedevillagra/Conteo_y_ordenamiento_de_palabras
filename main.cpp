#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm> 

using namespace std;

//int ncomp=0;
//int nmov=0;

//ARBOL --------------------------------------------------
template <class T> class nodo { //Nodos solo usados por ArbolPos
public:
    T info;
    nodo<T>* der, * izq;
};


template <class T> class ArbolPos { //Esta clase esta destinada a contener en sus hojas punteros a las posiciones de una lista
private:
    nodo<T>* raizpos, * q;
    void ArbolBusq(T x, nodo<T>*& nuevo, string pos);
    void show(nodo<T>* aux, int n);
    T getNodo(nodo<T>* aux, string pos);
    void mh(nodo<T>* aux); 
    T menor(nodo<T>* aux);
    int TAM;

public:
    ArbolPos() { raizpos = NULL; };
    ~ArbolPos() {};
    void CreaArbolBus(T x, int pos) { ArbolBusq(x, raizpos, DecToBin(pos)); };
    void VerArbol() { show(raizpos, 0); }
    void MostrarHojas() { mh(raizpos); }
    T Menor() { return menor(raizpos); }
    T GetNodo(int pos){ return getNodo(raizpos, DecToBin(pos));}
    void setTAM(int t){ TAM = t;};
    string DecToBin(int dec);
};

template <class T> void ArbolPos<T>::ArbolBusq(T x, nodo<T>*& nuevo, string pos)
{
  if(nuevo == NULL)
  {
    nuevo = new nodo<T>;
    nuevo->der = nuevo->izq = NULL;
  }
    if (pos.empty()) {
        nuevo->info = x;
        return;
    }
    if (pos[0]=='1') ArbolBusq(x, nuevo->der,pos.substr(1));
    if (pos[0]=='0') ArbolBusq(x, nuevo->izq,pos.substr(1));
}

template <class T> void ArbolPos<T>::show(nodo<T>* aux, int n)
{
    int i;
    if (aux != NULL) {              //OjO este es un recorrido dri
        show(aux->der, n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->info << "\n";
        show(aux->izq, n + 1);
    }
}

template <class T> void ArbolPos<T>::mh(nodo<T>* aux)
{
    if (aux != NULL) {
        mh(aux->izq);
        if (aux->izq == NULL && aux->der == NULL)cout << "\n" << aux->info;
        mh(aux->der);
    }
}

template <class T> T ArbolPos<T>::getNodo(nodo<T>* aux, string pos)
{
    if (pos.empty()) {
        return aux->info;
    }
    if (pos[0]=='1') return getNodo(aux->der,pos.substr(1));
    if (pos[0]=='0') return getNodo(aux->izq,pos.substr(1));
    return aux->info; 
}

template <class T> string ArbolPos<T>::DecToBin(int dec)
{	
  string st  = "";
  while(dec>0 || st.length()<TAM)
  {
    char bit = (dec % 2) + '0';
        st = bit + st;               
        dec = dec / 2;
  }
  return st;
}
//FIN ARBOL-------------------------------------------------------------------------

class NodoDatos
{
  public:
    string dato;
    int cont;

    NodoDatos(){ cont = 1; }
};

class Nodo{
public: 

  NodoDatos* nododato;

  Nodo *next;
  Nodo *izq;
  Nodo *der;

  Nodo(){ next = NULL; izq = NULL; der = NULL; nododato = new NodoDatos; };
};

class Arbalesta{
  private:
  Nodo *raiz;
  Nodo *czo;

  ArbolPos< Nodo* > binbusq; //este sera el arbol a llenar con posiciones
  vector< Nodo* > vec; //en este vector guardo punteros a cada nodo en este arbol

  //metodos privados, para esconder la raiz
  void arbalesta(string nuevodato, Nodo*& aux);
  void show(Nodo* aux, int n); //profe
  void ird(Nodo* aux);
  void ordenar(Arbalesta* nueva, Nodo* aux);


  public:
  Arbalesta(){ raiz = NULL; czo = new Nodo; };
  void CreaArbalesta(string dato) { arbalesta(dato, raiz); };
  void VerArbol() { show(raiz, 0); } //codigo del profe. Imprime como arbol
  void impre(void); //profe. Imprime como lista
  void impre2(void); //usa el posicion para iterar como un array
  void IRD(void){ ird(raiz);}; //menor a mayor
  bool esvacia(void); //profe
  int size(); //profe
  Arbalesta* resto(void); //profe
  void setTAM();
  void LlenaArbPos();
  void HojasArbPos(){ binbusq.MostrarHojas(); }
  void Seleccion();
  void Selec();
  void MHDatos(); //hace casi lo mismo que impre2
  void Qsort(int prim, int ult, int &comp);
  int particion(int prim, int ult, int &comp);
  void Ordenar(Arbalesta* nueva){ ordenar(nueva, raiz); }
  string cabeza(void); //el tipo de return podria ser NodoDatos*, si piden cantidad en la comparacion
  bool ListIg2(Arbalesta* arb1, Arbalesta* arb2);
  bool ListasIguales(Arbalesta* arb1, Arbalesta* arb2);

  //vector< Nodo* > vec; //en este vector guardo punteros a cada nodo en este arbol

};

void Arbalesta::arbalesta(string nuevodato, Nodo*& aux)
{

  if(aux == NULL)
  {  	
    aux = new Nodo;
    aux->nododato->dato = nuevodato; //logica de arbol

    aux->next = czo; //logica de lista
    czo = aux;
    vec.push_back(aux); //cargo el puntero en el vector de posiciones
    return;
  }
  string auxdato = aux->nododato->dato;
  if(auxdato == nuevodato) aux->nododato->cont++;
  if(nuevodato<auxdato) arbalesta(nuevodato, aux->izq);
  if(nuevodato>auxdato) arbalesta(nuevodato, aux->der);
}

void Arbalesta::show(Nodo* aux, int n)
{
    int i;
    if (aux != NULL) {                      //OjO este es un recorrido dri
        show(aux->der, n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->nododato->dato << "\n";
        show(aux->izq, n + 1);
    }
}

void Arbalesta::impre(void)
{
    Nodo* aux;
    aux = czo;
    while (aux->next != NULL) { // LIFO
        cout << aux->nododato->dato<< ": " << aux->nododato->cont << endl;
        aux = aux->next;
    }
}

void Arbalesta::impre2(void)
{
  for(int i=0; i<size(); i++) // FIFO
  {
    cout << binbusq.GetNodo(i)->nododato->dato << ": " << binbusq.GetNodo(i)->nododato->cont << endl;
  }
}

void Arbalesta::ird(Nodo* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout << endl << aux->nododato->dato << " (" << aux->nododato->cont << ")";;
        ird(aux->der);
    }
}

bool Arbalesta::esvacia(void)
{
    return (czo->next == NULL);
}

Arbalesta* Arbalesta::resto(void)
{
    Arbalesta* l = new Arbalesta();
    l->czo = this->czo->next;
    return (l);
}

int Arbalesta::size()
{
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
}

void Arbalesta::LlenaArbPos()
{
  setTAM();

  Nodo* ith = new Nodo;
  for(int i=0; i<size(); i++)
  {
    ith = vec.at(i);
    binbusq.CreaArbolBus(ith, i);
  }
}

void Arbalesta::setTAM()
{
  int coc = vec.size(); //size() seria mejor, no depende de la existencia del vec
  int pow = 0;
  while(coc>0)
  {
    coc = coc/2;
    pow++;
  }
  binbusq.setTAM(pow);
}

void Arbalesta::MHDatos()
{
  for(int i=0; i<size(); i++)
  {
    cout << binbusq.GetNodo(i)->nododato->cont << endl;
    cout << binbusq.GetNodo(i)->nododato->dato << endl;
  }
}

void Arbalesta::Selec()
{
  //ncomp = 0;
  //nmov = 0;
  int comp = 0;
  int i, j;
  int indmenor;
  string menpos; //no lo necesito como int, creo
  NodoDatos* aux;
  for(i=0; i<size(); i++)
  {
    //Tomo como menor el elemento i
    indmenor = i;
    for(j=i+1; j<size(); j++)
    {
      //ncomp ++;
      comp++;
      if(binbusq.GetNodo(indmenor)->nododato->cont < binbusq.GetNodo(j)->nododato->cont) //si el elemento j-esimo es menor que menor, j-esimo es ahora el menor
      {
        indmenor = j;
      }

    }
    //nmov ++;
    //pongo el menor en la posicion i-esima
    aux = binbusq.GetNodo(i)->nododato;
    binbusq.GetNodo(i)->nododato = binbusq.GetNodo(indmenor)->nododato;
    binbusq.GetNodo(indmenor)->nododato = aux;
  }
  cout  << "El numero de comparaciones para seleccion fue: " << comp << endl;
}


void Arbalesta::Qsort(int prim, int ult, int &comp)
{
  int pi;
  if(prim<ult)
  {
    pi = particion(prim, ult, comp);
    Qsort(prim, pi-1,comp);
    Qsort(pi+1,ult,comp);
  }
}

int Arbalesta::particion(int prim, int ult, int &comp)
{
  NodoDatos* aux;
  int ipp;
  string pivote = binbusq.GetNodo(ult)->nododato->dato;

  int i = prim-1;

  for(int j=prim; j<ult; j++)
  {
    //ncomp ++;
    comp++;
    if(binbusq.GetNodo(j)->nododato->dato <= pivote)
    {
      //nmov ++;
      i++;
      aux = binbusq.GetNodo(i)->nododato;
      binbusq.GetNodo(i)->nododato = binbusq.GetNodo(j)->nododato;
      binbusq.GetNodo(j)->nododato = aux;
    }
  }
  //nmov ++;
  ipp = i+1;
  aux = binbusq.GetNodo(ipp)->nododato;
  binbusq.GetNodo(ipp)->nododato = binbusq.GetNodo(ult)->nododato;
  binbusq.GetNodo(ult)->nododato = aux;
  return i+1;
}

void Arbalesta::ordenar(Arbalesta* nueva, Nodo* aux)
{
  int i = 0;
  if(aux!=NULL)
  {
    ordenar(nueva, aux->izq);
    for(i=0;i<aux->nododato->cont;i++)
    {
      nueva->CreaArbalesta(aux->nododato->dato); //esto para mantener la cantidad de repeticiones
  }
    ordenar(nueva, aux->der);
  }
}

string Arbalesta::cabeza()
{
  return czo->nododato->dato;
}

bool ListIg2(Arbalesta* arb1, Arbalesta* arb2)
{
  if(arb1->esvacia()) return true;
  if(arb1->cabeza() != arb2->cabeza()) return false;
  return ListIg2(arb1->resto(), arb2->resto());

}

bool ListasIguales(Arbalesta* arb1, Arbalesta* arb2) //En realidad son Arbalestas, pero solo chequeamos la lista
{
  if(arb1->size() != arb2->size()){
    return false;
  }
  if(arb1->cabeza() != arb2->cabeza())
  {
    return false;
  }
  return ListIg2(arb1->resto(),arb2->resto());
}


int main() {

  Arbalesta* arb = new Arbalesta();
  int compQS = 0;

  ifstream archivo("test.txt");
  string palabra; 

  if(!archivo)
  {
    cout << "F en el chat" << endl;
    return 1;
  }
  while (archivo >> palabra) {
    transform(palabra.begin(), palabra.end(), palabra.begin(),::toupper);
    arb->CreaArbalesta(palabra);
    }

  archivo.close();

  cout << "ARBOL BINARIO" << endl << endl;
  arb->VerArbol();

  Arbalesta *arbord = new Arbalesta();

  arb->Ordenar(arbord);
  arbord->LlenaArbPos();

  cout << endl;
  cout << "Lista del arbol" << endl;
  cout << endl;

  arb->impre();
  cout << endl;

  cout << "Lista en orden alfabetico con frecuencia (IRD) " << endl;

  arb->IRD();
  arb->LlenaArbPos();

  cout << endl << endl << endl << "SELECCION" << endl;
  arb->Selec();
  cout << endl;
  cout << "Lista en orden de frecuencia:" << endl << endl;
  arb->impre2();
  //cout << endl << "Cantidad de movimientos: " << nmov << endl << "cantidad de comparaciones: " << ncomp << endl;

  cout << endl << endl;
  cout << "QUICKSORT" << endl;
  //ncomp = 0;
  //nmov =0;
  arb->Qsort(0, arb->size()-1,compQS);
  cout << "El numero de comparaciones para QuickSort fue: " << compQS << endl << endl;
  cout << "Lista en orden alfabética:" << endl << endl;
  arb->impre2();
  //cout << endl << "Cantidad de movimientos: " << nmov << endl << "Cantidad de comparaciones: " << ncomp << endl;

  //cout << endl << "Esto es arbord : "<< endl;
  //arbord->impre2();
  cout << endl;
  cout << endl << "Llamamos a listas iguales y dio " << ListasIguales(arb, arbord) << endl;
}
