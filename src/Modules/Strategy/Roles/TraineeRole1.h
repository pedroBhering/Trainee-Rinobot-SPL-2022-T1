#ifndef RINO_PLAYER_H
#define RINO_PLAYER_H

#include "Role.h"

using namespace std;

class TraineeRole1 : public Role
{

private:
    bool onStart;
    bool ballSpotted;
    int timeBall;
    bool ballHere;
    int gap;
    int timePitch;
    float angle;
    bool foundBall;
    bool para;
    bool dist;
    float ballDistActual;
    float ballDistPrevious;
    bool rodou;
    bool abaixouC;
    bool headHigh;
    bool headLow;
    bool headLeft;
    bool headRight;
    int andou;
    float h;
    float ballDistanceDif;
    float ballD;
    int timeLow;
    int timeHigh;
    int timeLeft;
    int timeRight;


    lookingForTheBall();





    int variavelQualquer;
    int timeH;     // variavel de controle para fazer o robo manter a cabeça reta
    int timeFound; // variavel de controle para fazer o robo falar que a bola foi encontrada
    int timeSp;    // variavel de controle para fazer o robo falar que a bola foi avistada
    int timeSay;   // variavel de controle para fazer o robo falar que está procurando a bola
    int timeL;
    int timeR;
    bool spinL; //girou para a esquerda
    bool spinR; //girou para a direita
    bool spinB;
    int degree;

public:
    TraineeRole1(SpellBook *spellBook);
    ~TraineeRole1();
    void Tick(float ellapsedTime, const SensorValues &);
};
#endif
