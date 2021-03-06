// plane.cpp - the plane class

/***********************************************************
Copyright (c) 2013 Juho Rinta-Paavola

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Softaware is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***************************************************************/

/**** INCLUDES ****/

#include <iostream>
#include <cmath>
#include <random>
#include "main.h"
#include "plane.h"
#include "haversine.h"
#include "error.h"

using namespace std;

/**** GLOBAL VARIABLES ****/

extern const double pi;

/**** MEMBER FUNCTIONS ****/

plane::plane(int initialRange, double initialLatitude, double initialLongtitude, double initialMoney) {
  currentRange = maxTheoreticalRange = initialRange;
  currentLatitude = initialLatitude;
  currentLongtitude = initialLongtitude;
  currentMoney = initialMoney;

#if defined DEBUG
  cerr << "DEBUG: currentRange = maxTheoreticalRange = " << currentRange << " = " << maxTheoreticalRange << '\n';
  cerr << "DEBUG: currentLatitude = " << currentLatitude << '\n';
  cerr << "DEBUG: currentLongtitude = " << currentLongtitude << '\n';
#endif
}

void plane::move(double targetLatitude, double targetLongtitude) {
  //Fudge currentRange
  default_random_engine generator;
  uniform_real_distribution<double> distribution(0.95,1);
  currentRange *= distribution(generator); //Decrease remaining range by 0-5%

  double travelDistance = calculateDistance(currentLatitude, currentLongtitude, targetLatitude, targetLongtitude);

  if (currentRange - travelDistance >= 0) {
    currentRange -= travelDistance;
    currentLatitude = targetLatitude;
    currentLongtitude = targetLongtitude;
  }
  else throw ERROR_OUT_OF_RANGE;

#if defined DEBUG
  cerr << "DEBUG: currentRange = " << currentRange << '\n';
#endif
}

int plane::rangePercentage() {
#if defined DEBUG
  cerr << "DEBUG: currentRange, maxTheoreticalRange, percentage: " << currentRange << ',' << maxTheoreticalRange << ',' << currentRange*100/maxTheoreticalRange << '\n';
#endif
  return int(currentRange*100/maxTheoreticalRange);
}

double plane::latitude() {
  return currentLatitude;
}

double plane::longtitude() {
  return currentLongtitude;
}

double plane::money() {
  return currentMoney;
}

double plane::refuel() {
  //Fudge fuel price -- between 60 000 and 240 000 Won per refuel
  const int basePrice = 120000;
  default_random_engine generator;
  normal_distribution<double> distribution(0.5,2);
  double priceNow = int(basePrice * distribution(generator) * 100) / 100;
  
  currentMoney -= priceNow;
  if (currentMoney < 0) {
    throw ERROR_OUT_OF_MONEY;
  }
  
  currentRange = maxTheoreticalRange;
  return priceNow;
}

/**** FUNCTIONS ****/

double calculateDistance(double startLatitude, double startLongtitude, double targetLatitude, double targetLongtitude) {
  const int earthRadius = 6370; //km

  return 2*earthRadius*asin(sqrt(haversin(targetLatitude - startLatitude) + cos(startLatitude)*cos(targetLatitude)*haversin(targetLongtitude - startLongtitude)));
}

void test_calculateDistance() {
  //Test 1: 0,0 to 10/180,10/180. Correct answer: 1569 (km)
  if (calculateDistance(0,0,10*pi/180,10*pi/180) == 1569)
    cerr << "test_calculateDistance() Test 1: Success!\n";
  else cerr << "test_calculateDistance() Test 1: Failure! Error: " << calculateDistance(0,0,10*pi/180,10*pi/180) - 1569 << " km.\n";

  //Test 2: 85,54/180;42,86/180 to -20,836/180;-75,19/180. Correct answer: 12550 (km)
  if (calculateDistance(85.54*pi/180,42.86*pi/180,-20.836*pi/180,-75.19*pi/180) == 12550)
    cerr << "test_calculateDistance() Test 2: Success!\n";
  else cerr << "test_calculateDistance() Test 2: Failure! Error: " << calculateDistance(85.54*pi/180,42.86*pi/180,-20.836*pi/180,-75.19*pi/180) - 12550 << " km.\n";
}
