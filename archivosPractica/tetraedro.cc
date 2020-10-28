#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float size)
{

   // inicializar la tabla de vértices 
   v.push_back(Tupla3f(0,size,0));              // vertice 0        
   v.push_back(Tupla3f(-size/2,0,-size/2));     // vertice 1
   v.push_back(Tupla3f(0,0,size/2));            // vertice 2
   v.push_back(Tupla3f(size/2,0,-size/2));      // vertice 3
    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   f.push_back(Tupla3i(1,3,2));
   f.push_back(Tupla3i(0,2,3));
   f.push_back(Tupla3i(0,1,2));
   f.push_back(Tupla3i(0,3,1));
   
   for(int i = 0; i < v.size(); i++){
      color.push_back(Tupla3f(1.0,0.0,1.0));
      colorLineas.push_back(Tupla3f(0.5,1.0,0.1)); //verde pistacho
      colorPuntos.push_back(Tupla3f(0.2,0.1,1.0));
      color2Ajedrez.push_back(Tupla3f(0.0,1.0,0.0));
      colorAmarillo.push_back(Tupla3f(1.0,1.0,0.0));
   }

   ct.push_back(Tupla2f(0.5,0.5));
   ct.push_back(Tupla2f(0.0,1.0));
   ct.push_back(Tupla2f(0.0,0.0));
   ct.push_back(Tupla2f(1.0,0.0));
   textura = new Textura("./acero.jpg");

   
   calcular_normales();

}

