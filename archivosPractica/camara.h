#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED
#include "aux.h"
class Camara{

    private:

        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;
        Tupla3f forward;
        Tupla3f director;
        int tipo; //Ortogonal o perspectiva
        float left,right,botton,top,near,far;
        Tupla3f ejex ;
        Tupla3f ejey ;

        //Establecimiento del ejeX
        bool noEstablecidoEjeX;

        //Posición del obervador en el plano frontal caundo hay un objeto seleccionado
        float observadorX;
        float observadorY;
        
        //Posición dle observador en el plano frontal cuando no hay objeto seleccionado
        float observadorXFirstPerson;
        float observadorYFristPeron;

        //Posición de la cámara en el frame anterior caundo no hay un objeto seleccionado
        float posicionAnteriorX;
        float posicionAnteriorY;

        //Posición de la cámara en el frame anterior cuando hay un objeto seleccionado
        float posicionAnteriorFirstPersonX;
        float posicionAnteriorFirstPersonY;

        //bool objeto seleccionado
        bool objSel;

        //Bool para saber cuando la cámara se encuentra en el movimiento
        bool movimientoCamara;
        
    public:

        //Constructor de cámara
        Camara(Tupla3f eye, int tipo_camara); 

        //Rotaciones en torno al origen
        void rotarXExaminar(float angle);
        void rotarYExaminar(float angle);

        //Moviemiento de la cámara
        void mover(float x, float y);

        //Zoom para la cámara
        void zoom(float factor);

        //Setters
        void setObserver();
        void setProyeccion();
        void setObservadorXY(float valorX, float valorY);
        void setObjSel(bool sel);
        void setMovCamara(bool mov);
        void setObservadorFirstPerson();
        void setAt(Tupla3f At);
        void setEye(Tupla3f Eye);

        //getters
        float getObservadorX();
        float getObservadorY();
        Tupla3f getAt();
        
        //Rotación en torno a un objeto seleccionado
        void rotarObjetoX(float angle);
        void rotarObjetoY(float angle);

        //Rotación en primera persona
        void rotarXFirstPerson(float angle);
        void rotarYFirstPerson(float angle);
        
        
};

#endif