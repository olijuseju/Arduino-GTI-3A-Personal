// -*- mode: c++ -*-

// --------------------------------------------------------------
/**
 * @author Jose Julio Peñaranda
 * 2021-10-14
 */
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
  "josej", //  nombre emisora
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
  HUMEDAD = 10,
  CO2 = 11,
  TEMPERATURA = 12,
  RUIDO = 13
  };

  // ............................................................
  // ............................................................
  Publicador( ) {
  // ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
  // Pondremos un método para llamarlo desde el setup() más tarde
  } // ()

  // ............................................................
  // ............................................................
  /*
   * encendemos la emisora
   */
  void encenderEmisora() {
  (*this).laEmisora.encenderEmisora();
  } // ()

  // ............................................................
  // ............................................................
  /*
   * Publicamos los valores de CO2
   * 
   * @param {int} valorCO2 - Valor CO2 a publicar
   * 
   * @param {uint} contador - Numero natural que representa al contador
   * @param {long} tiempoEspera - Valor del tiempo de espera
   */
  void publicarCO2( int16_t valorCO2, uint8_t contador,
          long tiempoEspera ) {

  //
  // 1. empezamos anuncio
  //
  uint16_t major = (MedicionesID::CO2 << 8) + contador;
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
                      major,
                      valorCO2, // minor
                      (*this).RSSI // rssi
                  );

  /*
  Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
  Globales::elPuerto.escribir( valorCO2 );
  Globales::elPuerto.escribir( "   contador=" );
  Globales::elPuerto.escribir( contador );
  Globales::elPuerto.escribir( "   todo="  );
  Globales::elPuerto.escribir( major );
  Globales::elPuerto.escribir( "\n" );
  */

  //
  // 2. esperamos el tiempo que nos digan
  //
  esperar( tiempoEspera );

  //
  // 3. paramos anuncio
  //
  (*this).laEmisora.detenerAnuncio();
  } // ()

  // ............................................................
  // ............................................................
  
  /*
   * Publicamos los valores de temperatura
   * 
   * @param {int} valorTemperatura - Valor temperatura a publicar
   * 
   * @param {uint} contador - Numero natural que representa al contador
   * @param {long} tiempoEspera - Valor del tiempo de espera
   */
  void publicarTemperatura( int16_t valorTemperatura,
              uint8_t contador, long tiempoEspera ) {

  uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
                      major,
                      valorTemperatura, // minor
                      (*this).RSSI // rssi
                  );
  esperar( tiempoEspera );

  (*this).laEmisora.detenerAnuncio();
  } // ()


  // ............................................................
  // ............................................................
  
  /*
   * Publicamos los valores de humedad
   * 
   * @param {int} valorHumedad - Valor humedad a publicar
   * 
   * @param {uint} contador - Numero natural que representa al contador
   * @param {long} tiempoEspera - Valor del tiempo de espera
   */
  void publicarHumedad( int16_t valorHumedad,
              uint8_t contador, long tiempoEspera ) {

  uint16_t major = (MedicionesID::HUMEDAD << 8) + contador;
  (*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
                      major,
                      valorHumedad, // minor
                      (*this).RSSI // rssi
                  );
  esperar( tiempoEspera );

  (*this).laEmisora.detenerAnuncio();
  } // ()
  
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
