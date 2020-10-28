#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "objply.h"
#include "tetraedro.h"
#include "cilindro.h"
#include "esfera.h"
#include "objrevolucion.h"
#include "cono.h"
#include "luzDireccional.h"
#include "luzPosicional.h"
#include "modeloJerárquico.h"
#include "cuadro.h"
#include "camara.h"


typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELILUMINACION,SELAUTOMATICO,SELMANUAL} menu;
typedef enum {PUNTOS,ALAMBRE,SOLIDO,AJEDREZ,ILUMINACION,AUTOMATICO,MANUAL} visualizacion;
typedef enum {INMEDIATO,DIFERIDO} dibujado;

//valores para incrementar / decrementar los grados de libertad
const float GiroTiovivo = 9;
const float AnguloPLY = 1;
const float TranslacionPLY = 1;

//Clase escena
class Escena
{

   private:
    //Parámetros para saber que dibujar.
    int visualizacion ,  // 1 = puntos, 2= linea, 3= solido, 4 = ajedrez
        dibujado,       // 1 = glDrawElements, 2 = VBOs
        luz;            // luz a encender desde 0 hasta 7 Por defecto vale 0 para que la escena no salga en negro
    bool objeto_cubo,objeto_tetraedro; 
    bool punto,linea,solido,ajedrez,inmediato,diferido,sinTapa;
    bool iluminacion,visualizacionIluminado;
    
    //Modo manipulación manual del grado de libertad del Tiovivo, así como el grado a manipular
    bool manipulacionGradoLibertad;
    int gradoSeleccionado;
    //animaciones
    
    bool animacionAutomatica;
    bool animacionLuz;

    //Para variar las posiciones de las luces direccionales
    char variacion;
    //Boolean para activar o desactivar las texturas
    bool texturas;
    
    //*****************************************************
    //*********** VARIABLES PARA LA CÁMARA*****************
    //*****************************************************

    //Bool para saber si se ha movido de posición una cámara
    bool movimientoCamara;
    //Bool para saber si se ha hecho scroll up or scroll down
    bool zoom;
    //Selección de la cámara
    int camaraSeleccionada;
    //Posición anterior de la cámara
    int posicionXCamara;
    int posicionYCamara;
    //Tanto por ciendo de incremento del zoom
    int factorZoom;
    //bool para indicar selección de cámaras activado
    bool seleccionCamaras;
    bool objetoSeleccionadoAntes;
    bool algunoAmarillo;
    //****************************************************

    //Matriz identidad
    GLdouble identidad[16]={1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,1};


 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    

    
   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
    ObjPLY * obj_noria = nullptr;
    Cilindro * cilindro = nullptr;
    ObjRevolucion * revolucion_peon_1 = nullptr;
    Esfera * esfera = nullptr;
    Cono * cono = nullptr;
    LuzPosicional *luz0 = nullptr;
    LuzDireccional *luz1 = nullptr;
    LuzDireccional *luz2= nullptr;
    Tiovivo * tiovivo = nullptr;
    ObjPLY * f16 = nullptr;
    Cuadro * cuadro = nullptr;
    Cuadro * cuadro2 = nullptr;
    Cilindro * cilindro2 = nullptr;
    vector<Camara> camaras;
   
    //Valores de los colores de los objetos, cada uno ha de estar de un color diferente
    vector<Tupla3i> colores;

    //Selección del objeto a pintar de amarillo
    int objetoSeleccionado;

    //Vector con los objetos a pintar de amarillo
    vector<bool> pintarAmarillo;

    //Localización de los objetos
    vector<Tupla3f> coordenadasObjetos;

    //Posiciones de mira de partida de las camaras
    vector<Tupla3f> puntoMiraOriginal;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    //Menú
    void Menu(int opcion, bool visualizacion, bool manipulacion)const;
    //Animación modelo jerárquico
    void animarModeloJerrarquico();

    //Para cuando se pulse alguna tecla del ratón
    void clickRaton( int boton, int estado, int x, int y);

    //Para cuando se mueva el ratón
    void ratonMovido(int x, int y);

    //Establecer el objeto seleccionado con el ratón
    void pickColor(int x, int y);

    //Función para dibujar "como segunda pantalla"
    void dibujaPreviaSeleccion();

    void dibujarSeleccion();
};
#endif
