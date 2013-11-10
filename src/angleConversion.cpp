//angleConversion.cpp - tools to convert to/from radians from/to player-readable/-writable string

/***********************************************************
Copyright (c) 2013 Juho Rinta-Paavola

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Softaware is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***************************************************************/

#include <iostream>
#include "main.h"
#include "error.h"
#include "angleConversion.h"
using namespace std;

/**** GLOBAL VARIABLES ****/

extern const double pi;

/**** FUNCTIONS ****/

double toRadians(double degrees) { return degrees*(pi/180); }

double toRadians(double degrees, char sign) {
  if (sign == 'N' || sign == 'E') return toRadians(degrees);
  else if (sign == 'S' || sign == 'W') return -1*toRadians(degrees);
  else throw ERROR_INVALID_COORDINATE;
}

double toDegrees(double radians) { return radians*(180/pi); }

char getSign(double angle, bool isLatitude) {
  if (angle >= 0) {
    if (isLatitude) return 'N';
    else return 'E';
  }
  else {
    if (isLatitude) return 'S';
    else return 'W';
  }
}

#if defined DEBUG
void test_conversions() {
  cerr << "Pi = " << fixed << pi << '\n';
  if (toRadians(78) == 1.36135682)
    cerr << "test_conversions(): toRadians(double) test 1 Success!\n";
  else
    cerr << "test_conversions(): toRadians(double) test 1 Failure! Error: " << toRadians(78) - 1.36135682 << '\n';

  if (toRadians(-162) == -2.82743339)
    cerr << "test_conversions() toRadians(double) test 2 Success! \n";
  else
    cerr << "test_conversions(): toRadians(double) test 2 Failure! Error: " << toRadians(-162) - (-2.82743339) << '\n';

  if (toRadians(78,'N') == 1.36135682)
    cerr << "test_conversions(): toRadians(double, char) test 1 Success!\n";
  else
    cerr << "test_conversions(): toRadians(double, char) test 1 Failure! Error: " << toRadians(78,'N') - 1.36135682 << '\n';

  if (toRadians(162,'W') == -2.82743339)
    cerr << "test_conversions(): toRadians(double, char) test 2 Success!\n";
  else
    cerr << "test_conversions(): toRadians(double, char) test 2 Failure! Error: " << toRadians(162, 'W') - (-2.82743339) << '\n';

  if (toDegrees(pi) == 180)
    cerr << "test_conversions(): toDegrees(double) test 1 Success!\n";
  else
    cerr << "test_conversions(): toDegrees(double) test 1 Failure! Error: " << toDegrees(pi) - 180 << '\n';

  if (toDegrees(-1.5) == -85.9436693)
    cerr << "test_conversions(): toDegrees(double) test 2 Success!\n";
  else
    cerr << "test_conversions(): toDegrees(double) test 2 Failure! Error: " << toDegrees(-1.5) - (-85.9436693) << '\n';
}
#endif
