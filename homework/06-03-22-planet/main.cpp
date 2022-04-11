#include <iostream>
#include <cstring>
using namespace std;
//============================================================================
// Homework on basic class
//============================================================================

class Planet
{
    // TODO add fields
private:
    char planetName[50];
    double distanceToSun;
    double diameter;
    double mass;

public:
    Planet(const char *name, double distanceToSun, double diameter, double weight);
    ~Planet();

    // TODO add getters and setters

    void print();
    double getSecondsToSun();
};

int main()
{

    // Get the name from the console
    // Then create an object of type Planet and test all the methods.

    char planetName[50];
    double distanceToSun, diameter, mass;
    cout << "Enter planet name: ";
    cin >> planetName;
    cout << "Distance to Sun: ";
    cin >> distanceToSun;
    cout << "Diameter: ";
    cin >> diameter;
    cout << "Mass: ";
    cin >> mass;
    Planet planet(planetName, distanceToSun, diameter, mass);
    planet.print();
    cout << "Seconds to the Sun: " << planet.getSecondsToSun() << " seconds." << endl;

    return 0;
}

Planet::Planet(const char *planetName, double distanceToSun, double diameter, double mass)
{
    strcpy(this->planetName, planetName);
    this->distanceToSun = distanceToSun > 0 ? distanceToSun : 0;
    this->diameter = diameter > 0 ? diameter : 0;
    this->mass = mass > 0 ? mass : 0;
}

Planet::~Planet()
{
}

void Planet::print()
{
    cout << endl;
    cout << "Planet: " << this->planetName << endl;
    cout << "Distance to Sun: " << this->distanceToSun << endl;
    cout << "Diameter: " << this->diameter << endl;
    cout << "Mass: " << this->mass << endl;
    cout << endl;
}

double Planet::getSecondsToSun()
{
    return this->distanceToSun / 299792;
}