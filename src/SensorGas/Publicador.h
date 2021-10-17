// -*- mode: c++ -*-

// --------------------------------------------------------------
// Jordi Bataller i Mascarell
// --------------------------------------------------------------

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

// --------------------------------------------------------------
// --------------------------------------------------------------
class Publicador {

  // ............................................................
  // ............................................................
private:

  uint8_t beaconUUID[16] = { 
	'E', 'P', 'S', 'G', '-', 'G', 'T', 'I', 
	'-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
	};

  // ............................................................
  // ............................................................
public:
  EmisoraBLE laEmisora {
	  "GTI-3A-ABENEST", //  nombre emisora
	  0x004c, // fabricanteID (Apple)
	  4 // txPower
  };
  
  const int RSSI = -53; // por poner algo, de momento no lo uso

  // ............................................................
  // ............................................................
public:

  // ............................................................
  // ............................................................
  enum MedicionesID  {
	CONCENTRACION = 11,
	TEMPERATURA = 12,
	HUMEDAD = 13
  };

  // ............................................................
  // ............................................................
  Publicador( ) {
	// ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
	// Pondremos un método para llamarlo desde el setup() más tarde
  } // ()

  // ............................................................
  // ............................................................
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  } // ()

  // ............................................................
  // ............................................................
  void publicarConcentracion( int16_t valorConcentracion, uint8_t contador,
					long tiempoEspera ) {

    	//
    	// 1. empezamos anuncio
      // operador << desplaza los bits de la variable CO2 8 posiciones a la izquierda para indicar el tipo de medida que se envía (11 = CO2)
    	//
    	uint16_t major = (MedicionesID::CONCENTRACION << 8);
    	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
    											major,
    											valorConcentracion, // minor
    											(*this).RSSI // rssi
    									);
    
    	//
    	// 2. esperamos el tiempo que nos digan
    	//
    	delay( tiempoEspera );
    
    	//
    	// 3. paramos anuncio
    	//
    	(*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  // ............................................................
  void publicarTemperatura( int16_t valorTemperatura,
							uint8_t contador, long tiempoEspera ) {

      //
      // 1. empezamos anuncio 
      // operador << desplaza los bits de la variable TEMPERATURA 8 posiciones a la izquierda para indicar el tipo de medida que se envía (12 = TEMPERATURA)
    	uint16_t major = (MedicionesID::TEMPERATURA << 8);
      
    	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
    											major,
    											valorTemperatura, // minor
    											(*this).RSSI // rssi
    									);

                      
      //
      // 2. esperamos el tiempo que nos digan
      //           
    	delay( tiempoEspera );

      //
      // 3. paramos anuncio
      //
    	(*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  // ............................................................
  void publicarRH( int16_t valorRH, uint8_t contador,
          long tiempoEspera ) {

      //
      // 1. empezamos anuncio
      // operador << desplaza los bits de la variable CO2 8 posiciones a la izquierda para indicar el tipo de medida que se envía (11 = CO2)
      //
      uint16_t major = (MedicionesID::HUMEDAD << 8);
      (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
                          major,
                          valorRH, // minor
                          (*this).RSSI // rssi
                      );
    
      //
      // 2. esperamos el tiempo que nos digan
      //
      delay( tiempoEspera );
    
      //
      // 3. paramos anuncio
      //
      (*this).laEmisora.detenerAnuncio();
  } // ()
	
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
