// flight.cpp - main file of the flight game

/***********************************************************
Copyright (c) 2013 Juho Rinta-Paavola

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Softaware is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***************************************************************/

/**** INCLUDES ****/

#include <iostream>
#include <iomanip>

#include <cmath>
#include <cctype>

#include <string>

#include "main.h"
#include "plane.h"
#include "error.h"
#include "angleConversion.h"

using namespace std;

//Note: all latitudes and longtitudes in rad
//Positive: Northern latitude/Eastern longtitude

/**** GLOBAL VARIABLES ****/
extern const double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

/**** FUNCTIONS ****/

int main() { try {
    cout << "Copyright (c) 2013 Juho Rinta-Paavola\n\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Softaware is furnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n\n\n"; // Don't edit the legalese!

#if defined DEBUG
    test_calculateDistance();
    test_conversions();
#endif

    const int playerRange = 1000;
    const double EFOULatitude = 0.360717592594*pi; //Latitude of the Oulu airport
    const double EFOULongtitude = 0.140864197533*pi; //Longtitude of the Oulu airport
    const double initialMoney = 100000;
    
    plane playerPlane(playerRange, EFOULatitude, EFOULongtitude, initialMoney);

    while (true) { //Main game loop
      cout << "\nYour current coordinates are: " << fixed << abs(toDegrees(playerPlane.latitude())) << ' ' << getSign(playerPlane.latitude(), true) << ", " << abs(toDegrees(playerPlane.longtitude())) << ' ' << getSign(playerPlane.longtitude(), false) << ".\n";
      cout << playerPlane.rangePercentage() << "% of fuel remaining\n";
      cout << setprecision(2) << "You have " << playerPlane.money() << " North Korea Won\n";
      cout << "What's your order? (MOVE, QUIT or REFUEL)\nORDER> ";

      string playerOrder;
      cin >> playerOrder;
      
      for (int i = 0; i < playerOrder.length(); ++i)
	playerOrder[i] = toupper(playerOrder[i]);

      if (playerOrder == "QUIT") break;

      else if (playerOrder == "MOVE") {

	cout << "Please enter the coordinates you want to move to.\nMOVE> ";

	double latitude = 361, longtitude = 361;
	char latitudeSign = 'I', longtitudeSign = 'I';
	cin >> latitude >> latitudeSign >> longtitude >> longtitudeSign;
	try {
	  playerPlane.move(toRadians(latitude, latitudeSign), toRadians(longtitude, longtitudeSign));
	}
	catch (error e) {
	  if (e == ERROR_INVALID_COORDINATE)
	    cout << "Sorry, that is not a valid coordinate.\n";
	  else throw;
	}
      }
      else if (playerOrder == "REFUEL") {
	cout << "The refueling took " << playerPlane.refuel() << " Won\n"; //Note: refuel() also changes the plane's remaining fuel and money
      }
      else cout << "Invalid order: " << playerOrder << "\n\n";
      
      //Check for win condition - allow for error up to 1 degree
      const double ZKPYLatitude = toRadians(39.0);
      const double ZKPYLongtitude = toRadians(126.0);
      if (abs(playerPlane.latitude() - ZKPYLatitude) <= toRadians(1.0) && abs(playerPlane.longtitude() - ZKPYLongtitude) <= toRadians(1.0)) {
	cout << "Congratulations! Thanks to your efforts, North Korea has won the war and communism rules the earth!\n";
	break;
      }
    }
  }
  catch (error e) {
    if (e == ERROR_UNDEFINED) cerr << "\nException caught: ERROR_UNDEFINED\n";
    else if (e == ERROR_OUT_OF_RANGE) cout << "\nYour plane has run out of petrol and crashed. The enemy has won the war. Better luck next time!\n";
    else if (e == ERROR_OUT_OF_MONEY) cout << "\nYou have run out of money and gone into debt. Damn those capitalist pigs! Better luck next time!\n";
  }
}
