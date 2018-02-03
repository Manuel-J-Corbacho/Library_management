#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <set>

class Autor{
	public:
		Autor(const Cadena& n, const Cadena& a, const Cadena& d) noexcept:
			nombre_(n),apellidos_(a),direccion_(d)
		{}
		
		const Cadena& nombre() const noexcept { return nombre_;}
		const Cadena& apellidos() const noexcept { return apellidos_;}
		const Cadena& direccion() const noexcept { return direccion_;}
	private:
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;

};



class Articulo{
	public:
		/*P4*/
		class Autores_vacios{};
		typedef std::set<Autor*> Autores;
		
		Articulo(	const Autores& autores,	const Cadena& referencia,const Cadena& titulo, 
					const Fecha& f_publi, const double precio);
		const Autores& autores() const { return autores_; }

		//El =0 hace al método virtual puro y por lo tanto Articulo se convierte en una clase abstracta
		virtual void impresion_especifica(std::ostream& salida) const = 0;
		virtual ~Articulo(){}
		/*No modificado*/
		Cadena referencia() const noexcept	{ return referencia_;}
		Cadena titulo() const noexcept 		{ return titulo_ ;	}
		Fecha f_publi() const noexcept		{ return f_publi_;	}
		double& precio() noexcept			{ return precio_; }
		const double precio() const noexcept{ return precio_;}
		/*P4*/
	protected://Protected es private pero accesible desde clases que hereden.
		Autores autores_;
		/*No modificado*/
		Cadena referencia_;
		Cadena titulo_;
		Fecha f_publi_;
		double precio_;

};

std::ostream& operator<<(std::ostream& salida,const Articulo& a) ;

/*P4 stuff*/
//http://www.learncpp.com/cpp-tutorial/114-constructors-and-initialization-of-derived-classes/
class ArticuloAlmacenable: public Articulo{
	public:
		ArticuloAlmacenable(const Autores& autores,	const Cadena& referencia,const Cadena& titulo, 
				 	const Fecha& f_publi, double precio, unsigned stock=0):
			Articulo( autores, referencia, titulo, f_publi, precio ) , stock_(stock)
		{}

		//virtual void impresion_especifica(std::ostream& salida) const = 0; No es necesario ponerlo porque ya s ehereda	
		const unsigned stock() const noexcept	{ return stock_; }
		unsigned& stock() noexcept { return stock_; }
	protected:
		unsigned stock_;	
};

class Libro: public ArticuloAlmacenable{//test caso3-auto linea 335 y 337 añadido el 5
	public:
		Libro(	const Autores& autores,	const Cadena& referencia,const Cadena& titulo, 
				 		const Fecha& f_publi, double precio, unsigned n_pag, unsigned stock=0):
			ArticuloAlmacenable( autores, referencia, titulo, f_publi, precio, stock), n_pag_(n_pag)
		{}

		void impresion_especifica(std::ostream& salida) const {
			salida << n_pag_ << " págs., " << stock_ << " unidades.";
		}

		unsigned n_pag() const noexcept{ return n_pag_; }
	private:
		unsigned n_pag_;	
};

class Cederron: public ArticuloAlmacenable{
	public:
		Cederron(	const Autores& autores,	const Cadena& referencia,const Cadena& titulo, 
				 		const Fecha& f_publi, double precio, unsigned tam, unsigned stock=0):
			ArticuloAlmacenable( autores, referencia, titulo, f_publi, precio, stock), tam_(tam)
		{}

		void impresion_especifica(std::ostream& salida) const {
			salida << tam_ << " MB, " << stock_ << " unidades.";
		}

		double tam() const noexcept{ return tam_; }
	private:	
		unsigned tam_;
};

class LibroDigital: public Articulo {
	public:
		LibroDigital(const Autores& autores,	const Cadena& referencia,const Cadena& titulo, 
				 			const Fecha& f_publi, double precio, Fecha f_expir):
			Articulo( autores, referencia, titulo, f_publi, precio), f_expir_(f_expir)
		{}

		void impresion_especifica(std::ostream& salida) const {
			salida << "A la venta hasta el " << f_expir_ << ".";
		}
		Fecha f_expir() const noexcept {return f_expir_;}
	private:	
		Fecha f_expir_;
};


#endif

