#include "camara.h"
#include "iostream"
using namespace std;

Camara::Camara(Tupla3f eye, int tipo_camara){
    this->eye = eye;
    at = Tupla3f(0.0,0.0,0.0);
    up = Tupla3f(0.0,1.0,0.0);
    
    tipo = tipo_camara;

    forward = {1,0,0};
    director = {1,0,0};

    observadorX = 0;
    observadorY = 0;

    posicionAnteriorX = 0;
    posicionAnteriorY = 0;
    posicionAnteriorFirstPersonX = 0;
    posicionAnteriorFirstPersonY = 0;
    
    movimientoCamara = false;

    //Clasificamos la declaración de los parámetros extrínsecos dependiendo el tipo de cámara
    switch (tipo)
    {
    case 0: //Perpectiva
        
        left = -0.1;
        right = 0.1;
        botton = -0.1;
        top = 0.1;
        near = 0.1;
        far = 2000.0;

        break;
    
    case 1: //Ortogonal
        
        left = -eye[2];
        right = eye[2];
        botton = -eye[2];
        top = eye[2];
        near = -20.0;
        far = 2000.0;
        
        break;
    }

    noEstablecidoEjeX = true;


}

void Camara::setObserver(){
       

    gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);

    if(objSel){
        rotarObjetoX(observadorX);
        rotarObjetoY(observadorY);
            
     }
     else{
            
        rotarXFirstPerson(observadorXFirstPerson);
        rotarYFirstPerson(observadorYFristPeron);
 
    }
    
}

void Camara::rotarXExaminar(float angle){
    
    glRotatef(angle,0.0,1.0,0.0);
}

void Camara::rotarYExaminar(float angle){
    
    glRotatef(angle,1.0,0.0,0.0);
}


void Camara::setProyeccion(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    switch (tipo)
    {
    case 0:
        glFrustum(left,right,botton,top,near,far);
        break;
    
    case 1:
        glOrtho(left,right,botton,top,near,far);
        break;
    }
    glMatrixMode(GL_MODELVIEW);

}

void Camara::zoom(float factor){
   
    left += (left*factor)/100;
    right += (right*factor)/100;
    top += (top*factor)/100;
    botton += (botton*factor)/100;

    
}

void Camara::mover(float x, float y){

    if(!objSel){
        
        
        float distanciaX = abs(posicionAnteriorFirstPersonX - x);
        float distanciay = abs(posicionAnteriorFirstPersonY - y);

        if(posicionAnteriorFirstPersonX > x){
           
            observadorXFirstPerson -= distanciaX;

        }else{

            observadorXFirstPerson += distanciaX;
        }
            
        if(posicionAnteriorFirstPersonY > y){

             observadorYFristPeron -= distanciay;
        }else{

            observadorYFristPeron += distanciay;
            }


        posicionAnteriorFirstPersonX = x;
        posicionAnteriorFirstPersonY = y;

    }else{
  
        float distanciaX = abs(posicionAnteriorX - x);
        float distanciay = abs(posicionAnteriorY - y);

        if(posicionAnteriorX > x)
            observadorX -= distanciaX;
        else
            observadorX += distanciaX;

        if(posicionAnteriorY > y)
            observadorY -= distanciay;
        else
            observadorY += distanciay;
            posicionAnteriorX = x;
        posicionAnteriorY = y;
    }
    
}

Tupla3f rotacionEntronoAEjeArbitrario(Tupla3f eje, float angle, Tupla3f puntoRotar){
    Tupla3f resultado = {0.0,0.0,0.0};
    
    resultado[0] = puntoRotar[0]*( cos(angle) + (eje[0]*eje[0])*(1 - cos(angle)) );
    resultado[0] += puntoRotar[1]*(( eje[1]*eje[0]*(1-cos(angle)))  + (eje[2]*sin(angle)));
    resultado[0] += puntoRotar[2] * (( eje[2]*eje[0]*(1-cos(angle)) ) - eje[1]*sin(angle) );

    resultado[1] = puntoRotar[0]*(( eje[1]*eje[0]*(1-cos(angle)))  - (eje[2]*sin(angle)));
    resultado[1] += puntoRotar[1]*( cos(angle) + (eje[1]*eje[1])*(1 - cos(angle)) );
    resultado[1] += puntoRotar[2]*(( eje[2]*eje[1]*(1-cos(angle)) ) + eje[0]*sin(angle) );

    resultado[2] = puntoRotar[0]*(( eje[0]*eje[2]*(1-cos(angle)) ) + eje[1]*sin(angle) );
    resultado[2] += puntoRotar[1]*(( eje[1]*eje[2]*(1-cos(angle)) ) - eje[0]*sin(angle) );
    resultado[2] += puntoRotar[2]*( cos(angle) + (eje[2]*eje[2])*(1 - cos(angle)) );

    return resultado;

}

void Camara::rotarXFirstPerson(float angle){
    
    if(movimientoCamara){
        //Obtenemos el vector que va desde desde el punto eye al punto a
        Tupla3f vectorDirector = at-eye;
    
        //Obtenemos los ejes de la cámara
        if(noEstablecidoEjeX){
            ejex = up.cross(vectorDirector);
            ejex = ejex.normalized();
            noEstablecidoEjeX = false;
        }

        ejey = vectorDirector.cross(ejex);
        ejey = ejey.normalized();
        //Pasamos el ángulo a radianes puesto que utilizaremos la función coseno y seno
        angle = (angle*(3.14159))/180;

        //Rotamos los vectores en torno al eje Y obtenido;
        vectorDirector = rotacionEntronoAEjeArbitrario(ejey,angle/500,vectorDirector);
        //up = rotacionEntronoAEjeArbitrario(ejey,angle/100000,up);
        ejex = rotacionEntronoAEjeArbitrario(ejey,angle/500,ejex);
    
        at = eye + vectorDirector;

    }
    
    
}



void Camara::rotarYFirstPerson(float angle){
    if(movimientoCamara){
        //Obtenemos el vector que va desde desde el punto eye al punto a
        Tupla3f vectorDirector = at-eye;
    
        //Obtenemos los ejes de la cámara
        ejex = up.cross(vectorDirector);
        ejex = ejex.normalized();

        angle = (angle*(3.14159))/180;

        //Rotamos los vectores en torno al eje Y obtenido;
        vectorDirector = rotacionEntronoAEjeArbitrario(ejex,angle/500,vectorDirector);
        //up = rotacionEntronoAEjeArbitrario(ejex,angle/1000000,up);
        ejey = rotacionEntronoAEjeArbitrario(ejex,angle/500,ejey);
        at = eye + vectorDirector;
      

    }
    
}


void Camara::rotarObjetoX(float angle){
    //OpenGL primero rota entorno al origen y después nos trasladamos para ubicarnos entorno al objeto, de modo que rotaremos en torno al objeto
    glTranslatef(at[0],at[1],at[2]);
    glRotatef(angle,0.0,1.0,0.0);
}

void Camara::rotarObjetoY(float angle){

    glTranslatef(at[0],at[1],at[2]);
    glRotatef(angle,1.0,0.0,0.0);
}



void Camara::setObservadorXY(float valorX, float valorY){
    observadorX = valorX;
    observadorY = valorY;
}

float Camara::getObservadorX(){
    return observadorX;
}

float Camara::getObservadorY(){
    return observadorY;
}

void Camara::setAt(Tupla3f At){
    at = At;
}

void Camara::setEye(Tupla3f Eye){
    eye = Eye;
}

Tupla3f Camara::getAt(){
    return at;
}

void Camara::setObjSel(bool sel){
    objSel = sel;
}

void Camara::setMovCamara(bool mov){
    movimientoCamara = mov;
}

void Camara::setObservadorFirstPerson(){
    observadorXFirstPerson = observadorX;
    observadorYFristPeron = observadorY;
}