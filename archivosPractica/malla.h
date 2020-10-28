// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"
using namespace std;

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato y con tapas 
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   void draw_ajedrez(); //dibuja el objeto en modo ajedréz método de pruebas
   
   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modo, bool ajedrez) ;
   void setColor(const Tupla3f rgb);
   void setMaterial(const Material m);
   Material getMaterial()const;
   void aplicarMaterial();
   void asignacionTexturaAutomatica();
   void setColorSeleccionado(int color);
   void setAFalseColores();
   void escalarCoordenadasTextura(int escalar);
   protected:
   
   void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)
   GLuint crearVBO(GLuint tipo_vbo,GLuint tamanio_bytes, GLvoid * punturo_ram); // Se establece como protected como consecuencia de las sobreescrituras del dibujado
   GLuint id_vbo_vertices = 0,id_vbo_triangulos = 0,id_vbo_color=0,id_vbo_normales=0, id_vbo_textura = 0;
   vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   vector<Tupla3f> color;
   vector<Tupla3f> colorLineas;
   vector<Tupla3f> colorPuntos;
   vector<Tupla3f> colorAmarillo;
   bool puntos = false, lineas = false, solido = false, amarillo = false;
   vector<Tupla3f> color2Ajedrez;
   vector<Tupla3f> nv;
   Material material;
   Textura * textura= nullptr;
   vector<Tupla2f> ct;
   bool tieneMaterial = false;
   //añadir vector de colores por vértices, y relleno de vector
   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
