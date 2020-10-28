#include "modeloJerárquico.h"

//*****************CONSTRUCTOR*************************

Tiovivo::Tiovivo(ObjPLY * ply,string imagenCono,string imagenBases,string imagenBarra){

    bajar = true;
    inclinarAbajo = true;

    giroParteSuperior = 0.0;
    giroZPLY = 0.0;
    translacionPLY = 0.0;
    velocidad = 1.0;

    parteSuperior = new ParteSuperiorTiovivo(ply,imagenCono,imagenBases,imagenBarra);
    base = new BasePrincipalTiovivo(imagenBases);

}

//****************METODOS******************************


void Tiovivo::setColor(Tupla3f color){

    //Ajudicamos el color a las distintas partes del objeto
    parteSuperior->setColor(color);
    base->setColor(color);

}

void Tiovivo::setMaterial(const Material & material,const Material & material2,const Material & material3){

    //Adjudicamos el material a las distintas partes del objeto
    parteSuperior->setMaterial(material,material2,material3);
    base->setMaterial(material);

}

void Tiovivo::draw(int modo, bool ajedrez, bool tapas){
    
    glPushMatrix();
        glPushMatrix();
            base->draw(modo,ajedrez,tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 2.0, 0.0); //Desplazamos 2 toda la parte superior para que se posicione encima de la base
            parteSuperior->draw(modo,ajedrez,tapas,translacionPLY,giroZPLY,giroParteSuperior);
        glPopMatrix();
    glPopMatrix();

}

//Modificar valores grados de los grados de libertad
void Tiovivo::modificarGradosLibertad(int gradoLibertad, float valor){

    switch (gradoLibertad){
        
        case 0: //Giro del Tiovivo
            giroParteSuperior += valor;
        break;
        
        case 1: //Giro del archivo ply respecto el eje z
            giroZPLY += valor;
        break;

        case 2: //Movimiento del obj ply sobre la barra
            translacionPLY += valor;
        break;
    }
    
}
void Tiovivo::acelerar(){
    velocidad += 0.2; //incrementamos la velocidad poco a poco

    

}

void Tiovivo::desacelerar(){
    //Establecemos la velocidad mínima como 0.2;
    velocidad = max(velocidad - 0.2, 0.2);

}

void Tiovivo::inicioAnimaciones(){
    
    //instante de la primera animación
    intanteUltimaAccion = steady_clock::now();
}

void Tiovivo::movimientoAutomatico(){
    
    //Calcular el tiempo desde la última acción
    const InstanteActual actual = steady_clock::now();
    const Duracion duracion = actual - intanteUltimaAccion ;
    const float segundos = duracion.count();

    intanteUltimaAccion = actual;

    //Evitamos que sobrepase el techo 
    if( bajar ){

        translacionPLY -= (segundos*velocidad)*0.10;        
        if(translacionPLY <= -4.0 )
            bajar = false;
            
    }else {

        translacionPLY += (segundos*velocidad)*0.10;
        if(translacionPLY > 4.0 )
            bajar = true;
    }

    //Evitamos que gire demasiado rapido
    
    giroParteSuperior += segundos*velocidad;

    
     if( inclinarAbajo ){
        
        giroZPLY += (segundos*velocidad)*0.10;
        
        
        if(giroZPLY >= 30.0 )
            inclinarAbajo = false;
        
    }else {
        giroZPLY -= (segundos*velocidad)*0.10;
        if(giroZPLY < -30.0 )
            inclinarAbajo = true;
    }
}

void Tiovivo::setColorSeleccionado(int color){
    parteSuperior->setColorSeleccionado(color);
    base->setColorSeleccionado(color);
}

void Tiovivo::setColoresAFalse(){
    parteSuperior->setColoresAFalse();
    base->setAFalseColores();
}