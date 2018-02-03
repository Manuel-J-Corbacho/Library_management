
#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(	const Autores& autores, const Cadena& referencia, const Cadena& titulo, 
					const Fecha& f_publi, const double precio):
	referencia_(referencia), 
	titulo_(titulo),
	f_publi_(f_publi),
	precio_(precio)
{
	if( autores.empty() ) throw Autores_vacios();
	autores_=autores;
}

/*Operar para la P4*/
std::ostream& operator<<(std::ostream& salida,const Articulo& a) {
	salida 	<< 	"[" << a.referencia() << "] \"" << a.titulo() << "\", " << "de ";
	Articulo::Autores::const_iterator it = a.autores().cbegin();//std::set<Autor*>::const_iterator//auto
	salida << (*it)->apellidos();
	it++;
	for(; it != a.autores().end(); it++ ){
		if( it != a.autores().end() ) { salida << ", "; }
		salida << (*it)->apellidos();
	}
	salida	<< ". "<< a.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << a.precio() <<" €\n\t";
	
	a.impresion_especifica(salida);
	return salida;
}
