/*Preguntar por qué da error poner los include en el hpp*/

#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

unsigned Pedido::N_pedidos = 0;


Pedido::Pedido( Usuario_Pedido& usuario_pedidos, Pedido_Articulo& pedido_articulo,  Usuario& u, const Tarjeta& t, const Fecha& fp )
    : num_(N_pedidos+1),tarjeta_(&t),fecha_(fp),total_(.0)     //&t porque es un puntero a una tarjeta
{

    if(u.n_articulos() == 0 ){ throw Vacio(u); } 
    if(&u != t.titular() )  { throw Impostor(u); }
    if(t.caducidad() < fp) { throw Tarjeta::Caducada(t.caducidad()); }
    Usuario::Articulos carro=u.compra();
    bool pedido_final_vacio=true;
    for(std::pair<Articulo*, unsigned> carrito : carro ){
        Articulo* pa =carrito.first;
        unsigned cantidad = carrito.second;
        double precio = pa->precio();
        if ( ArticuloAlmacenable* paa = dynamic_cast<ArticuloAlmacenable*>(pa) ){
            if( paa->stock() < cantidad ){
                const_cast<Usuario::Articulos&>( u.compra() ).clear();
                throw SinStock(*carrito.first);
            }
            paa->stock() -=cantidad;
            pedido_articulo.pedir(*this, *pa, precio, cantidad);
            total_+=precio*cantidad;
            pedido_final_vacio=false;
        }else if (LibroDigital* pdl = dynamic_cast<LibroDigital*>(pa) ){
            if( pdl->f_expir() > fp ){
                pedido_articulo.pedir(*this, *pa, precio, cantidad);
                total_+=precio*cantidad;
                pedido_final_vacio=false;
            }
        }
        u.compra(*pa , 0);//aquí no sé qué va 
    }
    if(pedido_final_vacio) throw Vacio(u);        
    usuario_pedidos.asocia(u, *this);
    N_pedidos++;
}

std::ostream& operator <<(std::ostream& salida, const Pedido& pedido){
    salida << "Núm. pedido: " << pedido.numero() << "\n";
    salida << "Fecha:       " << pedido.fecha() << "\n";
    salida << "Pagado con:  " << pedido.tarjeta()->tipo() << " n.º: " << pedido.tarjeta()->numero() << "\n";
    salida << "Importe:     " << std::fixed << std::setprecision(2) <<pedido.total() << " €\n";
    return salida;
}
