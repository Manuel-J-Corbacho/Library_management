#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iomanip>//setprecision
#include "pedido.hpp"


/*Cosas de la clase LineaPedido*/
class LineaPedido{
    public:
        explicit LineaPedido(double precio_venta, unsigned cantidad=1u);
        double precio_venta() const noexcept{  return precio_venta_; }
        unsigned cantidad() const noexcept{ return cantidad_; }
    private:
        double precio_venta_;
        unsigned cantidad_;
};

std::ostream& operator <<(std::ostream& salida, const LineaPedido& lineapedido);




/*Cosas de la clase Pedido_Articulo*/
//Los parámetros deben ser del tipo de la clave del map , así que deben ser Pedido* y Articulo*
struct OrdenaPedidos : public std::binary_function<Pedido*, Pedido*, bool> {
	bool operator()(const Pedido* p1, const Pedido* p2) const {return p1->numero() < p2->numero();}
};

struct OrdenaArticulos : public std::binary_function<Articulo*, Articulo*, bool> {
	bool operator()(const Articulo* a1, const Articulo* a2) const {return a1->referencia() < a2->referencia();}
};

class Pedido_Articulo{
    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
        void pedir( Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad=1u);
        void pedir( Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad=1u);
        
        const ItemsPedido& detalle(Pedido& pedido);//{ return articulos_de_un_pedido[&pedido]; }//V2 en cpp
        const Pedidos ventas(Articulo& articulo);//{ return pedidos_de_un_articulo[&articulo]; }//V2 en cpp           


        std::ostream& mostrarDetallePedidos(std::ostream& salida);
        std::ostream& mostrarVentasArticulos(std::ostream& salida);
    private:
        std::map<Pedido*, ItemsPedido, OrdenaPedidos> articulos_de_un_pedido;
        std::map<Articulo*, Pedidos, OrdenaArticulos> pedidos_de_un_articulo;
};

std::ostream& operator <<(std::ostream& salida, const Pedido_Articulo::ItemsPedido& items);
std::ostream& operator <<(std::ostream& salida, const Pedido_Articulo::Pedidos& pedidos);
#endif