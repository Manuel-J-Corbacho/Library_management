#include "pedido-articulo.hpp"

/*LineaPedido*/
LineaPedido::LineaPedido(double precio_venta, unsigned cantidad): 
    precio_venta_(precio_venta), 
    cantidad_(cantidad)
{}

std::ostream& operator <<(std::ostream& salida, const LineaPedido& lineapedido) {
    salida << std::fixed << std::setprecision(2) << lineapedido.precio_venta() << " €\t" << lineapedido.cantidad();
    return salida;
}

/*PedidoArticulo*/

void Pedido_Articulo::pedir( Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad){
    articulos_de_un_pedido[&pedido].insert(std::make_pair( &articulo,LineaPedido(precio, cantidad) ));
    pedidos_de_un_articulo[&articulo].insert(std::make_pair(&pedido, LineaPedido(precio, cantidad) ));
}

void Pedido_Articulo::pedir( Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad){
    pedir( pedido, articulo, precio, cantidad);
}

//*V2 de detalle
const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& pedido){ 
    std::map<Pedido*, ItemsPedido>::iterator it = articulos_de_un_pedido.find(&pedido);
    static ItemsPedido ip;//Evitar referencia a temporales
    if( it == articulos_de_un_pedido.end() ){
        return ip=ItemsPedido();
        }else{
            return ip=it->second;
    }
}
//*/

//*V2 de ventas
const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& articulo){ 
    std::map<Articulo*, Pedidos>::iterator it = pedidos_de_un_articulo.find(&articulo);
    if( it == pedidos_de_un_articulo.end() ){
        return Pedidos();
    }else{
        return it->second;
    } 
}
//*/

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& salida){
    double total = 0.0;
    for( std::pair<Pedido*, ItemsPedido> it : articulos_de_un_pedido ){//for( auto it : articulos_de_un_pedido ){
        salida << "Pedido núm. " << it.first->numero() << "\n";
        salida << "Cliente: " << it.first->tarjeta()->titular()->id() << "\t\t";
        salida << "Fecha: " << it.first->fecha()  << "\n";
        salida << it.second << "\n\n";
        for(std::pair<Articulo*, LineaPedido> it2 : it.second){//for(auto it2 : it.second){
            total += it2.second.precio_venta() * it2.second.cantidad();
        }
    }
    salida << "TOTAL VENTAS \t\t" << std::fixed << std::setprecision(2) << total << " €\n\n";
    return salida;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& salida){
    
    for( std::pair<Articulo*, Pedidos> it : pedidos_de_un_articulo){//for(auto it : pedidos_de_un_articulo){
        salida << "Ventas de " << "[" << it.first->referencia() << "] \"" << it.first->titulo() << "\"\n";
        salida << it.second << "\n";
    }
    return salida;
}

std::ostream& operator <<(std::ostream& salida, const Pedido_Articulo::ItemsPedido& items){
    double total = 0.0;
    salida << std::fixed << std::setprecision(2);   
    salida <<   "  PVP \t Cantidad \t\tArtículo\n";
    salida <<   "==================================================================\n";
    for( std::pair<Articulo*, LineaPedido> it : items){//for(auto it : items){
        salida << it.second << "\t\t";
        salida << "[" << it.first->referencia() << "] \"" << it.first->titulo() << "\"" << "\n";
        total += it.second.precio_venta() * it.second.cantidad();
    }
    salida <<   "==================================================================\n";
    salida <<   "Total:   " << total << " €";
    return salida;    
}

std::ostream& operator <<(std::ostream& salida, const Pedido_Articulo::Pedidos& pedidos){
    double total = 0.0;
    unsigned cantidadtotal = 0;
    salida << "[Pedidos: " << pedidos.size() << "]\n";
    salida << "==================================================================\n";
    salida << "  PVP\tCantidad\t\t   Fecha de venta\n";
    salida << "==================================================================\n";
    
    for( std::pair<Pedido*, LineaPedido> it : pedidos ){//for( auto it : pedidos ){
        salida << it.second << "\t\t\t" << it.first->fecha() << "\n";
        total+= it.second.precio_venta()*it.second.cantidad();
        cantidadtotal+=it.second.cantidad();
    }
    salida << "==================================================================\n";
    salida << std::fixed << std::setprecision(2) << total << " €\t" << cantidadtotal <<"\n";
    return salida;
}
