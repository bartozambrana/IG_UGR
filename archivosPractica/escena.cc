

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

using namespace std;

//**************************************************************************
// Zonas de codigo comentadas como consecuencia de preguntar si se necesita visualizar el sombreado suave y el plano
//**************************************************************************
/*
  Combiar puesto que puede ser que el triangulo se encuentre deformado siendo una línea, de mod que 
   
*/
void MensajePrincipal(){
   cout << "Se encuentra en el menú principal, opciones disponibles: " << endl
        << "\t O despliega submenú de elección de objeto a dibujar" << endl 
        << "\t V despliaga submenú de elección de modo de visualización" << endl
        << "\t T activar / desactivar las texturas de la escena " << endl
        << "\t D despliega submenú de elección de modo de visualización" << endl
        << "\t C despliega submenú de elección de cámara" << endl
        << "\t A Activa/Desactiva la animación automática de los objetos de la escena" << endl
        << "\t M Gira manualmente el objeto Tiovivio" << endl
        << "\t Q finalizar ejecución del programa" << endl;
}

void Mensajes(char letra){
   if(letra == 'O'){
       cout << "\t C activa/desactica la visualización del Cubo" << endl  
           << "\t P activa/desactica la visualización del Tetraedro" << endl
           << "\t Q letra para salir del submenu" << endl;
   }else if(letra == 'V'){
      cout << "\t L activa/desactica la visualización en modo alambre, y desactiva la iluminación" << endl  
           << "\t P activa/desactica la visualización en modo punto, y desactiva la iluminación" << endl
           << "\t A activa/desactica la visualización en modo ajedrez, y desactiva la iluminación" << endl
           << "\t I activa la visualización con iluminacion " << endl
           << "\t T activar / desactivar tapas de los objetos de revolución " << endl
           << "\t Q para salir del submenu" << endl;
   }else if(letra == 'D'){
      cout << "Opciones disponibles visualizado iluminado, ha de estar en el menú inicial para ejecutarlos" << endl 
           << "\t 1 activa/desactica dibujado en modo inmediato" << endl  
           << "\t 2 activa/desactica dibujado en modo diferido" << endl
           << "\t A variación alfa " << endl
           << "\t B variación beta " << endl
           << "\t Q para salir del submenu" << endl;
      
   }

}

void MesajesVisualizacionIluminado(){
     cout << "Movimiento manual del Tiovivo" << endl;
     cout  << "\t 1 Activa luz direccional morada" << endl
           << "\t 2 Activa luz direccional verde pistacho " << endl
           << "\t 0 Activa/Desactiva luz posicional Blanca" << endl
           << "\t A Activa el modo variación del ángulo alfa(EJE Y)" << endl
           << "\t B Activa el modo variación del ángulo beta(EJE X)" << endl
           << "\t > Incrementa el ángulo según lo último pulsado" << endl
           << "\t < Decrementa el ángulo según lo último pulsado" << endl;




}

void MensajesManipulacionGradoLibertad(){
      cout << "Manipulación manual, opciones:" << endl;
      cout << "\t 1 Activa el grado de libertadad de variación del ángulo de los objetos" << endl
           << "\t 2 Activa el grado de libertad del movimiento de los objetos por la barra " << endl
           << "\t 0 Activa el grado de libertad del giro del tiovivo" << endl
           << "\t + Aumenta el valor aplicado al grado de libertad seleccionado" << endl
           << "\t - Disminuya el valor aplicado al grado de libertad seleccionado" << endl
           << "\t Q Se sale del momo de animación manual del tiovivo" << endl;
}

void MenajesAnimacionAutomatica(){
   cout << "Opciones disponibles para la animación automática" << endl;
   cout << "\t + Aumenta la velocidad " << endl
        << "\t - Disminuye la velocidad" << endl;
   
}
void Escena::Menu(int opcion, bool visualizacion, bool manipulacion)const{
   //Realizamos un SWITCH con las disintas opciones del menú.

   if(iluminacion && modoMenu != SELVISUALIZACION)
      MesajesVisualizacionIluminado();
   if(manipulacion)
      MensajesManipulacionGradoLibertad();
   else if (animacionAutomatica) 
      MenajesAnimacionAutomatica();
   else if (seleccionCamaras){
      cout << "Introduzca 0,1,2 para seleccionar la cámara que desee " << endl;
   }
   switch (opcion)
   {
      case SELVISUALIZACION:
         Mensajes('V');
         break;
      case SELDIBUJADO:
         Mensajes('D');
         break;
      case SELOBJETO:
         Mensajes('O');
         break;

      case NADA:
         MensajePrincipal();
         break;
   }
   
}

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   objeto_cubo = false;
   objeto_tetraedro = false;
   visualizacion = 3; //Solido por defecto
   dibujado = 1; // 1 inmediato, 2 diferido, 3 ajedrez;
   luz = -1;
   punto = false;
   linea = false;
   solido = true;
   ajedrez = false;
   inmediato = true;
   diferido = false;
   sinTapa = false;
   iluminacion = false;
   visualizacionIluminado = false;
   texturas = false;
   movimientoCamara = false;
   zoom = false;
   seleccionCamaras = false;
   camaraSeleccionada = posicionXCamara = posicionYCamara = 0;
   objetoSeleccionadoAntes  = false;
   algunoAmarillo = false;

   camaras.push_back(Camara({-500.0,50.0,300.0},0));
   camaras.push_back(Camara({0.0,0.0,300.0},1));
   camaras.push_back(Camara({500.0,50.0,10.0},0));
   // camaraSeleccionada = 1;

   pintarAmarillo.resize(6,false);

   //Inicialmente no se cuentra seleccionado la variación del grado de libertad
   gradoSeleccionado = -1;
   manipulacionGradoLibertad = false;

   animacionLuz = false;
   animacionAutomatica = false;

   cuadro = new Cuadro("./cesped.jpg");
   cuadro ->escalarCoordenadasTextura(10);
   cuadro2 = new Cuadro("./montaña2.jpg");

   //Modelo jerárquico
   f16 = new ObjPLY("./archivosPLY/modelos_ply/f16.ply","./guerra.jpg");
   f16->setColor(Tupla3f(0.0,1.0,0.0));

   tiovivo = new Tiovivo(f16,"./nuebes.jpg","./text-madera.jpg","./acero.jpg");
   cubo = new Cubo(30);
   tetraedro = new Tetraedro(30);
   obj_noria = new ObjPLY("./archivosPLY/ferriswheel.ply","./acero.jpg");
   cilindro2 = new Cilindro(40,100,40,"text-lata-1.jpg");
   
   //Inicialización de las luces tiene que haber al menos una posicional y una direccional
   luz0 = new LuzPosicional(Tupla3f(0.0,25.0,50.0),GL_LIGHT0,Tupla4f(1.0,1.0,1.0,1.0), Tupla4f(1.0,0.0,0.1,1.0),Tupla4f(1.0,1.0,1.0,1.0)); //luz por defecto
   //luz0 = new LuzPosicional(Tupla3f(0.0,25.0,0.0),GL_LIGHT0,Tupla4f(1.0,1.0,1.0,1.0), Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0)); //luz por defecto
   //Luz Morada
   luz1 = new LuzDireccional(Tupla3f(0.0,50.0,10.0),GL_LIGHT1,Tupla4f(0.0,0.0,0.2,1.0), Tupla4f(0.7,0.0,0.1,1.0),Tupla4f(0.3,0.0,0.7,1.0));
   
   //luz1 = new LuzDireccional(Tupla3f(-50.0,150.0,1),GL_LIGHT1,Tupla4f(0.4,0.5,0.1,0.0), Tupla4f(0.3,0.5,0.7,0.0),Tupla4f(0.4,0.5,0.1,0.0));
   //Luz Verde Pistacho
   luz2 = new LuzDireccional(Tupla3f(0,20,100),GL_LIGHT2, Tupla4f(0.5,0.2,0.0,1.0),Tupla4f(0.5,0.1,1.0,1.0), Tupla4f(0.0,0.7,0.0,1.0));

   //Materiales
   Material materialPerla( Tupla4f(1.0,0.829,0.829,1.0), Tupla4f(0.296648,0.296648,0.296648,1.0), Tupla4f(0.25,0.20725,0.20725,1.0) ,0.088);
   Material materialRuby( Tupla4f(0.61424,0.04136,0.04136,1.0), Tupla4f(0.727811,0.626959,0.626959,1.0), Tupla4f(0.1745,0.01175,0.01175,1.0),0.6);
   Material materialOro(Tupla4f(	0.75164,0.60648,0.22648,1.0), Tupla4f(0.628281,0.555802,0.366065,1.0),Tupla4f(0.24725,0.1995,0.0745,1.0),0.4);
   Material materialPlata(Tupla4f(0.50754,0.50754,0.50754,0.0),Tupla4f(0.508273,0.508273,0.508273,0.0), Tupla4f(0.19225,0.19225,0.19225,0.0),0.4);
   Material materialObjetoElegido(Tupla4f(0.07568,0.61424,0.07568,1.0),Tupla4f(0.633,0.727811,0.633,1.0), Tupla4f(0.0215,0.1745,0.0215,1.0),0.6);

   //Introducción de los materiales a los objetos
   cubo->setMaterial(materialOro);
   tetraedro->setMaterial(materialRuby);
   obj_noria->setMaterial(materialPerla);
   
   tiovivo->setMaterial(materialOro,materialRuby,materialPerla);
   cuadro2->setMaterial(materialPlata);
   cuadro->setMaterial(materialPerla);

   //Isertamos los colores de los objetos
   colores.push_back(Tupla3i(0,0,255));//Cuadro1
   colores.push_back(Tupla3i(0,0,255));//Cuadro2
   colores.push_back(Tupla3i(0,255,0));//Tiovivo
   colores.push_back(Tupla3i(0,255,255));//Cubo
   colores.push_back(Tupla3i(255,0,255));//Tetraedro
   colores.push_back(Tupla3i(255,0,0));//Noria

   objetoSeleccionado = -1;
  
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
   glEnable(GL_CULL_FACE);//Habilitamos el cull face

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

   MensajePrincipal();
}

//Animar modelo jerarquico

void Escena::animarModeloJerrarquico(){
   if(animacionAutomatica){
      tiovivo->movimientoAutomatico();
      
   }
   if(animacionLuz)
      luz0->movimientoAutomatico();
      
}
// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujarSeleccion(){
   if(algunoAmarillo){
      objetoSeleccionadoAntes = true;
   }else
      objetoSeleccionadoAntes = false;
   

if(iluminacion)//iluminación activada
   {
      glEnable(GL_NORMALIZE);
      glEnable(GL_LIGHTING);

      switch (luz)
      {
      case 0:
         if(glIsEnabled(GL_LIGHT0) == GL_TRUE && (glIsEnabled(GL_LIGHT1) == GL_TRUE || glIsEnabled(GL_LIGHT2) == GL_TRUE)) //Permitiendo que nunca se quede la escena en negro
            luz0->desactivar();
         else 
            luz0->activar();

         if(glIsEnabled(GL_LIGHT0) == GL_TRUE && (glIsEnabled(GL_LIGHT1) == GL_FALSE && glIsEnabled(GL_LIGHT2) == GL_FALSE))
            cout << "Tiene que haber al menos una luz activada con la iluminación dada" << endl;
         break;
      
      case 1:
         if(glIsEnabled(GL_LIGHT1) == GL_TRUE && (glIsEnabled(GL_LIGHT0) == GL_TRUE || glIsEnabled(GL_LIGHT2) == GL_TRUE)) //Permitiendo que nunca se queda la escena en negro
            luz1->desactivar();
         else{
            luz1->activar();
         }
         if(glIsEnabled(GL_LIGHT1) == GL_TRUE && (glIsEnabled(GL_LIGHT0) == GL_FALSE && glIsEnabled(GL_LIGHT2) == GL_FALSE))
            cout << "Tiene que haber al menos una luz activada con la iluminación dada" << endl;
         break;

      case 2:
         if(glIsEnabled(GL_LIGHT2) == GL_TRUE && (glIsEnabled(GL_LIGHT1) == GL_TRUE || glIsEnabled(GL_LIGHT0) == GL_TRUE)) //Permitiendo que nunca se quede la escena en negro
            luz2->desactivar();
         else 
            luz2->activar();
         
         if(glIsEnabled(GL_LIGHT2) == GL_TRUE && (glIsEnabled(GL_LIGHT1) == GL_FALSE && glIsEnabled(GL_LIGHT0) == GL_FALSE))
            cout << "Tiene que haber al menos una luz activada con la iluminación dada" << endl;

         break;
      default: //Luz por defecto en el caso de que no haya ninguna encendida
         if(glIsEnabled(GL_LIGHT1) == GL_FALSE && glIsEnabled(GL_LIGHT2) == GL_FALSE)
            luz0->activar();
         break;
      }
      luz = -1; //Para evitar que la ultima luz pulsada se desactive y active al girar la escena
   }
   else{ //iluminación desactivada
      //Apagamos luces encendidas
      if(glIsEnabled(GL_LIGHT1) == GL_TRUE)
         luz1->desactivar();
      else if(glIsEnabled(GL_LIGHT0) == GL_TRUE)
         luz0->desactivar();
      else if(glIsEnabled(GL_LIGHT1) == GL_TRUE)
         luz2->desactivar();

      glDisable(GL_LIGHTING);
   }

   //Animación de la luz puntual para que acelere

   //HABILITACIÓN DE TEXTURAS
   if(texturas)
      glEnable(GL_TEXTURE_2D);
   else
      glDisable(GL_TEXTURE_2D);
   
   
   
   Tupla3f color;
   vector<int> dibujados;
      
   if(linea)
      dibujados.push_back(1);
   if(punto)
      dibujados.push_back(2);
   if(solido || ajedrez)
      dibujados.push_back(3);


   


   //establece los distintos visualizados y dibujados de objetos.
   for(int i = 0; i < dibujados.size(); i++){
      switch (dibujados[i])
      {
      case 1: //linea

         glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         break;
      case 2: //punto
         color = Tupla3f(0.2,0.1,1);

         glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
         break;
      case 3: //solido también sirve para el modo ajedrez
;
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         break;
      }
      if(cuadro != nullptr){
         
         glPushMatrix();
            glScalef(4.0,4.0,4.0);
            glRotatef(-90,1.0,0.0,0.0);
            cuadro->setAFalseColores();
            // if(pintarAmarillo[0])
            //    cuadro->setColorSeleccionado(4);
            // else         
               cuadro->setColorSeleccionado(dibujados[i]);
            cuadro->draw(dibujado,ajedrez);
            if(pintarAmarillo[5] && iluminacion){
                  glEnable(GL_LIGHTING);
               }
         glPopMatrix();
      }
      
      if(cuadro2 != nullptr){
         
         glPushMatrix();
            glTranslatef(0.0,200.0,-200.0);
            glScalef(4.0,4.0,4.0);
            cuadro2->setAFalseColores();
            // if(pintarAmarillo[0])
            //    cuadro2->setColorSeleccionado(4);
            // else
               cuadro2->setColorSeleccionado(dibujados[i]);            
            cuadro2->draw(dibujado,ajedrez);
         glPopMatrix();
      }

      if(tiovivo != nullptr){
         
         glPushMatrix();
            glScalef(2.0,2.0,2.0);
            tiovivo->setColoresAFalse();
            if(pintarAmarillo[2]){
               tiovivo->setColorSeleccionado(4);
               camaras[camaraSeleccionada].setObjSel(true);
               camaras[camaraSeleccionada].setAt({0.0,0.0,0.0});
               glDisable(GL_LIGHTING);
            }else
               tiovivo->setColorSeleccionado(dibujados[i]);
            tiovivo->draw(dibujado,ajedrez,!sinTapa);
            if(pintarAmarillo[2] && iluminacion){
                  glEnable(GL_LIGHTING);
               }
         glPopMatrix();
      }

      if(objeto_cubo){
        
         glPushMatrix();
            glTranslatef(80.0,0.0,40.0);
            cubo->setAFalseColores();
            if(pintarAmarillo[3]){
               cubo->setColorSeleccionado(4);
               camaras[camaraSeleccionada].setObjSel(true);
               camaras[camaraSeleccionada].setAt({-95.0,0.0,-55.0});
               glDisable(GL_LIGHTING);
            } else
               cubo->setColorSeleccionado(dibujados[i]);
            cubo->draw(dibujado,ajedrez);
            if(pintarAmarillo[3] && iluminacion){
                  glEnable(GL_LIGHTING);
               }
         glPopMatrix();
      }
      
      // glPushMatrix();
      //    glTranslatef(100.0,0.0,100.0);
      //    cilindro2->draw(dibujado,ajedrez,!sinTapa);
      // glPopMatrix();


      if(objeto_tetraedro){
         //tetraedro->setMaterial(materialPerla);
         
         glPushMatrix();
            glTranslatef(80.0, 0.0, -30.0);
            tetraedro->setAFalseColores();
            if(pintarAmarillo[4]){
               tetraedro->setColorSeleccionado(4);
               camaras[camaraSeleccionada].setObjSel(true);
               camaras[camaraSeleccionada].setAt({-80,0.0,30});
               glDisable(GL_LIGHTING);
            }
               
            else
               tetraedro->setColorSeleccionado(dibujados[i]);
            tetraedro->draw(dibujado,ajedrez);
            if(pintarAmarillo[4] && iluminacion){
                  glEnable(GL_LIGHTING);
               }
         glPopMatrix();
      }
     
      if(obj_noria != nullptr){
         glPushMatrix();
            glTranslatef(-100.0,0.0,-100.0);
            glRotatef(90,0.0,1.0,0.0);
            glScalef(0.2,0.2,0.2);
            obj_noria->setAFalseColores();
            
            if(pintarAmarillo[5]){
               obj_noria->setColorSeleccionado(4);
               //if(camaras[camaraSeleccionada].getAt()[0] == 0){
                  camaras[camaraSeleccionada].setObjSel(true);
                  camaras[camaraSeleccionada].setAt({100.0,0.0,100.0});
               //camaras[camaraSeleccionada].setEye({0.0,0.0,20.0});
               //}
               glDisable(GL_LIGHTING);
            }
            else
               obj_noria->setColorSeleccionado(dibujados[i]);
               
            obj_noria->draw(dibujado,ajedrez);
            if(pintarAmarillo[5] && iluminacion){
                  glEnable(GL_LIGHTING);
               }
         glPopMatrix();
      }
   }
   bool algunoAmarillo = false;
   for(int i = 0; i < pintarAmarillo.size() && !algunoAmarillo; i++){
      if(pintarAmarillo[i])
         algunoAmarillo = true;
   }
      
   if(!algunoAmarillo && objetoSeleccionadoAntes){
      //Ponemos que se igule el obsevador de primera persona al observador X,Y
      camaras[camaraSeleccionada].setObservadorFirstPerson();
   }
   if(!algunoAmarillo){
       camaras[camaraSeleccionada].setObjSel(false);
   }
     
}
void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   
   if(glIsEnabled(GL_LIGHTING) == GL_TRUE){ //Apagamos las luces si estan dadas para pintar los ejes de color plano
      glDisable(GL_LIGHTING);
      glDisable(GL_NORMALIZE);

   }
   if(glIsEnabled(GL_TEXTURE_2D) == GL_TRUE)
      glDisable(GL_TEXTURE_2D);

   ejes.draw();
   
   dibujarSeleccion();
   
   
   
   
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         manipulacionGradoLibertad = false;
         seleccionCamaras = false;
         if(modoMenu == SELILUMINACION)
            modoMenu = SELVISUALIZACION;

         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO;
         cout << "Selección de objetos" << endl;
         break;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout << "Selección de modo de visualización" << endl;
               
         break ;
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "Selección de modo de dibujado" << endl;
         break ;
      case 'C' :
         if(modoMenu != SELAUTOMATICO && modoMenu != SELDIBUJADO && modoMenu != SELMANUAL && modoMenu != SELVISUALIZACION && modoMenu != SELOBJETO)
            seleccionCamaras = true;
         if(modoMenu == SELOBJETO){
            if(objeto_cubo)
               objeto_cubo = false; 
            else
               objeto_cubo = true;//cubo
            cout << "Se activa o se desactiva el Cubo" << endl;
         }else 
            modoMenu=NADA;
         break;
      case 'T' :
         if(modoMenu == SELOBJETO || modoMenu == SELVISUALIZACION)
            if(!sinTapa && modoMenu == SELVISUALIZACION)
               sinTapa = true;
            else
               sinTapa = false;
               
            if(modoMenu == SELOBJETO){
               if(objeto_tetraedro)
                  objeto_tetraedro = false;
               else
                  objeto_tetraedro = true; //trapecio
               cout << "Se activa o se desactiva el Trapecio" << endl;
            }
         else if (modoMenu == NADA)
            if(!texturas)
               texturas = true;
            else{
                texturas = false;  
            }
         else{
            modoMenu = NADA;
         }
         
            
         break;
      case 'P' :
         if(iluminacion ){
            if(!animacionLuz){
               animacionLuz = true;
               luz0->inicioAnimaciones();
            }else
            {
               animacionLuz = false;
            }
            
            
         }
            
         if(modoMenu == SELVISUALIZACION){
            visualizacion = PUNTOS;
            if(!punto){
               punto = true;
               ajedrez = false;
            }else 
               punto = false;
            
            cout << "Se activa o se desactiva la visualización en modo puntos" << endl;
         }else if(visualizacionIluminado){
            if(animacionLuz)
               animacionLuz = false;
            else
               animacionLuz = true;
            
         }
            modoMenu=NADA;
         break;
      case 'L' : 

         if(modoMenu == SELVISUALIZACION){
            visualizacion = ALAMBRE;
            if(!linea){
               linea = true;
               ajedrez = false;
            }else
               linea = false;
            cout << "Se activa o se desactiva la visualización en modo lineas" << endl;
         }else        
            modoMenu=NADA;
         break;

      case 'S' : 

         
         if(modoMenu == SELVISUALIZACION){
            visualizacion = SOLIDO;
            if(!solido){
               solido = true;
               ajedrez = false;
            }else 
               solido  = false;
            
            
            
         }else 
            modoMenu=NADA;
         break;
      case 'A' :
         if(iluminacion){
            variacion = 'A';
            //modoMenu = SELILUMINACION;

         }
            
         if(modoMenu == SELVISUALIZACION){
            visualizacion = AJEDREZ;
            if(!ajedrez){
               ajedrez = true;
               solido = false;
               punto = false;
               linea = false;
            }else{
               ajedrez = false;
            }           
            cout << "Se activa o desactiva la visualiación en modo ajedrez" << endl;
            
            
         }else if(modoMenu == NADA){ 
            modoMenu = SELAUTOMATICO;
            cout << "Entro automativo" << endl;
            if(!animacionAutomatica){
               animacionAutomatica = true;
               tiovivo->inicioAnimaciones();
            }else 
               animacionAutomatica = false;
            
            if(!animacionLuz ){
               animacionLuz = true;
               luz0->inicioAnimaciones();

            }else 
               animacionLuz = false;
         }
         if(modoMenu != SELVISUALIZACION && modoMenu != SELAUTOMATICO && !iluminacion)
            modoMenu = NADA;
         break;
      
      case 'M':
         modoMenu = SELMANUAL;
         manipulacionGradoLibertad = true;
      break;
      case '0' :
         if(manipulacionGradoLibertad)
            gradoSeleccionado = 0; 
      break;
      case '1' : 
         if(manipulacionGradoLibertad)
            gradoSeleccionado = 1;
         else if(modoMenu == SELDIBUJADO){
               dibujado = 1;
         }else if(!visualizacionIluminado)
            modoMenu=NADA;
         break;

      case '2' :
         if(manipulacionGradoLibertad)
            gradoSeleccionado = 2;
         else if(modoMenu == SELDIBUJADO){
           dibujado = 2;
            
         }else 
            modoMenu=NADA;
         break;

      case 'I':
         if(modoMenu == SELVISUALIZACION){
            modoMenu = SELILUMINACION;
            if(!iluminacion){
               visualizacion = ILUMINACION;
               iluminacion = true;
               ajedrez = false;
               modoMenu = SELILUMINACION;

               cout << "Se activa la iluminación" << endl;
            }
            
            
         }else{
            modoMenu = NADA;
         }
         
         

         
      break;

      case 'B':
         if(iluminacion)
            variacion = 'B';
      break;

      
      case '<':
         if(variacion == 'A'){

            luz0->variarAnguloAlpha(-10);
            cout << "variando alpha" << endl;
         }else if (variacion == 'B')
            luz0->variarAnguloBeta(-10);
            
      break;

      case '>':
         if(variacion == 'A'){
            luz0->variarAnguloAlpha(10);
            cout << "variando alpha" << endl;
         }else if (variacion == 'B')
            luz0->variarAnguloBeta(10);
      break;



      case '+': 
         if(manipulacionGradoLibertad)
            switch (gradoSeleccionado)
            {
            case 0:
               tiovivo->modificarGradosLibertad(gradoSeleccionado,GiroTiovivo);
               break;
            case 1:
               tiovivo->modificarGradosLibertad(gradoSeleccionado,AnguloPLY);
               break;

            case 2:
               tiovivo->modificarGradosLibertad(gradoSeleccionado,TranslacionPLY);
               break;
            }
         else if(modoMenu == SELAUTOMATICO){
            
            if(animacionAutomatica){
               tiovivo->acelerar();
               cout << "Acelero " << endl;
            }
               
            
            if(animacionLuz)
               luz0->acelerar();
         }else if(animacionLuz)
               luz0->acelerar();
            
         
      break;
      case '-': 
         if(manipulacionGradoLibertad)
            switch (gradoSeleccionado)
            {
            case 0:
               tiovivo->modificarGradosLibertad(gradoSeleccionado,-GiroTiovivo);
               break;
            case 1:
               tiovivo->modificarGradosLibertad(gradoSeleccionado,-AnguloPLY);
               break;

            case 2:
               tiovivo->modificarGradosLibertad(gradoSeleccionado,-TranslacionPLY);
               break;
            }
         else if(modoMenu == SELAUTOMATICO){
            if(animacionAutomatica)
               tiovivo->desacelerar();
            if(animacionLuz)
               luz0->desacelerar();
         }else if(animacionLuz)
               luz0->desacelerar();
            
            
         
      break;

      default:
         visualizacion = NADA;
         modoMenu = NADA;
         break;   
   }


   if(modoMenu == SELVISUALIZACION && (toupper(tecla)  == 'P' || toupper(tecla) == 'L' || toupper(tecla) == 'S' || toupper(tecla) == 'A')){
      if(iluminacion)
         cout << "Se desactiva la iluminación" << endl;
      iluminacion = false;
      visualizacionIluminado = false;
      
   
   }
   
   
   if(iluminacion && (tecla <= '7' && tecla >= '0' )){
      luz = tecla - '0';
      modoMenu = SELILUMINACION;
   }
      
   if(seleccionCamaras && (tecla <= '7' && tecla >= '0')){

      //Obtenemos las posiciones de los observadores en la cámara anterior
      float observadorX = camaras[camaraSeleccionada].getObservadorX();
      float observadorY = camaras[camaraSeleccionada].getObservadorY();
      
      camaraSeleccionada = tecla - '0';

      //Cambiamos la proyección a la cámara seleccionada
      camaras[camaraSeleccionada].setProyeccion();
      //Insertamos los observadores a la cámara introducida para conservar la posción del observador
      //camaras[camaraSeleccionada].setObservadorXY(observadorX,observadorY);
   }
      
   Menu(modoMenu,iluminacion,manipulacionGradoLibertad);

   return salir;
 
         
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   // glMatrixMode( GL_PROJECTION );
   // glLoadIdentity();
   // const float wx = float(Height)*ratio_xy ;
   // glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
   
   camaras[camaraSeleccionada].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   //Antes de poner cámaras
   // glTranslatef( 0.0, 0.0, -Observer_distance );
   // glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   // glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );

   camaras[camaraSeleccionada].setObserver();
}



//*****************************************************************************
// Se pulsa alguna tecla del ratón para activarse
//*****************************************************************************

void Escena::clickRaton(int boton, int estado, int x, int y){
   
   //boton == 3 => scroll up | botton == 4 => scroll down
   //Se comportan como los botones GLUT_UP se deja de usar moviendo
   // GLUT_DOWN se está usando


   //Establecemos el moviemiento que con las flechas
   if(boton == GLUT_RIGHT_BUTTON){
      //Se mueve la cámara como si fuera las fechas, es decir se mueve mientras se tiene pulsado
      if(estado == GLUT_DOWN){
         movimientoCamara = true;
         camaras[camaraSeleccionada].setMovCamara(true);
         posicionXCamara = x;
         posicionYCamara = y;
         // if(objetoSeleccionado == -1){
         //    cout << camaras[camaraSeleccionada].getAt()[0] << " " << camaras[camaraSeleccionada].getAt()[1] << " " << camaras[camaraSeleccionada].getAt()[2] << endl;
         //    camaras[camaraSeleccionada].setAt(Tupla3f(x,y,0));
         //    cout << camaras[camaraSeleccionada].getAt()[0] << " " << camaras[camaraSeleccionada].getAt()[1] << " " << camaras[camaraSeleccionada].getAt()[2] << endl;
         // }
            

      }else{
         //Una vez que se ha dejado de pulsar ya no se rotará y se establece su posción mirándo al origen
         movimientoCamara = false;
         camaras[camaraSeleccionada].setMovCamara(false);
         // if(objetoSeleccionado){
         //    posicionXCamara = 0;
         //    posicionYCamara = 0;
         // }
         
      }
   }else if((boton == 3 || boton == 4) && (estado == GLUT_DOWN) ){
      movimientoCamara = false;
      if(boton == 3) // IMPLICA AUMENTO
         camaras[camaraSeleccionada].zoom(10);
        
      else           // IMPLECA RETROCESO
         camaras[camaraSeleccionada].zoom(-10);
         
       camaras[camaraSeleccionada].setProyeccion();
      //Aumentar y Retroceder Zoom
  
   }else if((boton == GLUT_LEFT_BUTTON) && (estado == GLUT_DOWN) ){
      pickColor(x,y);
   }

   //Para girar entorno a un objeto seleccionado hay que realizarlo posteriormente o aquí viendo si hay índices activador
   //eso realizarlo posteriormente
}

void Escena::ratonMovido(int x, int y){
   //Es decir mantenemos pulsado el botón derecho mientras movemos el ratón
   if(movimientoCamara){
      float posicion = posicionXCamara - x;
      float posicion2 = posicionYCamara -y;
      camaras[camaraSeleccionada].mover(posicion,posicion2);
      
      // if(objetoSeleccionado == -1){
      //    camaras[camaraSeleccionada].rotarXFirstPerson(camaras[camaraSeleccionada].getObservadorX());
      //    camaras[camaraSeleccionada].rotarYFirstPerson(camaras[camaraSeleccionada].getObservadorY());
      // }
   }
   //pickColor(x,y);

   //Volvemos a redibujar la escena
   glutPostRedisplay();
}

void Escena::dibujaPreviaSeleccion(){
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   
   Tupla3f color;
   vector<int> dibujados;
      
   if(linea)
      dibujados.push_back(1);
   if(punto)
      dibujados.push_back(2);
   if(solido || ajedrez)
      dibujados.push_back(3);


   


   //establece los distintos visualizados y dibujados de objetos.
   for(int i = 0; i < dibujados.size(); i++){
      switch (dibujados[i])
      {
      case 1: //linea

         glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         break;
      case 2: //punto
         color = Tupla3f(0.2,0.1,1);

         glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
         break;
      case 3: //solido también sirve para el modo ajedrez
;
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         break;
      }
      if(cuadro != nullptr){
         
         glPushMatrix();
            glScalef(4.0,4.0,4.0);
            glRotatef(-90,1.0,0.0,0.0);
            cuadro->setAFalseColores();
            cuadro->setColorSeleccionado(dibujados[i]);
            cuadro->draw(dibujado,ajedrez);
         glPopMatrix();
      }
      
      if(cuadro2 != nullptr){
         
         glPushMatrix();
            glTranslatef(0.0,200.0,-200.0);
            glScalef(4.0,4.0,4.0);
            cuadro2->setAFalseColores();
            cuadro2->setColorSeleccionado(dibujados[i]);
            cuadro2->draw(dibujado,ajedrez);
         glPopMatrix();
      }

      if(tiovivo != nullptr){
         
         glPushMatrix();
            glScalef(2.0,2.0,2.0);
            tiovivo->setColoresAFalse();
            tiovivo->setColorSeleccionado(dibujados[i]);
            tiovivo->draw(dibujado,ajedrez,!sinTapa);
         glPopMatrix();
      }

      if(objeto_cubo){
        
         glPushMatrix();
            glTranslatef(80.0,0.0,40.0);
            cubo->setAFalseColores();
            cubo->setColorSeleccionado(dibujados[i]);
            cubo->draw(dibujado,ajedrez);
         glPopMatrix();
      }
         
      if(objeto_tetraedro){
         //tetraedro->setMaterial(materialPerla);
         
         glPushMatrix();
            glTranslatef(80.0, 0.0, -30.0);
            tetraedro->setAFalseColores();
            tetraedro->setColorSeleccionado(dibujados[i]);
            tetraedro->draw(dibujado,ajedrez);
         glPopMatrix();
      }
     
      if(obj_noria != nullptr){
         glPushMatrix();
            glTranslatef(-100.0,0.0,-100.0);
            glRotatef(90,0.0,1.0,0.0);
            glScalef(0.2,0.2,0.2);
            obj_noria->setAFalseColores();
            obj_noria->setColorSeleccionado(dibujados[i]);
            obj_noria->draw(dibujado,ajedrez);
         glPopMatrix();
      }
   }
}
void Escena::pickColor(int x, int y ){
   //Desactivamos lo necesario para que funcione correctamente
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);

   GLint viewport[4];
   GLubyte pixel[3];

   
   //Limpiamos la pantalla secundaria
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 

   //LLAMAR A DIBUJAR LOS OBJETOS INTERNAMENTE
   dibujaPreviaSeleccion();

   glGetIntegerv(GL_VIEWPORT,viewport);
   glReadBuffer(GL_BACK);
   glReadPixels(x, viewport[3]-y, 1, 1,GL_RGB,GL_UNSIGNED_BYTE,(void *)&pixel);

   //Comprobamos el color del pixel seleccionado
   bool parar = false;
   objetoSeleccionado = -1;
   for(int i = 0; i < colores.size() && !parar; i++)
      if( colores[i][0] == (int)pixel[0]  && colores[i][1] == (int)pixel[1] && colores[i][2] == (int)pixel[2]){
         objetoSeleccionado = i;
         parar = true;
      }

   // cout << objetoSeleccionado << endl;
   //Establecemos el objeto a dibujar de amarillo.
   if(objetoSeleccionado != -1)
      if( pintarAmarillo[objetoSeleccionado] ) //ya estaba pintado de amarillo
         pintarAmarillo[objetoSeleccionado] = false;
      else
         pintarAmarillo[objetoSeleccionado] = true;
   
   
   
   glEnable(GL_DITHER);
   //LLamamos al dibujar para poner el objeto seleccionado del nuevo color
   dibujarSeleccion();
   //Volvemos a redibujar la escena
   //glutPostRedisplay();

   //objetoSeleccionado = -1;

         

}