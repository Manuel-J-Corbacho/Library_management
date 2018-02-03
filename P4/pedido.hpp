#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "tarjeta.hpp"



class Usuario;
class Articulo;
class Usuario_Pedido;
class Pedido_Articulo;


class Pedido{
    public:
        class Vacio{
            public:
                Vacio(Usuario& usuario) : u(&usuario) {}
                Usuario& usuario()const noexcept{ return *u; }
            private:
                Usuario *u;
        };
        class Impostor{
            public:
                Impostor(Usuario& usuario) : u(&usuario) {}
                Usuario& usuario()const noexcept{ return *u; }
            private:
                Usuario *u;
        };
        class SinStock{
            public:
                SinStock(Articulo& articulo) : art(&articulo) {}
                const Articulo& articulo()const noexcept{ return *art; }
            private:
                Articulo *art;
        };
        Pedido( Usuario_Pedido& usuario_pedidos, Pedido_Articulo& pedido_articulo, Usuario& u, const Tarjeta& t,const Fecha& fp=Fecha());
        int numero() const noexcept{ return num_;}
        const Tarjeta* tarjeta() const noexcept{ return tarjeta_; }
        Fecha fecha() const noexcept{ return fecha_; }
        double total() const noexcept{ return total_; }
        static int n_total_pedidos() noexcept{ return N_pedidos; }
    private:
        static unsigned N_pedidos;
        int num_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;
};

std::ostream& operator <<(std::ostream& salida, const Pedido& pedido);
#endif