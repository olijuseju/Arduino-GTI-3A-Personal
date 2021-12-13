// -*-c++-*-


//TEST

// --------------------------------------------------------------
/**
 * @author Jose Julio Peñaranda
 * 2021-10-14
 */
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

#undef min // vaya tela, están definidos en bluefruit.h y  !
#undef max // colisionan con los de la biblioteca estándar

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 9600 ); // 115200 o 9600 o ...

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
};

// ----------------------------------------------------------
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

  delay( 1000 );

  
  // 
  // 
  // 
  Globales::elMedidor.iniciarMedidor();

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// --------------------------------------------------------------
/**
 * Hacemos parpadear el led
 */
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 1000 ); //  100 apagado
} // ()

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

  elMedidor.realizarMedicion('\r');


  elPuerto.escribir( "---- TIPO DE DATO **** " );
  elPuerto.escribir( elMedidor.getTipoDeDato() );
  elPuerto.escribir( " **** TIPO DE DATO ---- " );

  // 
  // mido CO2
  // 

  uint16_t valorCO2 = elMedidor.medirCO2();
  elPuerto.escribir( "---- VALOR CO2 **** " );

  elPuerto.escribir( ((valorCO2*5000)/65535) );
  elPuerto.escribir( " **** VALOR CO2 ---- " );


  // 
  // mido Temperatura
  // 
  int valorTemperatura = elMedidor.medirTemperatura();
  elPuerto.escribir( "---- VALOR Temperatura **** " );

  elPuerto.escribir( valorTemperatura );
  elPuerto.escribir( " **** VALOR Temperatura ---- " );



  // 
  // mido Humedad
  // 
  int valorHumedad = elMedidor.medirHumedad();
  elPuerto.escribir( "---- VALOR Humedad **** " );

  elPuerto.escribir( valorHumedad );
  elPuerto.escribir( " **** VALOR Humedad ---- " );
  


  //
  // publico las 3 mediciones
  //
  elPublicador.publicarCO2( valorCO2,
              cont,
              1000 // intervalo de emisión
              );

  elPublicador.publicarTemperatura( valorTemperatura,
              cont,
              1000 // intervalo de emisión
              );


  elPublicador.publicarHumedad( valorHumedad,
              cont,
              1000 // intervalo de emisión
              );

  // elPublicador.laEmisora.detenerAnuncio();
  // 
  // 
  // 
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

  delay(2000);
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
