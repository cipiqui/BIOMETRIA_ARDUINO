
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
/*
AUTOR: CARLOS IPIÉNS QUINTANAR
NOMBRE DEL FICHERO: EnviarBeacon.ino
DESCRIPCIÓN: ESTE PROGRAMA LANZARÁ BEACONS QUE SERÁN RECOGIDOS DESDE LA APLICACIÓN MOVIL
FECHA: JUEVES 22 DE SEPTIEMBRE DE 2022
*/
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
// Librería de adafruit
#include <bluefruit.h> 
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------

void setup() {
 
  // Inicializo el puerto serie a 115.200 baudios 
  Serial.begin(115200); 

  // Inicializo el modulo de Bluefruit
  Bluefruit.begin();

  // Le pongo un nombre al dispositivo y lo reconozco para añadirlo a su información ("nombre del beacon")
  Bluefruit.setName("Beacon_Carlos");
  Bluefruit.ScanResponse.addName();

  startAdvertising();

}

//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
// Función de configuración del Beacon (Introducir UUID y los parámetros necesarios)

void startAdvertising(){

  // En un principio no se ejecuta, se llamará después cuando se quiera utilizar
  Bluefruit.Advertising.stop();

  // Se añade el parámetro TxPower referente al consumo y se añaden los paquetes propios del beacon
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  // Incluimos el nombre del beacon
  Bluefruit.Advertising.addName();

  // Configuramos el UUID del beacon
  uint8_t beaconUUID[16] = {'C', 'A', 'R', 'L', 'O', 'S', '-', 'B','E', 'A', 'C', 'O', 'N', '-', '3', 'A' };
  BLEBeacon elBeacon( beaconUUID, 23, 03, 73 ); // Beacon , Major, Minor, unidad
  elBeacon.setManufacturer( 0x004c ); // Fabricado por Apple
  Bluefruit.Advertising.setBeacon( elBeacon );
  

  // Inicio la función
  Bluefruit.Advertising.start(0);

}

//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
// Se crea la variable contador fuera del Loop para que se pueda incrementar el valor

namespace Loop {
  int NumeroBeacon = 0;
};

//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------

void loop() {
 
 using namespace Loop;

  NumeroBeacon++;

  delay(3000);

  Serial.print( "Nº de Beacon enviado: " );
  Serial.println( NumeroBeacon );

}

//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------