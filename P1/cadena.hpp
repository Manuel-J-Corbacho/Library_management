/**
* Emulación de algunas funciones de la biblioteca cstring de C++
* Prácticas de la asignatura Programación Orientada a Objetos (curso 2016-2017)
* @author Manuel Jesús Corbacho Sánchez
* @version 1.0.27.03.2017
*/
#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstring>
#include <stdexcept>
#include <iterator>
#include <functional>

class Cadena{
    public:
        static const size_t npos = static_cast<size_t>(-1);
        explicit Cadena(size_t tam=0,char c=' ');//
        Cadena(const Cadena& cad);//
        Cadena(const char* cad);//
        Cadena(const char* cad , size_t tam);//
        Cadena(const Cadena& cad , size_t ini , size_t lon=npos );
        ~Cadena();//
        size_t length() const noexcept;//
        Cadena& operator =(const char* cad);
        Cadena& operator =(const Cadena& cad);
        Cadena& operator +=(const Cadena& cad);
        char operator[](size_t pos) const  noexcept;//
        char& operator[](size_t pos)  noexcept;//
        Cadena substr(size_t ini,int lon) const;
        char at(size_t i) const;//
        char& at(size_t i);//
        /*Práctica 1*/
        Cadena(Cadena&& cad);//
        Cadena& operator =(Cadena&& cad);
        const char* c_str() const;//
        /*iteradores*/
        typedef char* iterator;
        typedef const char * const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        inline iterator begin()noexcept{ 
            return s_; 
        }

        inline iterator end()  noexcept{
            return s_+tam_; 
        }

        inline const_iterator begin()  const noexcept{
            return s_;
        }

        inline const_iterator end()    const noexcept{
            return s_+tam_;
        }

        inline const_iterator cbegin() const noexcept{
            return s_;
        }

        inline const_iterator cend()   const noexcept{
            return s_+tam_;
        }

        inline reverse_iterator rbegin() noexcept{
            return reverse_iterator(end());
        }

        inline reverse_iterator rend()   noexcept{
            return reverse_iterator(begin());
        }

        inline const_reverse_iterator rbegin() const noexcept{
            return const_reverse_iterator(end());
        }
        
        inline const_reverse_iterator rend()   const noexcept{
            return const_reverse_iterator(begin());
        }

        inline const_reverse_iterator crbegin()const noexcept{
            return const_reverse_iterator(end());
        }

        inline const_reverse_iterator crend()  const noexcept{
            return const_reverse_iterator(begin());
        }
    
    private:
        char* s_;
        size_t tam_;
};

Cadena operator +(const Cadena& cad1,const Cadena& cad2);
bool operator == (const Cadena& cad1,const Cadena& cad2);//
bool operator != (const Cadena& cad1,const Cadena& cad2);//
bool operator <  (const Cadena& cad1,const Cadena& cad2);//
bool operator <= (const Cadena& cad1,const Cadena& cad2);//
bool operator >  (const Cadena& cad1,const Cadena& cad2);//
bool operator >= (const Cadena& cad1,const Cadena& cad2);//
/*Práctica1*/
std::ostream& operator<<(std::ostream& salida,const Cadena& cad);
std::istream& operator>>(std::istream& entrada,Cadena& cad);

// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std
    template <> // Es una especialización de una plantilla para Cadena
    struct hash<Cadena> { // Es una clase con solo un operador publico
        size_t operator() (const Cadena& cad) const{ // el operador función
            hash<string> hs; // creamos un objeto hash de string
            const char * p = cad.c_str(); // obtenemos la cadena de la Cadena
            string s(p); // creamos un string desde una cadena
            size_t res = hs(s); // el hash del string. Como hs.operator()(s);
            return res; // devolvemos el hash del string
        }
    };
}

#endif
