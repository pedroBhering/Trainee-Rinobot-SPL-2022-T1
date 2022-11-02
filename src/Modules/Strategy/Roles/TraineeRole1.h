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





    int variavelQualquer;
    int timeH;     // variavel de controle para fazer o robo manter a cabeça reta
    int timeLow;   // variavel de controle para fazer o robo abaixar a cabeça
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
