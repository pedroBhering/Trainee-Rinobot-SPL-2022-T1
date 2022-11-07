#include "TraineeRole1.h"
#include "Core/Utils/Math.h"
#include "Core/Utils/RelativeCoord.h"
#include "Core/Utils/RobotDefs.h"
#include "Core/Utils/CartesianCoord.h"

TraineeRole1::TraineeRole1(SpellBook *spellBook) : Role(spellBook)
{

    ballSpotted = false;
    timeBall = 0;
    ballHere = false;
    foundBall = false;
    time = 0;

    timeLow = 0;
    timeHigh = 0;
    timeLeft = 0;
    timeRight = 0;

    headHigh = false;
    headLow = false;
    headLeft = false;
    headRight = false;

    ballAngle = 0;
    findAngle = false;

    ballDistActual = 0;
    dist = false;
    h = 0.573;
    ballDistanceDif = 0;
    ballD = 0;
    back = 0;
    timeAux = 0;
    close = false;
    timeBallSave = 0;

    onStart = false;
}
TraineeRole1::~TraineeRole1()
{
}

void TraineeRole1::bodyTurnBack()
{
    if (back < 150)
    {
        spellBook->motion.Vth = Deg2Rad(-10.0f);
        back++;
    }
    else
    {
        spellBook->motion.Vth = Deg2Rad(0.0f);
        back = 0;
        timeLeft = 0;
        timeLow = 0;
        timeHigh = 0;
        timeRight = 0;
        headLeft = false;
        headLow = false;
        headHigh = false;
        headRight = false;
    }
}

void TraineeRole1::spinBody(float spinAngle)
{
    cout << "Angulo da bola: " << spinAngle << endl;
    if (spinAngle >= 10 || spinAngle <= -10) // verifica se o angulo em relacao a bola esta para esquerda ou direita e
    {
        if (spinAngle > 0)
            spellBook->motion.Vth = Deg2Rad(-10.0f);
        else
            spellBook->motion.Vth = Deg2Rad(10.0f);
    }
    else
        spellBook->motion.Vth = Deg2Rad(0.0f);
}

void TraineeRole1::lookingForTheBall()
{
    spellBook->motion.Vx = 0;
    if (timeLeft < 50 && !headLeft)
    {
        timeLeft++;
        spellBook->motion.Vth = DEG2RAD(20.0f);
        cout << "Girou para Esquerda" << endl;
    }
    else
    {
        headLeft = true;
        if (timeLow < 50 && !headLow && headLeft)
        {
            timeLow++;
            spellBook->motion.HeadPitch = DEG2RAD(30.0f);
            cout << "Girou para baixo" << endl;
        }
        else
        {
            headLow = true;
            if (timeRight < 100 && !headRight && headLow)
            {
                timeRight++;
                spellBook->motion.Vth = DEG2RAD(-20.0f);
                cout << "Girou para a direita" << endl;
            }
            else
            {
                headRight = true;
                if (timeHigh < 50 && !headHigh && headRight)
                {
                    timeHigh++;
                    spellBook->motion.HeadPitch = DEG2RAD(0.0f);
                    cout << "Girou para cima" << endl;
                }
                else
                {
                    headHigh = true;
                    spellBook->motion.HeadYaw = DEG2RAD(0.0f);
                    if (headLow && headRight && headLeft && headHigh)
                    {
                        bodyTurnBack();
                    }
                }
            }
        }
    }
}

void TraineeRole1::Tick(float ellapsedTime, const SensorValues &sensor)
{
    spellBook->strategy.MoveHead = false;
    spellBook->motion.HeadYaw = 0;
    spellBook->motion.HeadSpeedYaw = 0.2f;
    spellBook->motion.HeadSpeedPitch = 0.2f;

    if ((spellBook->strategy.GameState == STATE_READY || spellBook->strategy.GameState == STATE_PLAYING) && !onStart)
    {
        if (spellBook->perception.vision.localization.Enabled)
        {
            spellBook->strategy.WalkForward = true;
            spellBook->strategy.TargetX = -1.0f;
            spellBook->strategy.TargetY = 0.0f;
            spellBook->strategy.TargetTheta = 0;

            CartesianCoord current(spellBook->perception.vision.localization.X, spellBook->perception.vision.localization.Y);
            CartesianCoord desired(spellBook->strategy.TargetX, spellBook->strategy.TargetY);
            if (current.distance(desired) < 0.2f)
            {
                spellBook->strategy.WalkForward = false;
                onStart = true;
            }
        }
        else
        {
            onStart = true;
        }
    }
    if (spellBook->strategy.GameState == STATE_PLAYING && onStart)
    {
        if (spellBook->perception.vision.ball.BallDetected)
        {
            spellBook->motion.HeadPitch = Deg2Rad(30.0f);
            // spellBook->motion.HeadYaw = DEG2RAD(0.0f);
            cout << "Viu a bola" << endl;

            if (!foundBall)
            {
                cout << "viu a bola 2 " << endl;
                SAY("I found the ball");
                foundBall = true;
            }

            ballAngle = spellBook->perception.vision.ball.BallYaw;
            spinBody(ballAngle);
            ballSpotted = true;

            if (!dist)
            {
                ballDistActual = spellBook->perception.vision.ball.BallDistance; // uma vez
                timeAux = 0;
                dist = true;
                close = false;
                ballHere = false;
                ballDistanceDif = spellBook->perception.vision.ball.BallDistance;
                if (ballDistanceDif <= 0.25)
                {
                    timeBallSave = 0;
                    close = true;
                    spellBook->motion.Vx = 0;
                    if (!ballHere)
                    {
                        SAY("The ball is here");
                        ballHere = true;
                    }
                }
            }

            else
            {
                cout << "Dist percorrida 1: " << 0.15 * timeAux << endl;
                cout << "Dist encontrada 1: " << ballDistActual << endl;
                ballDistanceDif = spellBook->perception.vision.ball.BallDistance;
                cout << "Dist na hora: " << ballDistanceDif << endl;
                if ((ballDistActual > (0.15 * timeAux + 0.2)) && ballDistanceDif > 0.2)
                {
                    cout << "Indo ate a bola" << endl;
                }
                else
                {
                    ballAngle = spellBook->perception.vision.ball.BallYaw;
                    spinBody(ballAngle);
                    dist = false;
                    timeBallSave = 0;
                    close = true;
                    spellBook->motion.Vx = 0;
                    if (!ballHere)
                    {
                        SAY("The ball is here");
                        ballHere = true;
                    }
                }
            }
        }
        if (ballSpotted)
        {
            timeLow = 0;
            timeHigh = 0;
            timeLeft = 0;
            timeRight = 0;
            headLow = false;
            headHigh = false;
            headLeft = false;
            headRight = false;
            cout << "Dist percorrida 2: " << 0.15 * timeAux << endl;
            cout << "Dist encontrada 2: " << ballDistActual << endl;
            spellBook->motion.Vth = Deg2Rad(0.0f);
            timeAux += ellapsedTime;
            cout << "Tempo decorrido: " << timeAux << endl;
            if ((ballDistActual > (0.15 * timeAux + 0.2)))
            {
                if (!close)
                {
                    cout << "Indo ate a bola" << endl;
                    spellBook->motion.Vx = 0.15;
                }
                else
                {
                    spellBook->motion.Vx = 0;
                    timeBallSave += ellapsedTime;
                    cout << "Tempo sem ver a bola: " << timeBallSave << endl;
                    if (timeBallSave < 5)
                    {
                        cout << "Perto da bola: " << ballD << endl;
                        if (!ballHere)
                        {
                            SAY("The ball is here");
                            ballHere = true;
                        }
                    }
                    else
                    {
                        spellBook->motion.Vth = 0;
                        spellBook->motion.HeadPitch = Deg2Rad(0.0f);
                        ballSpotted = false; // logo faz procurar a bola novamente
                        dist = false;
                    }
                }
            }
            else if (close)
            {
                spellBook->motion.Vx = 0;
                timeBallSave += ellapsedTime;
                cout << "Tempo sem ver a bola: " << timeBallSave << endl;
                if (timeBallSave < 5)
                {
                    cout << "Perto da bola: " << ballD << endl;
                    if (!ballHere)
                    {
                        SAY("The ball is here");
                        ballHere = true;
                    }
                }
                else
                {
                    spellBook->motion.Vth = 0;
                    spellBook->motion.HeadPitch = Deg2Rad(0.0f);
                    ballSpotted = false; // logo faz procurar a bola novamente
                    dist = false;
                }
            }
            else
            {
                spellBook->motion.Vth = 0;

                spellBook->motion.HeadPitch = Deg2Rad(0.0f);
                spellBook->motion.Vx = 0;
                ballSpotted = false; // logo faz procurar a bola novamente
                dist = false;
            }
        }

        else
        {
            lookingForTheBall();
            ballHere = false;
            foundBall = false;
            findAngle = false;
            dist = false;
            // SAY("Looking");
        }
    }
}
