#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Point {
	double x, y;
};

void findIndexes(int , int , Point* , int* , int , double* , int* );

void DrawLine(sf::RenderWindow* , double , double , double , double );