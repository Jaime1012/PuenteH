///
/// Ejemplo de control de Puente H
///
/// by RafaG
///
 
#include "PuenteH.h"
 
/// Definición de pines
///
// Motor derecho
const int PWMR = 5; // Pin PWM
const int DIRR = 2;
// Motor izquierdo
const int PWML = 6; // Pin PWM
const int DIRL = 3;
// Enable motores
const int ENA = 8;
///
/// Fin de definición de pines
 
/// Instancia a clase PuenteH
///
PuenteH puenteH(PWML, DIRL, PWMR, DIRR, ENA);
///
/// Fin de instancia a clase PuenteH
 
/// Funciones básicas
///
void setup() {
 puenteH.initMotors();
}
 
void loop() {
 puenteH.goForward(100);
 delay(1000);
 puenteH.goBackward(100);
 delay(1000);
 puenteH.turnLeft(100);
 delay(1000);
 puenteH.turnRight(100);
 delay(1000);
 puenteH.stop();
 delay(1000);
}
///
/// Fin funciones básicas
