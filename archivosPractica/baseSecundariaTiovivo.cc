#include "baseSecundariaTiovivo.h"

BaseSecundariaTiovivo::BaseSecundariaTiovivo(string imagen){
    cilindro = new Cilindro(50,1,1,imagen);
}

void BaseSecundariaTiovivo::setColor(Tupla3f color){
    cilindro->setColor(color);
}

void BaseSecundariaTiovivo::setMaterial(const Material & material){
    cilindro->setMaterial(material);
}

void BaseSecundariaTiovivo::draw(int modo, bool ajedrez, bool tapas){
    glPushMatrix();
        glScalef(20,1,20);
        cilindro->draw(modo,ajedrez,tapas); //Para que se dibuje con las mismas condiciones que todos los objetos de la escena
    glPopMatrix();
}

void BaseSecundariaTiovivo::setColorSeleccionado(int color){
    cilindro->setColorSeleccionado(color);
}

void BaseSecundariaTiovivo::setAFalseColores(){
    cilindro->setAFalseColores();
}