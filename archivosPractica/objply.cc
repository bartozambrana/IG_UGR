#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo,string imagen )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
   
   for(int i=0; i < v.size(); i++){
      color.push_back(Tupla3f(1.0,0.0,0.0));
      colorLineas.push_back(Tupla3f(0.0,1.0,1.0));
        colorPuntos.push_back(Tupla3f(0.2,0.1,1.0));
        color2Ajedrez.push_back(Tupla3f(0.0,1.0,0.0));
        colorAmarillo.push_back(Tupla3f(1.0,1.0,0.0));
   }
   calcular_normales();
   textura = new Textura(imagen);
}


