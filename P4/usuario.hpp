#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include "articulo.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>

class Numero;
class Tarjeta;

class Clave{
	public:
		Clave(const char* texto_claro);
		const Cadena& clave()const noexcept{ return clave_; }
		bool verifica(const char* cad)const;
		enum Razon{CORTA,ERROR_CRYPT};
		class Incorrecta{
			public:
				Incorrecta(Razon razon):razon_(razon){}
				Razon razon() const noexcept { return razon_; }
			private:
				const Razon razon_;
		};
	private:
		Cadena clave_;
};

class Usuario{
	public:
		typedef std::map<Numero, Tarjeta*> Tarjetas;
		typedef std::unordered_map<Articulo*, unsigned int> Articulos;
		/*Constructores*/
		Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apellidos,const Cadena& direccion,const Clave& password);
		/*No podemos duplicar los identificadores*/
		class Id_duplicado{
			public:
				Id_duplicado(const Cadena id): idd_(id) {}
				const Cadena idd()const noexcept{ return idd_; }
			private:
				const Cadena idd_;
		};
    	//No podemos copiar ni asignar usuarios, eliminamos los métodos por defecto
    	Usuario(const Usuario& usuario) = delete;
		Usuario& operator = (const Usuario& usuario) = delete;
		/*Métodos observadores */
		Cadena id() const noexcept{	return id_; }
		Cadena nombre() const noexcept{ return nombre_; }
		Cadena apellidos() const noexcept{ return apellidos_; }
		Cadena direccion() const noexcept{ return direccion_; }
		const Tarjetas& tarjetas() const noexcept{ return tarjetas_; }
		/*Asociación con Tarjeta .*/
		void es_titular_de(Tarjeta& tarjeta);
		void no_es_titular_de(Tarjeta& tarjeta);
		/*Destructor*/
		~Usuario();
		/*Asociación  con Articulo */
		void compra(Articulo& articulo,unsigned cantidad=1u);
		/*Observadores de la asociación con artículo */
		const Articulos& compra() const noexcept{ return articulos_; }
		size_t n_articulos() const noexcept		{ return articulos_.size(); }
		/*<< como friend*/
		friend std::ostream& operator<<(std::ostream& salida,const Usuario& usuario);
	private:
		Cadena id_;
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
		Clave clave_;
		Tarjetas tarjetas_;
		Articulos articulos_;
		static std::unordered_set<Cadena> identificadores;
};

std::ostream& mostrar_carro(std::ostream& salida, const Usuario& usuario);

#endif