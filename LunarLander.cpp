#include <iostream>
#include <iomanip>
#include <math.h>
#include "LunarLander.hpp"
#include <time.h>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;

Vect operator+(Vect a, Vect b)
{
    Vect c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Lander::Lander(Vect iG, double iangle, Vect ivelocity, double ifuel,
               Vect iposition, double imax, bool icrashed, bool ilanded) :
gravity(iG), angle(iangle), velocity (ivelocity), fuel(ifuel), position(iposition),
crashed(icrashed), landed(ilanded), maxTouchdownSpeed(imax)
{
    thrust.x = 0.0;
    thrust.y = 0.0;
    
}
Vect Lander::getVelocity()
{
    return velocity;
}
double Lander::getFuel()
{
    return fuel;
}
Vect Lander::getPosition()
{
    return position;
}
double Lander::getMTS()
{
    return maxTouchdownSpeed;
}
bool Lander::getCrashed()
{
    return crashed;
}
bool Lander::getLanded()
{
    return landed;
}
double Lander::getAngle()
{
    return angle;
}
void Lander::rotateLeft(double rotateAngle)
{
    if (rotateAngle < 0)
        rotateAngle *= -1;
    if (rotatedThisTurn > PI / 12)
        rotatedThisTurn = PI / 12;
    rotatedThisTurn -= rotateAngle;
    
}
void Lander::rotateRight(double rotateAngle)
{
    if (rotateAngle < 0)
        rotateAngle *= -1;
    if (rotatedThisTurn < -PI / 12)
        rotatedThisTurn = -PI / 12;
    rotatedThisTurn -= rotateAngle;
    
}
void Lander::burn(double fuelAmount)
{
    fuelBurnedThisTurn += fuelAmount;
    if (fuelBurnedThisTurn > 50)
        fuelBurnedThisTurn = 50;
}
void Lander::timeUpdate()
{
    if (crashed)
        return;
    angle += rotatedThisTurn;
    if (angle > 0.0 )
        angle -= 2 * PI;
    if (angle < 0.0 )
        angle += 2 * PI;
    if (fuelBurnedThisTurn > fuel)
        fuelBurnedThisTurn = fuel;
    fuel -= fuelBurnedThisTurn;
    thrust.x = cos(angle)*fuelBurnedThisTurn;
    thrust.y = sin(angle)*fuelBurnedThisTurn;
    velocity = velocity + thrust + gravity;
    position = position + velocity;
    rotatedThisTurn = 0.0;
    fuelBurnedThisTurn = 0.0;
    if (position.y <= 0)
    {
        if ((velocity.x * velocity.x) + (velocity.y * velocity.y) >= maxTouchdownSpeed)
        {
            crashed = true;
        }
        else
        {
            landed = true;
        }
        if (crashed || landed)
        {
            velocity.x = 0;
            velocity.y = 0;
            position.y = 0;
        }
    }
    
}
