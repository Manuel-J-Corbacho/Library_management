#ifndef _USUARIO_PEDIDO_HPP
#define _USUARIO_PEDIDO_HPP

#include <map>
#include <set>


class Usuario;
class Pedido;

class Usuario_Pedido{
    public:
        typedef std::set<Pedido*> Pedidos;
        
        void asocia(Usuario& usuario, Pedido& pedido){
            pedidosde_un_usuario[&usuario].insert(&pedido);
            usuariode_un_pedido_[&pedido] = &usuario;
        }
        
        void asocia(Pedido& pedido, Usuario& usuario){
            usuariode_un_pedido_[&pedido] = &usuario;
            pedidosde_un_usuario[&usuario].insert(&pedido);
        }

        //const Pedidos& pedidos(Usuario& usuario)noexcept{ return pedidosde_un_usuario[&usuario];}
        //const Usuario* cliente(Pedido& pedido)  noexcept{ return usuariode_un_pedido_[&pedido]; }
        const Pedidos pedidos(Usuario& usuario)noexcept{ 
            std::map<Usuario*, Pedidos>::iterator it = pedidosde_un_usuario.find(&usuario);
            if( it == pedidosde_un_usuario.end() ){
                return Pedidos();
            }else{
                return it->second;
            }
        }

        const Usuario* cliente(Pedido& pedido)  noexcept{ 
            std::map<Pedido*, Usuario*>::iterator it = usuariode_un_pedido_.find(&pedido);
            if( it == usuariode_un_pedido_.end() ){
                return nullptr;
            }else{
                return it->second;
            }
        }
    
    private:
        std::map<Usuario*, Pedidos> pedidosde_un_usuario;
        std::map<Pedido*, Usuario*> usuariode_un_pedido_;
};

#endif
