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
    int time;
    bool procurou;
    bool rodouAux;
    float ballAngle;
    bool findAngle;
    bool headLowHead;
    int timeLowHead;
    bool rodando;
    int back;
    int timeAux;
    bool close;

    void lookingForTheBall();
    void spinBody(float spinAngle);
    void turnBack();
    void headLH();
    void bodyTurnBack();

public:
    TraineeRole1(SpellBook *spellBook);
    ~TraineeRole1();
    void Tick(float ellapsedTime, const SensorValues &);
};
#endif