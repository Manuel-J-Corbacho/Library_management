#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <cctype>
#include <functional>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Usuario;

class Numero{
	public:
		enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
		/*Constructor*/
		Numero(const Cadena& cad);
		/*Clase de excepcion*/
		class Incorrecto{
			public:
				Incorrecto(const Razon razon): razon_(razon) {}
				const Razon razon() const noexcept{ return razon_; }
			private:
				Razon razon_;
		};
		/*Conversor*/
		operator const char*() const noexcept{ return numero_.c_str(); }
	private:
		Cadena numero_;
};

inline bool operator <(const Numero& n1,const Numero& n2){
	return strcmp(n1,n2)<0;
}

class Tarjeta{
	public:
		enum Tipo{VISA,Mastercard,Maestro,JCB,AmericanExpress};
		/*Constructor*/
		Tarjeta(const Tipo& tipo,const Numero& numero,Usuario& titular,const Fecha& caducidad);
		/*Clase de excepción*/
		class Caducada{
			public:
				Caducada(const Fecha& cuando):cuando_(cuando){}
				const Fecha& cuando() const noexcept{ return cuando_; }
			private:
				const Fecha cuando_;
		};
		/*Evitar duplicidades*/
		Tarjeta(const Tarjeta& tarjeta) = delete;
		Tarjeta& operator = (const Tarjeta& tarjeta) = delete;


		/*Observadores*/
		Tipo tipo() const noexcept{ return tipo_; }
		Numero numero() const noexcept{ return numero_; }
		Fecha caducidad() const noexcept{ return caducidad_; }
		Cadena titular_facial() const noexcept{ return titular_facial_; }
		const Usuario* titular() const noexcept{ return titular_; }
		/*Modificador*/
		void anular_titular();
		/*Destructor*/
		~Tarjeta();
	private:
		Tipo tipo_;
		Numero numero_;
		const Usuario* titular_;
		Fecha caducidad_;
		Cadena titular_facial_;
};

inline bool operator <(const Tarjeta& t1,const Tarjeta& t2){
	return std::strcmp(t1.numero(),t2.numero())<0;
}

std::ostream& operator<<(std::ostream& salida,const Tarjeta& t);
std::ostream& operator<<(std::ostream& salida,const Tarjeta::Tipo& tipo);

#endif
