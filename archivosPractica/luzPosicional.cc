#include "luzPosicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    id = idLuzOpenGL;
    this->posicion = Tupla4f(posicion[0],posicion[1],posicion[2],1.0); //1.0 indica que se trata una luz posicional
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}
