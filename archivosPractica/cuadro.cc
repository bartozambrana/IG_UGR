#include "cuadro.h"
#include "malla.h"

Cuadro::Cuadro(string imagen){
    v.push_back(Tupla3f(50.0,-50.0,0.0));
    v.push_back(Tupla3f(50.0,50.0,0.0));
    v.push_back(Tupla3f(-50.0,50.0,0.0));
    v.push_back(Tupla3f(-50.0,-50.0,0.0));

    f.push_back(Tupla3i(0,1,3));
    f.push_back(Tupla3i(1,2,3));

    for(int i = 0; i < v.size(); i++){
      color.push_back(Tupla3f(0.0,0.0,1.0));
      colorLineas.push_back(Tupla3f(0.8,0.4,0.0)); // naranja
      colorPuntos.push_back(Tupla3f(0.2,0.1,1.0));
      color2Ajedrez.push_back(Tupla3f(0.0,1.0,0.0));
      colorAmarillo.push_back(Tupla3f(1.0,1.0,0.0));
      
   }
   
   calcular_normales();

   ct.push_back(Tupla2f(1.0,1.0));
   ct.push_back(Tupla2f(1.0,0.0));
   ct.push_back(Tupla2f(0.0,0.0));
   ct.push_back(Tupla2f(0.0,1.0));

   textura = new Textura(imagen);
    
}