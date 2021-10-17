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
#include <Arduino.h>
#include <Adafruit_TinyUSB.h> // for Serial


#undef min // vaya tela, están definidos en bluefruit.h y  !
#undef max // colisionan con los de la biblioteca estándar

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  PuertoSerie elPuerto ( /* velocidad = */ 9600 ); // 115200 o 9600 o ...

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

  Medidor elMedidor(&Serial1);

}; // namespace





// --------------------------------------------------------------
// --------------------------------------------------------------
void inicializarPlaquita () {

  Serial1.begin(9600);

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

  // 
  // 
  // 
  elMedidor.iniciarMedicion('\r');

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

  // 
  // mido y publico
  // 
  int valorConcentracion = elMedidor.getConcentracionGas();
  int intervaloEmision = 1000;

  elPuerto.escribir( "\n---- Envio C02: empieza \n" );
  elPuerto.escribir( valorConcentracion );
  elPublicador.publicarConcentracion( valorConcentracion,
              cont,
              intervaloEmision // intervalo de emisión
              );

  elPuerto.escribir( "\n---- Envio C02: TERMINA \n" );

  // 
  // mido y publico
  // 
  int valorTemperatura = elMedidor.getTemperatura();

  elPuerto.escribir( "\n---- Envio Temperatura: empieza \n" );
  elPuerto.escribir( valorTemperatura );
  elPublicador.publicarTemperatura( valorTemperatura, 
                  cont,
                  intervaloEmision // intervalo de emisión
                  );
  elPuerto.escribir( "\n---- Envio Temperatura: TERMINA \n" );
  
  int valorRH = elMedidor.getRH();

  elPuerto.escribir( "\n---- Envio Humedad Relativa: empieza \n" );
  elPuerto.escribir( valorRH );
  elPublicador.publicarRH( valorRH, 
                  cont,
                  intervaloEmision // intervalo de emisión
                  );
  elPuerto.escribir( "\n---- Envio Humedad Relativa: TERMINA \n" );

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
