// plane.h - declaration of the plane class

/***********************************************************
Copyright (c) 2013 Juho Rinta-Paavola

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Softaware is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***************************************************************/

#pragma once

/**** CLASS DECLARATIONS ****/

/** class plane **
 **
 ** plane(int tankSize)
 **   Initialize the plane with the given tank size.
 **
 ** void move(double targetLatitude, double targetLongtitude)
 **   Move to the specified coordinates
 **
 ** int rangePercentage()
 **   Return % of fuel remaining in tank
 **
 ** double latitude(); double longtitude()
 **   Return latitude and longtitude, respectively
 **
 ** double money()
 **   Return amount of money left
 **
 ** double refuel()
 **   Fill the tank and return how much money was spent
 *****************/
class plane {
public:
  plane(int initialRange, double initialLatitude, double initialLongtitude, double initialMoney);
  void move(double targetLatitude, double targetLongtitude);
  int rangePercentage();
  double latitude();
  double longtitude();
  double money();
  double refuel();
private:
  int currentRange, maxTheoreticalRange;
  double currentLatitude, currentLongtitude, currentMoney;
};

/**** FUNCTION DECLARATIONS ****/

double calculateDistance(double startLatitude, double startLongtitude, double targetLatitude, double targetLongtitude);

void test_calculateDistance();
