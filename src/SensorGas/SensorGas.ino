// -*-c++-*-

// --------------------------------------------------------------
//
// Aitor Benítez Estruch
// 2021/10/05
//
// Descripción:
// Adapación del código original a las necesidades reales de este proyecto.
//
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython
// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------

#include <bluefruit.h>

#undef min // vaya tela, están definidos en bluefruit.h y  !
#undef max // colisionan con los de la biblioteca estándar

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ...

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"


// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  Publicador elPublicador;

  Medidor elMedidor;

}; // namespace





// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarPlaquita () {

  // de momento nada

} // ()

// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {

  // Método para que mientras no se habra el puerto serie no se acaba de completar el setup
  // ni se inicia el envío de beacons.
  // No es útil en el proyecto, no dispondremos de la información en el puerto serie!!
  //Globales::elPuerto.esperarDisponible();

  // 
  // 
  // 
  inicializarPlaquita();

  // Suspend Loop() to save power
  // suspendLoop();

  // 
  // 
  // 
  Globales::elPublicador.encenderEmisora();

  // Globales::elPublicador.laEmisora.pruebaEmision();
  
  // 
  // 
  // 
  Globales::elMedidor.iniciarMedidor();

  // 
  // 
  // 
  delay( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()



// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
};

// ..............................................................
// ..............................................................
void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

  // 
  // mido y publico
  // 
  int valorCO2 = elMedidor.medirCO2();
  int intervaloEmision = 1000;

  elPuerto.escribir( "\n---- Envio C02: empieza \n" );
  elPublicador.publicarCO2( valorCO2,
              cont,
              intervaloEmision // intervalo de emisión
              );

  elPuerto.escribir( "\n---- Envio C02: TERMINA \n" );

  // 
  // mido y publico
  // 
  int valorTemperatura = elMedidor.medirTemperatura();

  elPuerto.escribir( "\n---- Envio Temperatura: empieza \n" );
  elPublicador.publicarTemperatura( valorTemperatura, 
                  cont,
                  intervaloEmision // intervalo de emisión
                  );
elPuerto.escribir( "\n---- Envio Temperatura: TERMINA \n" );
  
  
  /*// 
  // prueba para emitir un iBeacon y poner
  // en la carga (21 bytes = uuid 16 major 2 minor 2 txPower 1 )
  // lo que queramos (sin seguir dicho formato)
  // 
  // Al terminar la prueba hay que hacer Publicador::laEmisora privado
  // 
  char datos[21] = {
  'H', 'o', 'l', 'a',
  'H', 'o', 'l', 'a',
  'H', 'o', 'l', 'a',
  'H', 'o', 'l', 'a',
  'H', 'o', 'l', 'a',
  'H'
  };

  // elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 );
  elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( "MolaMolaMolaMolaMolaM", 21 );*/

  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  elPublicador.laEmisora.detenerAnuncio();
  delay( 10000 );
  // 
  // 
  // 
  
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
