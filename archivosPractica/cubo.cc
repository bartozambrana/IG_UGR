#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   float lado2 = lado/2;
   // v.push_back(Tupla3f(-lado2,0,lado2));        //vertice 0
   // v.push_back(Tupla3f(lado2,0,lado2));         //vertice 1
   // v.push_back(Tupla3f(-lado2,lado,lado2));     //vertice 2
   // v.push_back(Tupla3f(lado2,lado,lado2));      //vertice 3
   // v.push_back(Tupla3f(-lado2,0,-lado2));       //vertice 4
   // v.push_back(Tupla3f(lado2,0,-lado2));        //vertice 5
   // v.push_back(Tupla3f(-lado2,lado,-lado2));    //vertice 6
   // v.push_back(Tupla3f(lado2,lado,-lado2));     //vertice 7

   v.push_back(Tupla3f(0,0,lado));        //vertice 0
   v.push_back(Tupla3f(lado,0,lado));         //vertice 1
   v.push_back(Tupla3f(0,lado,lado));     //vertice 2
   v.push_back(Tupla3f(lado,lado,lado));      //vertice 3
   v.push_back(Tupla3f(0,0,0));       //vertice 4
   v.push_back(Tupla3f(lado,0,0));        //vertice 5
   v.push_back(Tupla3f(0,lado,0));    //vertice 6
   v.push_back(Tupla3f(lado,lado,0));     //vertice 7

   f.push_back(Tupla3i(0,1,2));    //Cara Frente 1        
   f.push_back(Tupla3i(1,3,2));    //Cara Frente 2
   f.push_back(Tupla3i(2,3,7));    //Cara Superior 1
   f.push_back(Tupla3i(2,7,6));    //Cara Superior 2
   f.push_back(Tupla3i(1,5,3));    //Cara Derecha 1
   f.push_back(Tupla3i(3,5,7));    //Cara Derecha 2
   f.push_back(Tupla3i(7,5,4));    //Cara Trasera 1
   f.push_back(Tupla3i(6,7,4));    //Cara Trasera 2
   f.push_back(Tupla3i(0,4,1));    //Cara Inferior 1
   f.push_back(Tupla3i(1,4,5));    //Cara Inferior 2
   f.push_back(Tupla3i(0,6,4));    //Cara Izquierda 1
   f.push_back(Tupla3i(0,2,6));    //Cara Izquierda 2
   
   //rellenamos el vector con los colores de los vértices:
   for(int i = 0; i < v.size(); i++){
      color.push_back(Tupla3f(0.0,1.0,1.0)); //morado oscuro
      colorLineas.push_back(Tupla3f(0.0,1.0,1.0));
      colorPuntos.push_back(Tupla3f(0.2,0.1,1.0));
      color2Ajedrez.push_back(Tupla3f(0.0,1.0,0.0));
      colorAmarillo.push_back(Tupla3f(1.0,1.0,0.0));
   }
   //textura = new Textura("./text-madera.jpg");
   
   calcular_normales();
}

