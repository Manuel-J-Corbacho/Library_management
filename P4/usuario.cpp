#include "usuario.hpp"

#include <iomanip>
#include <random>
#include <utility> // std::pair
#include <cstdlib>//rand
extern "C"{
	#include <unistd.h>
}
std::unordered_set<Cadena> Usuario::identificadores;

/* Solución 1 al s_rand
struct T
{
	T(){ std::srand(std::time(nullptr)); }
};//En clave iría :char sal[]={ cv[ std::rand() % 64 ] , cv[ std::rand() % 64 ] };
T t;*/

/* Clase clave */
Clave::Clave(const char* texto_claro){
	if(std::strlen(texto_claro) < 5){ throw Incorrecta(CORTA); }
	static const char* const cv="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./"; //char* cv mejor que char cv[] y static evita que se cree varias veces
	static std::size_t longtd = sizeof(cv)-1;//quito el \0
	static std::random_device r;
	static std::uniform_int_distribution<std::size_t> dist(0, longtd-1);
	char sal[]={ cv[ dist(r) ] , cv[ dist(r) ] };
	if ( char* constraseña = crypt(texto_claro,sal) ){ 
		clave_ = Cadena(constraseña); 
	}else{ 
		throw Incorrecta(ERROR_CRYPT); 
	}
	
}

bool Clave::verifica(const char* texto_claro) const {
	if ( char* tc = crypt(texto_claro , clave_.c_str()) ){ return tc==clave_; }
	throw Incorrecta(ERROR_CRYPT); 
}
////////////////////////////////////////////////


/////////////////Clase Usuario 	/////////////
			/////Constructor	/////
Usuario::Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apellidos,const Cadena& direccion,const Clave& clave):
	id_(id),nombre_(nombre),apellidos_(apellidos),direccion_(direccion),clave_(clave)
{
	if(!identificadores.insert(id_).second ) throw Id_duplicado(id_);
}

/*Asociación con Tarjeta .*/
void Usuario::es_titular_de(Tarjeta& tarjeta){
	if( this ==tarjeta.titular() ){
		//Insert comprueba que no se repite , si fuera un multimap , entonces sí podrían repetirse.
		tarjetas_.insert(std::make_pair(tarjeta.numero(),&tarjeta) );
	}

}

void Usuario::no_es_titular_de(Tarjeta& tarjeta){
	tarjetas_.erase(tarjeta.numero()); //Borramos por clave del contenedor
}

/*Destructor*/
Usuario::~Usuario(){
	identificadores.erase(id_);
	while( !tarjetas_.empty() ){
		tarjetas_.begin()->second->anular_titular();
		tarjetas_.erase( tarjetas_.begin() );
	}
}

/*Asociación  con Articulo */
void Usuario::compra(Articulo& articulo,unsigned cantidad){
	if(!cantidad){
		articulos_.erase(&articulo);//articulo es la key , y erase elimina en base a la key recibida
	}else{
		articulos_[&articulo]=cantidad;
		//Si uso [] y no existe la key,se introduce un nuevo elemento , at lanza excepción out_of_range;
	}
}
/*Operadores Externos .*/
std::ostream& operator<<(std::ostream& salida,const Usuario& usuario){//amigo
	salida << usuario.id() <<" ["<< usuario.clave_.clave() <<"] "<< usuario.nombre() <<" "<< usuario.apellidos() <<"\n";
	salida << usuario.direccion()<<"\n";
	salida << "Tarjetas:\n";
	for(Usuario::Tarjetas::const_iterator it=usuario.tarjetas().begin(); it!=usuario.tarjetas().end();it++){
		salida << *it->second;
	}
	return salida;
}

std::ostream& mostrar_carro(std::ostream& salida,const Usuario& usuario){
	salida << "Carrito de compra de "<<usuario.id()<<" [Artículos: "<<usuario.n_articulos()<<"]\n";
	salida << " Cant. Artículo \n";
	salida << "=========================================================== \n";
  
	for( Usuario::Articulos::const_iterator it=usuario.compra().begin(); it!=usuario.compra().end(); ++it){//for(auto it...){
		salida 	<< "  " << it->second << "   [" << it->first->referencia() << "] " 
				<< "\"" << it->first->titulo() << "\"" << ", " << it->first->f_publi().anno()  << ". "
				<< std::fixed << std::setprecision(2) << it->first->precio() << " €" << "\n";
	}
	return salida;
}