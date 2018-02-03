/**
* Fichero con formato de fechas de España
* Prácticas de la asignatura Programación Orientada a Objetos (curso 2016-2017)
* @author Manuel Jesús Corbacho Sánchez
* @version 1.0.27.03.2017
*/
#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>
#include <ctime>   //std:: tm*/time_t/time()/localtime()/
#include <cstring> //strcpy
#include <cstdio>  //sscanf
#include <clocale>


class Fecha {
    public:
        /* Constantes Públicas . */
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;
        /* Constructores. */
        explicit Fecha(int = 0 , int = 0,int = 0);
        Fecha(const char* cad) ;
        /* Observadores */
        inline int dia() const noexcept{ return dia_; }
        inline int mes() const noexcept{ return mes_; }
        inline int anno()const noexcept{ return anno_;}
        /* Operador de conversión . */
        const char* cadena() const;
        /* Operadores aritméticos . */
        Fecha& operator +=(int i);      //Suma con decremento
        Fecha& operator -=(int i);      //Resta con decremento
        Fecha  operator + (int i) const;//Añadir días
        Fecha  operator - (int i) const;//Quitar días
        Fecha& operator ++();           //Pre -incremento
        Fecha  operator ++(int i);      //Post-incremento
        Fecha& operator --();           //Pre -decremento
        Fecha  operator --(int i);      //Post-decremento
        
        /* Excepciones */
        class Invalida {
            public:
                Invalida (const char* e);
                const char* por_que() const;
            private:
                const char* por_que_;
        };
    private:
        int dia_;
        int mes_;
        int anno_;
        int valida() const;//Private porque sólo se usa dentro de la clase
};

/* Operadores relacionales */
bool operator ==(const Fecha& f1 ,const Fecha& f2);
bool operator !=(const Fecha& f1 ,const Fecha& f2);
bool operator < (const Fecha& f1 ,const Fecha& f2);
bool operator <=(const Fecha& f1 ,const Fecha& f2);
bool operator > (const Fecha& f1 ,const Fecha& f2);
bool operator >=(const Fecha& f1 ,const Fecha& f2);
/* Resta de fechas */
long operator - (const Fecha& f1 ,const Fecha& f2);

std::ostream& operator<<(std::ostream& salida,const Fecha& f);
std::istream& operator>>(std::istream& entrada,Fecha& f);

#endif
