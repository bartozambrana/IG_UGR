#ifndef _LUZDIRECCIONAL_H
#define _LUZDIRECCIONAL_H

#include "luz.h"

class LuzDireccional : public Luz{
    public:
    LuzDireccional(Tupla3f direccion, GLenum idLuzOpenGl, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
    
    
    

};

#endif