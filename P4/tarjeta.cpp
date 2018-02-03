#include "tarjeta.hpp"
#include <iomanip>
#include <algorithm>

bool luhn(const Cadena&);

namespace{ //El namespace sin nombre indica que solo se puede usar en este fichero
/**
 *struct EsBlanco{
 *    bool operator()(char c) const { return isspace(c); }
 *};
 */

/**
 *Version previa a C++11 ->
 *struct EsDigito: std::unary_function<char, bool> {//El : es que hereda de unary_function y es necesario para que funcione el not1
 *    bool operator()(char c) const { return std::isdigit(c); }
 *};
 */

struct EsDigito{ //el function se lleva a la función
    bool operator()(char c) const { return std::isdigit(c); }
};

}
/*Funciones de Numero*/
Numero::Numero(const Cadena& num): numero_(num){ //Cadena no tiene constructor de copia trivial,así que se pasa por ref.const
	Cadena::iterator fin = std::remove_if( numero_.begin(), numero_.end(), [](char c){ return std::isspace(c); } );
	if( fin != numero_.end() ) {
		*fin='\0';
		//numero_[ std::distance(numero_.begin(),fin) ]='\0';
		Cadena sd( numero_.c_str() );
		numero_= sd;
	}

	if ( std::find_if(numero_.begin(), numero_.end(), std::not1(std::function<bool(char)>(EsDigito())) )!= numero_.end() ){ //El 1 es por el predicado unario
		throw Incorrecto(DIGITOS);
	}

	if( numero_.length()<13 or 19<numero_.length() ){ throw Incorrecto(LONGITUD); }
	if( not luhn(numero_) ) throw Incorrecto(NO_VALIDO);
}

/*Funciones de Tarjeta*/
Tarjeta::Tarjeta(const Tipo& tipo,const Numero& numero,Usuario& titular,const Fecha& caducidad):
	tipo_(tipo),numero_(numero),titular_(&titular),caducidad_(caducidad)
{
	if(caducidad < Fecha() ){ throw Tarjeta::Caducada(caducidad_); }
	titular_facial_ = titular_->nombre()+" "+titular_->apellidos();
	titular.es_titular_de(*this);
}


Tarjeta::~Tarjeta(){
	if(titular_){
		Usuario* aux=const_cast<Usuario *> (titular_);
		//const_cast<nuevotipo> (variable) permite transformar entre const y no const
		aux->no_es_titular_de(*this);
	}
}

void Tarjeta::anular_titular(){
	titular_=nullptr;//valor nulo de un puntero
}

std::ostream& operator<<(std::ostream& salida,const Tarjeta& t){
	salida << t.tipo() <<"\n";
	salida << t.numero() <<"\n";
	salida << t.titular_facial() <<"\n";
	salida << "Caduca: " << std::setfill('0') << std::setw(2) << t.caducidad().mes() << "/" << t.caducidad().anno()%100  <<"\n";
	return salida;
}

std::ostream& operator<<(std::ostream& salida,const Tarjeta::Tipo& tipo){
	switch (tipo){
		case 0:	salida << "VISA"; 				break; 	//case Tarjeta::VISA:
		case 1:	salida << "Mastercard"; 		break; 	//case Tarjeta::Mastercard:
		case 2:	salida << "Maestro"; 			break; 	//case Tarjeta::Maestro:
		case 3:	salida << "JCB"; 				break; 	//case Tarjeta::JCB:
		case 4:	salida << "AmericanExpresss";	break;	//case Tarjeta::AmericanExpress:
	}
	return salida;
}
/*****************************/
