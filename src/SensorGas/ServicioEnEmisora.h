// -*- mode: c++ -*-

// ----------------------------------------------------------
// Aitor Benítez Estruch
// 2021/10/05
// ----------------------------------------------------------
#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
// ----------------------------------------------------
#include <vector>
#include "Caracteristica.h"

// ----------------------------------------------------
// alReves() utilidad
// pone al revés el contenido de una array en el mismo array
// ----------------------------------------------------
template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for( int i=0; i < n/2; i++ ) {
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} // ()


// ----------------------------------------------------------
// ----------------------------------------------------------
class ServicioEnEmisora {

public:

  // --------------------------------------------------------
  // --------------------------------------------------------
  
private:
  
  uint8_t uuidServicio[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
	// least signficant byte, el primero
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };

  //
  //
  //
  BLEService elServicio;

  //
  //
  //
  std::vector< Caracteristica * > lasCaracteristicas;

public:
  
  // .........................................................
  // .........................................................
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
  {
	
  } // ()
  
  // .........................................................
  // .........................................................
  void escribeUUID() {
    	Serial.println ( "**********" );
    	for (int i=0; i<= 15; i++) {
    	  Serial.print( (char) uuidServicio[i] );
    	}
    	Serial.println ( "\n**********" );
  } // ()

  // .........................................................
  // .........................................................
  void anyadirCaracteristica( Caracteristica & car ) {
	    (*this).lasCaracteristicas.push_back( & car );
  } // ()

  // .........................................................
  // .........................................................
  void activarServicio( ) {
	// entiendo que al llegar aquí ya ha sido configurado
	// todo: características y servicio

    	err_t error = (*this).elServicio.begin();
    	Serial.print( " (*this).elServicio.begin(); error = " );
    	Serial.println( error );
    
    	for( auto pCar : (*this).lasCaracteristicas ) {
    	  (*pCar).activar();
    	} // for

  } // ()

  // .........................................................
  // .........................................................
  operator BLEService& () {
	    // "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService
	    return elServicio;
  } // ()
	
}; // class

#endif

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
