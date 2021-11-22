// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO
// --------------------------------------------------------------
/**
 * @author Jose Julio Peñaranda
 * 2021-10-14
 */
// --------------------------------------------------------------

// ----------------------------------------------------------
// ----------------------------------------------------------
/**
 * Este metodo se encarga de hacer esperar al led un tiempo
 *
 *@param {N} tiempo - Valor de tiempo de espera.
 *
 *
 */
void esperar (long tiempo) {
  delay (tiempo);
}

// ----------------------------------------------------------
// ----------------------------------------------------------
class LED {
private:
  int numeroLED;
  bool encendido;
public:

  // .........................................................
  // .........................................................
  LED (int numero)
  : numeroLED (numero), encendido(false)
  {
  pinMode(numeroLED, OUTPUT);
  apagar ();
  }

  // .........................................................
  // .........................................................
    /*
   * Enciende la placa
   */
  void encender () {
  digitalWrite(numeroLED, HIGH); 
  encendido = true;
  }

  // .........................................................
  // .........................................................
  /*
   * Apaga la placa
   */
  void apagar () {
    digitalWrite(numeroLED, LOW);
    encendido = false;
  }

  // .........................................................
  // .........................................................
    /*
   * Apaga la placa si está encendida y viceversa
   */
  void alternar () {
  if (encendido) {
    apagar();
  } else {
    encender ();
  }
  } // ()

  // .........................................................
  // .........................................................
      /*
   * la placa se enciende durante un tiempo y luego se apaga
   *  *@param {N} tiempo - Valor de tiempo de espera.

   */
  void brillar (long tiempo) {
  encender ();
  esperar(tiempo); 
  apagar ();
  }
}; // class

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif
