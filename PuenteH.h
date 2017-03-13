/*
   PuenteH.h - Library for controlling dual H-Bridge motor drivers
   Created by Rafa Gomez, 2014
   Licensed under GPL v3
   */
#ifndef PuenteH_h
#define PuenteH_h
 
#include "Arduino.h"
#include "MotorCtrl.h"
 
class PuenteH
{
    public:
        PuenteH(int pinM1PWM, int pinM1DIR, int pinM2PWM, int pinM2DIR, int pinENABLE);
        ~PuenteH();
        void initMotors();
        void turnLeft(int speed);
        void turnRight(int speed);
        void goForward(int speed);
        void goBackward(int speed);
        void stop();
        void correctToLeft();
        void correctToRight();
 
    private:
        enum modo {MODO_STOP, MODO_AVANZA, MODO_RETROCEDE, MODO_GIRO_IZQUIERDA, MODO_GIRO_DERECHA};
 
        MotorCtrl *_motor1;
        MotorCtrl *_motor2;
 
        void setDirSpeed(modo candidato, int speed);
 
        int _pinENABLE;
        modo _modoActual;
};
 
#endif
