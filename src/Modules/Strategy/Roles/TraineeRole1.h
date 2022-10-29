#ifndef RINO_PLAYER_H
#define RINO_PLAYER_H

#include "Role.h"

using namespace std;

class TraineeRole1 : public Role
{

private:
    bool onStart;
    int variavelQualquer;
    static int timeH;     // variavel de controle para fazer o robo manter a cabeça reta
    static int timeLow;   // variavel de controle para fazer o robo abaixar a cabeça
    static int timeFound; // variavel de controle para fazer o robo falar que a bola foi encontrada
    static int timeSp;    // variavel de controle para fazer o robo falar que a bola foi avistada
    static int timeSay;   // variavel de controle para fazer o robo falar que está procurando a bola
    // bool spinL = false; //girou para a esquerda
    // bool spinR = false; //girou para a direita

public:
    TraineeRole1(SpellBook *spellBook);
    ~TraineeRole1();
    void Tick(float ellapsedTime, const SensorValues &);
};
#endif
