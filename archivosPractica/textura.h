#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include <vector>
#include <string>
#include "aux.h"
//#include <GL/gl.h>

using namespace std;

class Textura {
    private:
        GLuint textura_id;
        vector<unsigned char> data;
        int with;
        int height;
    
    public:
        Textura( string archivo);
        void activar();
        void desactivar();
};

#endif