#include "textura.h"
#include "jpg_imagen.hpp"

using namespace jpg;
Textura::Textura(string archivo){
    
    Imagen * pimg = nullptr;

    //Cargamos la imagen
    pimg = new Imagen(archivo);

    //Establecemos el ancho y el alto
    with = pimg->tamX();
    height = pimg->tamY();
    //Recorremos los pixeles y establecemos sus colores rgb en data
    for(int i = 0; i < pimg->tamY(); i++)
        for(int j = 0; j < pimg->tamX(); j++){
            unsigned char *rgb = pimg->leerPixel(j,i);
            data.push_back(rgb[0]);
            data.push_back(rgb[1]);
            data.push_back(rgb[2]);
        }

}

void Textura::activar(){

    //Habilitamos las texturas
    //glEnable(GL_TEXTURE_2D);

    //Generamos el identificador
    glGenTextures(1,&textura_id); 

    //Activamos la textura
    glBindTexture(GL_TEXTURE_2D, textura_id);

    //iluminación activada
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    
    //Configuración de la textura
    //Que repita en S cuando el rango de la textura no esté en [0,1]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //Que repita en T cuando el rango de la textura no esté en [0,1]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Que se tome el valor más cercano caundo nos acercamos al objeto
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //Que se tome el valor mas cercano cuando nos alejamos del objeto
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,with,height,GL_RGB,GL_UNSIGNED_BYTE,data.data());
}

void Textura::desactivar(){
    glDisable(GL_TEXTURE_2D);
}
