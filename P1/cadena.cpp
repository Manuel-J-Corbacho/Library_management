/**
* Emulación de algunas funciones de la biblioteca cstring de C++
* Prácticas de la asignatura Programación Orientada a Objetos (curso 2016-2017)
* @author Manuel Jesús Corbacho Sánchez
* @version 1.0.27.03.2017
*/

#include "cadena.hpp"

/////////////////Constructores y Destructor////////////
Cadena::Cadena(size_t tam,char c):s_(new char[tam+1]),tam_(tam){
    memset(s_,c,tam_);
    s_[tam_]='\0';
}
Cadena::Cadena(const Cadena& cad):s_(new char[cad.length()+1]),tam_(cad.length()){
    strcpy(s_,cad.c_str());
}

Cadena::Cadena(const char* cad):s_(new char[strlen(cad)+1]),tam_(strlen(cad)) {
    strcpy(s_,cad);
}

Cadena::Cadena(const char* cad , size_t tam):s_(new char[tam+1]),tam_(tam){
    if( tam_>strlen(cad) ){
        tam_=strlen(cad);
        delete[] s_;
        s_ = new char[tam_+1];
        strcpy(s_,cad);
    }else{
        memcpy(s_,cad,tam_);
        s_[tam_]='\0';
    }
}

Cadena::Cadena(const Cadena& cad , size_t ini , size_t lon ){
    if(ini >= cad.length() ){throw std::out_of_range("Posición inicial de ctor. inválida");}
    if(lon==npos || ini+lon> cad.length() ){
        tam_ = cad.length()-ini;
    }else{
        tam_=lon;
    }
    s_=new char[tam_+1];
    memcpy(s_, cad.c_str()+ini, tam_);
    s_[tam_]='\0';
}

Cadena::~Cadena(){ delete[] s_;}
//////////////////////////////////////

////////Observadores//////////
inline size_t Cadena::length() const noexcept{ return tam_; }
inline const char* Cadena::c_str() const{ return s_; }
//////////////////////////////

/////////////////Acceso a carácter//////////
char Cadena::operator[](size_t pos) const  noexcept{
    return s_[pos];
}

char& Cadena::operator[](size_t pos)  noexcept{
    return s_[pos];
}

char Cadena::at(size_t i) const{
    if(i >= tam_){ throw std::out_of_range("Posición no accesible .");}
    return s_[i];
}

char& Cadena::at(size_t i){
    if(i >= tam_){ throw std::out_of_range("Posición no accesible .");}
    return s_[i];
}
////////////////////////////////////////////

Cadena Cadena::substr(size_t ini,int lon)const{
    if(ini>=length() || ini+lon>=length() || lon < 0 ){
        throw std::out_of_range("Parámetros de substr no válidos .");
    }
    char* aux = new char[lon+1];
    memcpy(aux,s_+ini,lon);
    aux[lon]='\0';
    Cadena cad(aux);
    delete[] aux;
    return cad;
}


////////Asignación de Cadenas///////////
Cadena& Cadena::operator =(const Cadena& cad){
    if (this!=&cad){
        tam_ = cad.length();
        delete[] s_;
        s_=new char[tam_+1];
        strcpy(s_,cad.c_str());
    }
    return *this;
}

Cadena& Cadena::operator =(const char* cad){
    delete[] s_;
    s_=new char[strlen(cad)+1];
    strcpy(s_,cad);
    tam_=strlen(cad);
    return *this;
}

////////////////////////////////////////
////////Concatenar Cadenas///////////////
Cadena& Cadena::operator +=(const Cadena& cad){
    char* aux=new char[length()+cad.length()+1];
    strcpy(aux,s_);
    strcat(aux,cad.s_);
    delete[] s_;
    tam_+= cad.length();
    s_=new char[tam_+1];
    strcpy(s_,aux);
    delete[] aux;
    return *this;
}

Cadena operator +(const Cadena& cad,const Cadena& cad2){
    Cadena nueva(cad.c_str());
    nueva+=cad2;
    return nueva;
}

//////////////////////////////////////////

//////////Operadores de comparación/////////////////////
bool operator == (const Cadena& cad1,const Cadena& cad2){
    return strcmp(cad1.c_str(),cad2.c_str()) == 0;
}

bool operator != (const Cadena& cad1,const Cadena& cad2){
    return strcmp(cad1.c_str(),cad2.c_str()) != 0;
}

bool operator <  (const Cadena& cad1,const Cadena& cad2){
    return strcmp(cad1.c_str(),cad2.c_str()) <  0;
}

bool operator <= (const Cadena& cad1,const Cadena& cad2){
    return strcmp(cad1.c_str(),cad2.c_str()) <= 0;
}

bool operator >  (const Cadena& cad1,const Cadena& cad2){
    return strcmp(cad1.c_str(),cad2.c_str()) >  0;
}

bool operator >=(const Cadena& cad1,const Cadena& cad2) {
    return strcmp(cad1.c_str(),cad2.c_str()) >= 0;
}
/////////////////////////////////////////////////////////

/*Práctica 1*/

std::ostream& operator<<(std::ostream& salida,const Cadena& cad){
    salida << cad.c_str();
    return salida;
}
std::istream& operator>>(std::istream& entrada,Cadena& cad){
    char nuevacadena[32]="";
    entrada >> nuevacadena;
    cad = Cadena(nuevacadena);
    return entrada;
}
//////////////////Semantica de movimiento///////////////////
//https://msdn.microsoft.com/es-es/library/dd293665.aspx
Cadena::Cadena(Cadena&& cad):s_(cad.s_), tam_(cad.tam_){
    cad.tam_=0;
    cad.s_=nullptr;
}

/*Cadena::Cadena(Cadena&& cad):s_(nullptr), tam_(0){
    tam_=cad.tam_;
    s_=cad.s_;
    cad.tam_=0;
    cad.s_=nullptr;
}*/

Cadena& Cadena::operator =(Cadena&& cad){
    if(this != &cad){
        delete[] s_;
        s_=cad.s_;
        tam_=cad.tam_;
        cad.tam_=0;
        cad.s_=nullptr;
    }
    return *this;
}

