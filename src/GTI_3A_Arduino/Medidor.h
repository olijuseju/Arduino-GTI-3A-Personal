// -*- mode: c++ -*-

// --------------------------------------------------------------
/**
 * @author Jose Julio Peñaranda
 * 2021-10-14
 */
// --------------------------------------------------------------

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------
class Medidor {

  // .....................................................
  // .....................................................
private:

    Stream *_mySerial;
    long sensorData[11]; //Datos de las medidas
    String informacionSensor[5]; //Datos sensor de la EEPROM
    
public:

  // .....................................................
  // constructores
  // .....................................................
    Medidor(Stream *mySerial) : _mySerial(mySerial) {    }
    Medidor(Stream &mySerial) : _mySerial(&mySerial) {    }
  // .....................................................
  // .....................................................
  /*
   * iniciarMedidor() <-
   * 
   * iniciarMedidor() inicializa el sensor y manda la parte de
   * de la información del sensor. Nos servirá para saber el tipo de medición. 
   *
   */
  void iniciarMedidor() {
      while (_mySerial->available()) _mySerial->read();
      _mySerial->flush();
      _mySerial->write('e');
    
      while (!_mySerial->available()) {}
    
      String data = _mySerial->readStringUntil('\n');
      while (!_mySerial->available()) {}
      for (int i = 15; i < 20; i++) {
        data = _mySerial->readStringUntil('\n');
        String subS1 = data.substring(0, data.indexOf('='));
        String subS2 = data.substring(data.indexOf('=') + 2);
        informacionSensor[i - 14] = subS2;
       
      }     
      while (_mySerial->available()) _mySerial->read();  
      
  } // ()

  // .....................................................
  // .....................................................

  /*
   * 
   * c: caracter -> iniciarMedicion() 
   * iniciarMedicion() se comunica con el serial mediante el carácter que recibe.
   * El carácter a enviar se obtiene del datasheet del sensor
   * 
   * @params c Caracter con la instrucción (descrito en el datasheet)
   * 
   */

  int realizarMedicion(char c)
    {
      delay(500);
      _mySerial->write(c);
      String datos;
      while (!_mySerial->available()) {}
      datos = _mySerial->readStringUntil('\n');
      for (int i = 0; i < 11; i++) {
        String subS = datos.substring(0, datos.indexOf(','));
        if (subS.length() == 0) return 0;
        sensorData[i] = subS.toInt();
        datos = datos.substring(datos.indexOf(',') + 2);
      }
      return 1;
    }



  // .....................................................
  // .....................................................
    /**
 * Medimos el CO2 con el sensor
 * 
 * @return {int} - Valor de CO2
 */
  uint16_t medirCO2() {
    uint16_t dato = sensorData[1];
    return round(dato);
  } // ()

  // .....................................................
  // .....................................................
 /**
 * Medimos la temperatura con el sensor
 * 
 * @return {int} - Valor de temperatura
 */
  int medirTemperatura() {
  return sensorData[2];
  } // ()

  // .....................................................
  // .....................................................
 /**
 * Medimos la humedad con el sensor
 * 
 * @return {int} - Valor de humedad
 */
  int medirHumedad() {
  return sensorData[3];
  } // ()

   /**
   * Obtenemos el tipo de dato
   * 
   * @return {String} - tipo de dato
   */
  String getTipoDeDato(){
    return informacionSensor[3];
  }
  
}; // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif
