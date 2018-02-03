/**
* Fichero con formato de fechas de ESPAÑA
* Prácticas de la asignatura Programación Orientada a Objetos (curso 2016-2017)
* @author Manuel Jesús Corbacho Sánchez
* @version 1.0.27.03.2017
*/

#include "fecha.hpp"

/////////////////////////Excepciones/////////
Fecha::Invalida::Invalida (const char* e): por_que_(e) {}
const char* Fecha::Invalida::por_que() const{ return por_que_; }

/////////////////Constructores///////////////
Fecha::Fecha(int d , int m,int a): dia_{d} , mes_{m} , anno_{a} {
    if(!d || !m || !a){
        std::time_t fecha_calendario = std::time(nullptr);
        std::tm* estructura_fecha = std::localtime(&fecha_calendario);
        if(!dia_)  dia_ = estructura_fecha->tm_mday;
        if(!mes_)  mes_ = 1+estructura_fecha->tm_mon;
        if(!anno_) anno_= 1900+estructura_fecha->tm_year;
    }
    if( d || m || a ){
        try{
            valida();
        }catch(Invalida e){
            throw;
        }
    }
}

Fecha::Fecha(const char* cad){
    int d,m,a;
    try{
        if( 3 != sscanf(cad , "%d / %d /%d" , &d,&m,&a) ){
            throw Fecha::Invalida("Fecha desde cadena inválida ...");
        }
        *this = Fecha::Fecha(d,m,a);//
    }catch(Fecha::Invalida e){
        throw;
    }
}
////////////////////////////////////////////////////////////////

/////////////Comprobacion de fecha correcta/////////////////////
int Fecha::valida() const{
    if(anno_<AnnoMinimo||AnnoMaximo<anno_) throw Invalida("Error en el anno");
    if( mes_ < 1 || 12 < mes_ ) throw Invalida("Error en el mes");
    if( dia_ < 1 || 31 < dia_ ) throw Invalida("Error en el día");
    int ndias[]{31,29,31,30,31,30,31,31,30,31,30,31};
    if( ndias[mes_-1]  < dia_ ) throw Invalida("Error en el día");
    if( mes_==2){
        if( anno_%4==0 && ( anno_%400==0 || anno_%100!=0 ) ){
            if(dia_>29) throw Invalida("Error en el día");
        }else{
            if(dia_>28) throw Invalida("Error en el día");
        }
    }
    return 1;
}
////////////////////////////////////////////////////////////////

/////////////Operadores de conversión///////////////////////////
const char* Fecha::cadena() const{  //Conversión a Cadena de bajo nivel
    //std::setlocale(LC_TIME,"spanish_Spain");
    std::setlocale(LC_TIME,"es_ES.UTF-8");
    struct tm estructura_fecha={ 0,0,0,dia() ,mes()-1 ,anno()-1900 ,0,0,0};
    std::mktime(&estructura_fecha);
    static char cad[36];
    std::strftime(cad,36,"%A %d de %B de %Y",&estructura_fecha);//
    return cad;
}
/////////////////////////////////////////////////////////

/////////////Operadores aritméticos//////////////////////
Fecha& Fecha::operator +=(int i){      //Suma con asignacion
    struct std::tm t={0, 0, 0,  dia()+i  , mes() -1 , anno() -1900 , 0, 0, 0 };
    mktime(&t);
    dia_ = t.tm_mday;
    mes_ = 1+ t.tm_mon;
    anno_= 1900 +t.tm_year;
    try{
        valida();
    } catch( Fecha::Invalida e){
        throw;
    }
    return *this;
}

Fecha& Fecha::operator -=(int i){      //Resta con asignacion
    *this += (-i);
    return *this;
}

Fecha& Fecha::operator ++(){           //Pre -incremento
    return *this+= 1;
}

Fecha Fecha::operator ++(int i){       //Post-incremento
    Fecha f(*this);
    *this+= 1;
    return f;
}

Fecha& Fecha::operator --(){           //Pre -decremento
    return *this+= -1;
}

Fecha Fecha::operator --(int i){       //Post-decremento
    Fecha f(*this);
    *this+= -1;
    return f;
}

Fecha Fecha::operator +(int i) const{  //Añadir días
    Fecha f(*this);
    f+=i;
    return f;
}

Fecha Fecha::operator -(int i) const{  //Quitar días
    Fecha f(*this);
    f+= (-i);
    return f;

}
/////////////////////////////////////////////////////////

/////////////////Operadores de comparación/////////////////
bool operator ==(const Fecha& f1 ,const Fecha& f2){
    return ( f1.anno()==f2.anno() && f1.mes()==f2.mes() && f1.dia()==f2.dia() );
}

bool operator < (const Fecha& f1 ,const Fecha& f2){
    if( f1.anno()>f2.anno() ){ return false; }
    if( f1.anno()<f2.anno() ){ return true;  }
    if( f1.mes() > f2.mes() ){ return false; }
    if( f1.mes() < f2.mes() ){ return true;  }
    if( f1.dia() > f2.dia() ){ return false; }
    if( f1.dia() < f2.dia() ){ return true;  }
    return false;
}

bool operator !=(const Fecha& f1 ,const Fecha& f2){ return !(f1 == f2); }
bool operator <=(const Fecha& f1 ,const Fecha& f2){ return !(f2  < f1); }
bool operator > (const Fecha& f1 ,const Fecha& f2){ return   f2  < f1 ; }
bool operator >=(const Fecha& f1 ,const Fecha& f2){ return !(f1  < f2); }
///////////////////////////////////////////////////

long operator - (const Fecha& f1 ,const Fecha& f2){
    struct std::tm t1={ 0,0,0,f1.dia(), f1.mes()-1, f1.anno()-1900, 0, 0, 0};
    struct std::tm t2={ 0,0,0,f2.dia(), f2.mes()-1, f2.anno()-1900, 0, 0, 0};
    return static_cast<long int> (difftime(mktime(&t1),mktime(&t2))/86400);//Segundos de 1 dia = 60s*60m*24h=86400s
}

//////////////////////////////
std::ostream& operator<<(std::ostream& salida,const Fecha& f){
    salida << f.cadena();
    return salida;
}

std::istream& operator>>(std::istream& entrada,Fecha& f){
    char nuevaFecha[11]="";
    entrada.width(11);
    try{
        entrada >> nuevaFecha;
        f=nuevaFecha;
    }catch(Fecha::Invalida){
        entrada.setstate(std::ios::failbit);
        throw;
    }
    return entrada;
}
