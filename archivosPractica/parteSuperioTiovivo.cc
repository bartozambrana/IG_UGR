#include "parteSuperiorTiovivo.h"

ParteSuperiorTiovivo::ParteSuperiorTiovivo(ObjPLY * ply, string imagenCono, string imagenBase, string imagenBarra){
    this->cilindro = new Cilindro(50,1,1,imagenBarra);
    this->cono = new Cono(50,1,1,imagenCono);
    this->barraConPLY = new BarraConPLY(ply,imagenBarra);
    this->base = new BaseSecundariaTiovivo(imagenBase);

}

void ParteSuperiorTiovivo::setMaterial(const Material & material, const Material & material2,const Material & material3){
    cilindro->setMaterial(material);
    cono ->setMaterial(material);
    barraConPLY->setMaterial(material3,material2);
    base->setMaterial(material);
}

void ParteSuperiorTiovivo::setColor(Tupla3f color){
    cilindro->setColor(color);
    cono->setColor(color);
    barraConPLY->setColor(color);
    base->setColor(color);
}

void ParteSuperiorTiovivo::draw(int modo, bool ajedrez, bool tapas, float translacionPLY, float giroZPLY, float giroParteSuperior){
     glPushMatrix();

        //TERCER GRADO DE LIBERTAD
        glRotatef(giroParteSuperior,0.0,1.0,0.0); //Rotamos todos los elementos

        //Techo del Tiovivo
        glPushMatrix();
            glTranslatef(0.0 , 21.0 , 0.0);//Situación en la parte superior del tiovivo
            glScalef( 20.0 ,15.0 ,20.0 );  //Cono de radio 10, altura 15 -> Diametro 20 altura 15
            cono->draw(modo,ajedrez,tapas);
        glPopMatrix();

        //Pilar Central
        glPushMatrix();
            glTranslatef(0.0 , 1.0, 0.0); //Situamos el pilar central a 1 del suelo
            glScalef(5 , 20.5, 5);    //Establecemos de altura 20 para enlazar con el techo y dándole más anchura para parecerse a un pilar
            cilindro->draw(modo,ajedrez,tapas);
        glPopMatrix();

        //Base
        glPushMatrix(); //Enlaza con el pilar
            base->draw(modo,ajedrez,tapas);
        glPopMatrix();

        //Barras con objetos ply: Rotaremos el archivo ply siempre para que mira siempre a la derecha
        //Partiendo de la hipótesis de que inicialmente está mirando hacia la derecha

        
        //Barra frente teniendo el ejeZ hacia nosotros
        glPushMatrix();
            glTranslatef(0.0,1.0,15.0); //Situamos la barra y objeto ply bajo el techo y entre la base secundaria en el frente
            glRotatef(180 ,0.0 ,1.0 ,0.0);
            barraConPLY->draw(modo,ajedrez,tapas,translacionPLY,giroZPLY);
        glPopMatrix();
        
        //Barra izquierda, con eje Z hacia nosotros
        glPushMatrix();
            glTranslatef(-15.0,1.0,0.0);
            glRotatef(90 ,0.0 ,1.0 ,0.0); 
            barraConPLY->draw(modo,ajedrez,tapas,translacionPLY,giroZPLY);
        glPopMatrix();
        
        //Barra derecha, con eje Z hacia nosotros
        glPushMatrix();
            glTranslatef(15.0,1.0,0.0);
            glRotatef(270.0 ,0.0 ,1.0 ,0.0);
            barraConPLY->draw(modo,ajedrez,tapas,translacionPLY,giroZPLY);
        glPopMatrix();

        
        //Barra detrás, con eje Z hacia nosotros
        glPushMatrix();
            glTranslatef(0.0,1.0,-15.0);
            barraConPLY->draw(modo,ajedrez,tapas,translacionPLY,giroZPLY);
        glPopMatrix();



    glPopMatrix();
}

void ParteSuperiorTiovivo::setColorSeleccionado(int color){
    cilindro->setColorSeleccionado(color);
    cono->setColorSeleccionado(color);
    base->setColorSeleccionado(color);
    barraConPLY->setColorSeleccionado(color);
    
}

void ParteSuperiorTiovivo::setColoresAFalse(){
    cilindro->setAFalseColores();
    cono->setAFalseColores();
    base->setAFalseColores();
    barraConPLY->setAFalseColores();

}