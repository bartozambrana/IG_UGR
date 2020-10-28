#include "luzDireccional.h"
#include <iostream>

LuzDireccional::LuzDireccional(Tupla3f direccion, GLenum idLuzOpenGl, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    id = idLuzOpenGl;
    posicion=Tupla4f(direccion[0],direccion[1],direccion[2],0.0); //0.0 indica que es una luz direccional
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}


