/* $Id: catalogo_check.cpp 401 2017-05-24 19:45:01Z gerardo $
 * Programa para comprobar diversas buenas prácticas en el código fuente de P4
 * POO - P4 
 * ©2014-16 Pedro Delgado y los profesores de POO
 * 2017 - Adaptado al DSL - Gerardo y Pedro
 */
#include "checkCode.h"

#include <vector>
#include <iostream>

using namespace std;

int main(int argc, const char **argv){

  vector<string> functionNames = {"strlen", "strcat", "memset", "strcpy", "strcmp"};
  string headerName = "cstring";
  
  checkCode c(argc, argv, "articulo.cpp", "Orden: ./pedido_check articulo.cpp tarjeta.cpp usuario.cpp pedido.cpp pedido-articulo.cpp usuario-pedido.hpp -- -std=c++14 -I../P1");
  
  c.setCorrectMessage("Verificación correcta de las clases Articulo, ArticuloAlmacenable, Libro, Cederron, LibroDigial, Autor.");
  c.setIncorrectMessage("REVISA LOS ERRORES DE ARTICULO");
  
  if(c.findClass({"Articulo","ArticuloAlmacenable","Autor","Libro","Cederron","LibroDigital"})){
    llvm::outs() << "* articulo.cpp:\n";
    // Pedido-Check
    c.includedHeader(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");
    c.allPrivateVariableMember("Articulo", "Revisa el acceso a los atributos.");
    c.notFriendMember("Articulo", "Revisa por qué es necesario incluir 'friend'");
    c.guardClauses("articulo.hpp", "Recuerda añadir las guardas de inclusión");
    
    // Catalogo-check
    c.memberVariable("Articulo", {"stock_"}, {"?"}, {false}, "Revisa el enunciado respecto a los atributos que deben estar en cada clase.");
    c.memberVariable("ArticuloAlmacenable", {"stock_"}, {"noconst"}, {true}, "Revisa el enunciado respecto a los atributos que deben estar en cada clase.");
    c.virtualMethod({"~Articulo"},{{}},"Articulo",{"noconst"}, "Contempla crear un destructor apropiado para esta clase.");
    c.functionWithReferencedMethod({"operator<<"},{{"class std::basic_ostream<char> &","const class Articulo &"}},{"impresion_especifica"},{{"class std::basic_ostream<char> &"}},"Articulo",{"const"},"Incluya impresion_especifica en el operador de extracción");
    c.methodWithReferencedVariable({"impresion_especifica"}, {{"class std::basic_ostream<char> &"}}, "Libro", {"const"}, {"n_pag_"}, "Revisa qué debe imprimir la definición del método impresion_especifica en cada clase.");
    c.methodWithReferencedVariable({"impresion_especifica"}, {{"class std::basic_ostream<char> &"}}, "Libro", {"const"}, {"stock_"},"Revisa qué debe imprimir la definición del método impresion_especifica en cada clase.");
    c.methodWithReferencedVariable({"impresion_especifica"}, {{"class std::basic_ostream<char> &"}}, "Cederron", {"const"}, {"tam_"},"Revisa qué debe imprimir la definición del método impresion_especifica en cada clase.");
    c.methodWithReferencedVariable({"impresion_especifica"}, {{"class std::basic_ostream<char> &"}}, "Cederron", {"const"}, {"stock_"},"Revisa qué debe imprimir la definición del método impresion_especifica en cada clase.");
    c.methodWithReferencedVariable({"impresion_especifica"}, {{"class std::basic_ostream<char> &"}}, "LibroDigital", {"const"}, {"f_expir_"},"Revisa qué debe imprimir la definición del método impresion_especifica en cada clase.");
    c.method({"nombre","apellidos","direccion"}, {{},{},{}}, "Autor", {"const","const","const"}, "Revisa el uso de métodos constantes.");
    c.noExceptMethod({"nombre","apellidos","direccion"},{{},{},{}}, "Autor", {"const","const","const"}, "Revisa el enunciado respecto a las excepciones.");
    c.check();
  }else{
    llvm::outs()<<"No se han encontrado las clases 'Articulo', 'ArticuloAlmacenable', 'Autor', 'Libro', 'Cederron' y/o 'LibroDigital'\n";
  }
  
  checkCode c2(argc, argv, "tarjeta.cpp", "");
  c2.setCorrectMessage("Verificación correcta de la clase Tarjeta.");
  c2.setIncorrectMessage("REVISA LOS ERRORES DE TARJETA");
  
  llvm::outs() << "* tarjeta.cpp:\n";
  if(c2.findClass({"Tarjeta"})){
    //Pedido-check
    c2.includedHeader(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");
    c2.allPrivateVariableMember("Tarjeta", "Revisa el acceso a los atributos.");
    c2.notFriendMember("Tarjeta", "Revisa por qué es necesario incluir 'friend'");
    c2.deletedMethod({"Tarjeta", "operator="}, {{"const class Tarjeta &"}, {"const class Tarjeta &"}}, "Tarjeta", {{"?"}, {"?"}}, "Revisa el enunciado respecto a la copia de objetos.");
    c2.guardClauses("tarjeta.hpp", "Recuerda añadir las guardas de inclusión");
    c2.check();
  }else{
    llvm::outs()<<"No se ha encontrado la clase 'Tarjeta'\n";
  }
  
  
  checkCode c3(argc, argv, "usuario.cpp", "");
  c3.setCorrectMessage("Verificación correcta de la clase Usuario.");
  c3.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO");
  
  if(c3.findClass({"Usuario"})){
    llvm::outs() << "* usuario.cpp:\n";
    //Pedido-check
    c3.includedHeader(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");
    c3.allPrivateVariableMember("Usuario", "Revisa el acceso a los atributos.");
    c3.deletedMethod({"Usuario", "operator="}, {{"const class Usuario &"}, {"const class Usuario &"}}, "Usuario", {{"?"}, {"?"}}, "Revisa el enunciado respecto a la copia de objetos.");
    c3.numberOfConstructors("Usuario", 1, false, "Revisa el enunciado respecto a la construcción de objetos");
    c3.friendFunction({"operator<<"}, {{"class std::basic_ostream<char> &","const class Usuario &"}}, "Usuario", "Revisa el enunciado respecto al operador de extracción.");
    c3.guardClauses("usuario.hpp", "Recuerda añadir las guardas de inclusión");	
    c3.check();
  }else{
    llvm::outs()<<"No se ha encontrado la clase 'Usuario'\n";
  }
  
  checkCode c4(argc, argv, "pedido.cpp", "");
  c4.setCorrectMessage("Verificación correcta de la clase Pedido.");
  c4.setIncorrectMessage("REVISA LOS ERRORES DE PEDIDO");
  
  if(c4.findClass({"Pedido"})){
    llvm::outs() << "* pedido.cpp:\n";
    // Pedido-check
    c4.includedHeader(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");
    c4.allPrivateVariableMember("Pedido", "Revisa el acceso a los atributos.");
    c4.numberOfConstructors("Pedido", 1, false, "Revisa el enunciado respecto a la construcción de objetos");
    c4.defaultArgumentsInMethod({"Pedido"}, {{"?"}}, "Pedido", {"?"}, {1}, {{"Fecha()"}}, "Revisa el enunciado respecto a la construcción de objetos.");
    c4.listInitializerConstructor("Pedido", {"?"}, {"int", "const class Tarjeta *", "class Fecha", "double"}, "Revisa la lista de inicialización del constructor."); //Ponemos ? como lista de parámetros porque solo debe haber un constructor
    c4.function({"operator<<"},{{"class std::basic_ostream<char> &", "const class Pedido &"}}, "Revisa el enunciado respecto al operador de extracción.");
    c4.memberVariable("Pedido",{"tarjeta_"},{"const"},{true},"Revisa el enunciado respecto al atributo de la tarjeta de pago.\n");
    c4.guardClauses("pedido.hpp", "Recuerda añadir las guardas de inclusión");
    // Catalogo-check
    c4.methodWithDynamicCast("Pedido", {}, "noconst", "Pedido", 2, true, "Es necesario que emplees el operador de molde apropiado en el constructor de la clase.\n");
    c4.check();
  }else{
    llvm::outs()<<"No se ha encontrado la clase 'Usuario'\n";
  }
  
  checkCode c5(argc, argv, "pedido-articulo.cpp", "");
  c5.setCorrectMessage("Verificación correcta de pedido-articulo.");
  c5.setIncorrectMessage("REVISA LOS ERRORES DE PEDIDO-ARTICULO");
  
  if(c5.findClass({"Pedido_Articulo","LineaPedido"})){
    llvm::outs() << "* pedido-articulo.cpp:\n";
    // Pedido-check
    c5.numberOfConstructors("LineaPedido", 1, false, "Revisa el enunciado respecto a la construcción de objetos");
    c5.numberOfConstructors("Pedido_Articulo",0,false,"Revisa la necesidad de definir constructores.");
    vector<string> params = {"double", "unsigned int"};
    vector<vector<string> > methodsParams;
    methodsParams = {params};
    c5.defaultArgumentsInMethod({"LineaPedido"}, methodsParams, "LineaPedido", {"?"}, {1}, {{"1u"}}, "Revisa el enunciado respecto a la construcción de objetos.");
    c5.function({"operator<<"},{{"class std::basic_ostream<char> &", "const class LineaPedido &"}},"Revisa la sobrecarga del operador de extracción en LineaPedido");
    c5.explicitSpecifiedConstructor("LineaPedido",params);
    c5.method({"pedir","pedir"},{{"class Pedido &", "class Articulo &", "double", "unsigned int"}
	,{"class Articulo &", "class Pedido &", "double", "unsigned int"}},
      "Pedido_Articulo", {"noconst","noconst"}, "Se sugiere la sobrecarga del método 'pedir'");
    c5.guardClauses("pedido-articulo.hpp", "Recuerda añadir las guardas de inclusión");
    c5.check();
  }else{
    llvm::outs()<<"No se ha encontrado la clase 'Usuario'\n";
  }
  
  checkCode c6(argc, argv, "usuario-pedido.hpp", "");
  c6.setCorrectMessage("Verificación correcta de usuario-pedido.");
  c6.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO-PEDIDO.");
  
  if(c6.findClass({"Usuario_Pedido"})){
    llvm::outs() << "* usuario-pedido.hpp:\n";
    // Pedido-check
    c6.includedHeader(functionNames,headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...\n");
    c6.allPrivateVariableMember("Usuario_Pedido", "Revisa el acceso a los atributos.");
    c6.guardClauses("usuario-pedido.hpp", "Recuerda añadir las guardas de inclusión");	
    // Catalogo-check
    c6.notFriendMember("Usuario_Pedido","Revisa por qué no es necesario incluir friend.");
    c6.check();
  }else{
    llvm::outs() << "No se ha encontrado la clase 'Usuario_Pedido'.\n";
  }
}


#if 0

int main(int argc, const char **argv)
{
  checkCode c1(argc, argv, "articulo.cpp", 
	       "Orden: ./catalogo_check articulo.cpp tarjeta.cpp usuario.cpp"
	       " pedido.cpp pedido-articulo.cpp usuario-pedido.hpp -- "
	       "-std=c++14 -I../P1");
  c1.setCorrectMessage("Verificación correcta de la clase Artículo.");
  c1.setIncorrectMessage("REVISA LOS ERRORES DE ARTÍCULO.");
  if(c1.findClass("Articulo")) {
    c1.memberVariableAccessLevel("Articulo", {".*"}, "protected", 
				 "Revisa el acceso a los atributos.");
    c1.notFriendMember("Articulo", 
		       "Revisa por qué es necesario incluir 'friend'");
    c1.guardClauses("articulo.hpp", "Recuerda añadir las guardas de inclusión");
    c1.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Articulo'\n";

  checkCode c2(argc, argv, "tarjeta.cpp", "");
  c2.setCorrectMessage("Verificación correcta de la clase Tarjeta.");
  c2.setIncorrectMessage("REVISA LOS ERRORES DE TARJETA.");

  if(c2.findClass("Tarjeta")) {
    c2.memberVariableAccessLevel("Tarjeta", {".*"}, "private", 
				 "Revisa el acceso a los atributos.");
    c2.notFriendMember("Tarjeta", 
		       "Revisa por qué es necesario incluir 'friend'");
    c2.deletedMethod({"Tarjeta", "operator="}, {{"const class Tarjeta &"}, 
	  {"const class Tarjeta &"}}, "Tarjeta", {{"?"}, {"?"}}, 
      "Revisa el enunciado respecto a la copia de objetos.");
    c2.guardClauses("tarjeta.hpp", "Recuerda añadir las guardas de inclusión");
    c2.check();
  } 
  else
    llvm::outs() << "No se ha encontrado la clase 'Tarjeta'\n";

  checkCode c3(argc, argv,"usuario.cpp", "");
  c3.setCorrectMessage("Verificación correcta de la clase Usuario.");
  c3.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO.");
  if(c3.findClass("Usuario")) {
    c3.memberVariableAccessLevel("Usuario", {".*"}, "private", 
				 "Revisa el acceso a los atributos.");
    c3.deletedMethod({"Usuario", "operator="}, {{"const class Usuario &"}, 
	  {"const class Usuario &"}}, "Usuario", {{"?"}, {"?"}}, 
      "Revisa el enunciado respecto a la copia de objetos.");
    c3.numberOfConstructors("Usuario", 1, false, 
	     "Revisa el enunciado respecto a los constructores en esta clase.");
    c3.friendFunction({"operator<<"}, {{"?"}}, "Usuario", 
  "Revisa si existen funciones que deben ser marcadas como amigas de la clase");
    c3.guardClauses("usuario.hpp", "Recuerda añadir las guardas de inclusión");	
    c3.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Usuario'\n";

  checkCode c4(argc, argv,"pedido.cpp", "");
  c4.setCorrectMessage("Verificación correcta de la clase Pedido.");
  c4.setIncorrectMessage("REVISA LOS ERRORES DE PEDIDO.");

  if(c4.findClass("Pedido")) {
    c4.memberVariableAccessLevel("Pedido", {".*"}, "private", 
				 "Revisa el acceso a los atributos.");
    c4.numberOfConstructors("Pedido", 1, false, 
		  "Revisa el enunciado respecto a la construcción de objetos.");
    c4.defaultArgumentsInMethod({"Pedido"}, {{"?"}}, "Pedido", {"?"}, {1}, 
				{{"Fecha()"}}, 
	         "Revisa el enunciado respecto a la construcción de objetos.");
    //Ponemos ? como lista de parámetros porque solo debe haber un constructor
    c4.listInitializerConstructor("Pedido", {"?"}, 
				  {"int", "const class Tarjeta *", 
				      "class Fecha", "double"}, 
    "Revisa la lista de inicialización del constructor."); 	
    c4.function({"operator<<"}, {{"?"}}, 
		"Revisa el lugar de la declaración de los operadores.");
    c4.memberVariable("Pedido", {"tarjeta_"}, {"const"}, 
	 "Revisa el enunciado respecto al atributo de la tarjeta de pago.");	
    //No implementado: incrementa_numero_pedidos
    c4.guardClauses("pedido.hpp", "Recuerda añadir las guardas de inclusión");	
    c4.check();
  }
  else
    llvm::outs()<<"No se ha encontrado la clase 'Pedido'\n";

  checkCode c5(argc, argv,"pedido-articulo.cpp", "");
  c5.setCorrectMessage("Verificación correcta de la clase Pedido_Articulo.");
  c5.setIncorrectMessage("REVISA LOS ERRORES DE PEDIDO_ARTICULO.");
  if(c5.findClass("Pedido_Articulo")) {
    c5.numberOfConstructors("Pedido_Articulo", 0, false, 
			    "Revisa la necesidad de definir constructores.");
    c5.numberOfConstructors("LineaPedido", 1, false, 
	      "Revisa el enunciado respecto a los construcción de LineaPedido");
    vector<string> params = {"double", "unsigned int"};
    vector<vector<string>> methodsParams;
    methodsParams = {params};
    //c5.method({"LineaPedido"}, methodsParams, "LineaPedido", {"?"}, "Revisa el enunciado respecto a los construcción de objetos.");
    c5.defaultArgumentsInMethod({"LineaPedido"}, methodsParams, "LineaPedido", 
				{"?"}, {1}, {{"1"}}, 
		 "Revisa el enunciado respecto al parámetro predeterminado"
				" del constructor de LineaPedido");
    c5.explicitSpecifiedConstructor("LineaPedido", params, 
     "Revisa el enunciado respecto a conversiones implícitas en LineaPedido.");
    //No comprobado: los parámetros por defecto
    c5.function({"operator<<"}, {{"?"}}, 
		"Revisa el lugar de la declaración de los operadores.");
    //'pedir' sobrecargado puede hacerse mediante la búsqueda de dos metodos 
    // con diferentes parámetros.
    c5.method({"pedir", "pedir"}, {
	{"class Pedido &", "class Articulo &", "double", "unsigned int"}, 
	{"class Articulo &", "class Pedido &", "double", "unsigned int"}
      }, "Pedido_Articulo", {"?", "?"}, 
      "Revisa la sobrecarga del método 'Pedido_Articulo::pedir'.");
    c5.guardClauses("pedido-articulo.hpp", 
		    "Recuerda añadir las guardas de inclusión múltiple.");	
    c5.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Pedido_Articulo'\n";

  checkCode c6(argc, argv,"usuario-pedido.hpp", "");
  c6.setCorrectMessage("Verificación correcta de la clase Usuario_Pedido.");
  c6.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO_PEDIDO.");
  if(c6.findClass("Usuario_Pedido")) {
    c1.memberVariableAccessLevel("Usuario_Pedido", {".*"}, "private", 
				 "Revisa el acceso a los atributos.");
    c6.guardClauses("usuario-pedido.hpp", 
		    "Recuerda añadir las guardas de inclusión");	
    c6.check();
  } else
    llvm::outs() << "No se ha encontrado la clase 'Usuario_Pedido'\n";
}
#endif
