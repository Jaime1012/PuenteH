/*
   PuenteH - Library for controlling dual H-Bridge motor drivers
   Created by Rafa Gomez, 2014
   Licensed under GPL v3
   */
 
#include "PuenteH.h"
 
PuenteH::PuenteH(int pinM1PWM, int pinM1DIR, int pinM2PWM, int pinM2DIR, int pinENABLE) // Constructor para puente H basado en IRF3205
{
    _motor1 = new MotorCtrl(pinM1PWM, pinM1DIR);
    _motor2 = new MotorCtrl(pinM2PWM, pinM2DIR);
 
    _pinENABLE = pinENABLE;
 
    _modoActual = MODO_STOP;
}
 
PuenteH::~PuenteH()
{
    delete _motor1;
    delete _motor2;
}
 
void PuenteH::initMotors()  // Inicializa motores
{
    pinMode(_pinENABLE, OUTPUT);
    digitalWrite(_pinENABLE, LOW);
 
    delay(500); // tiempo de espera para que se estabilice el driver
 
    digitalWrite(_pinENABLE, HIGH);
 
    _motor1->initMotor();
    _motor2->initMotor();
}
 
void PuenteH::turnLeft(int speed)
{
    setDirSpeed(MODO_GIRO_IZQUIERDA, speed);
}
 
void PuenteH::turnRight(int speed)
{
    setDirSpeed(MODO_GIRO_DERECHA, speed);
}
 
void PuenteH::goForward(int speed)
{
    setDirSpeed(MODO_AVANZA, speed);
}
 
void PuenteH::goBackward(int speed)
{
    setDirSpeed(MODO_RETROCEDE, speed);
}
 
void PuenteH::stop()
{
    if( _modoActual != MODO_STOP )
    {
        _motor1->stop();
        _motor2->stop();
        _modoActual = MODO_STOP;
    }
}
 
void PuenteH::setDirSpeed(modo modo_candidato, int speed)
{
    if( modo_candidato != _modoActual ) // cambia el modo de desplazamiento
    {
        _motor1->stop();
        _motor2->stop();
 
        switch(modo_candidato)
        {
            case MODO_AVANZA:
                _motor1->setDirection(MotorCtrl::AVANZA);
                _motor2->setDirection(MotorCtrl::AVANZA);
                break;
            case MODO_RETROCEDE:
                _motor1->setDirection(MotorCtrl::RETROCEDE);
                _motor2->setDirection(MotorCtrl::RETROCEDE);
                break;
            case MODO_GIRO_IZQUIERDA:
                _motor1->setDirection(MotorCtrl::RETROCEDE);
                _motor2->setDirection(MotorCtrl::AVANZA);
                break;
            case MODO_GIRO_DERECHA:
                _motor1->setDirection(MotorCtrl::AVANZA);
                _motor2->setDirection(MotorCtrl::RETROCEDE);
                break;
            default:
                // do nothing
                break;
        }
 
        _modoActual = modo_candidato;
    }
 
    _motor1->setSpeed(speed);
    _motor2->setSpeed(speed);
}
 
void PuenteH::correctToLeft()
{
    int offsetM1 = _motor1->getOffset();
    int offsetM2 = _motor2->getOffset();
 
    if( offsetM1 >= 0 && offsetM2 == 0)
    {
        offsetM1++;
    }
    else if( offsetM1 == 0 && offsetM2 > 0)
    {
        offsetM2--;
    }
 
    _motor1->setOffset(offsetM1);
    _motor2->setOffset(offsetM2);
}
 
void PuenteH::correctToRight()
{
    int offsetM1 = _motor1->getOffset();
    int offsetM2 = _motor2->getOffset();
 
    if( offsetM2 >= 0 && offsetM1 == 0)
    {
        offsetM2++;
    }
    else if( offsetM2 == 0 && offsetM1 > 0)
    {
        offsetM1--;
    }
 
    _motor1->setOffset(offsetM1);
    _motor2->setOffset(offsetM2);
}
