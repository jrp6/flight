//angleConversion.h - header for tools to convert to/from radians from/to player-readable/-writable string

/***********************************************************
Copyright (c) 2013 Juho Rinta-Paavola

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Softaware is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
***************************************************************/

#pragma once

/**** FUNCTION DECLARATIONS ****/

double toRadians(double degrees, char sign); //e.q. 78,'N' or 162,'W'
double toRadians(double degrees); //e.q. 78 or -162

double toDegrees(double radians);

char getSign(double angle, bool isLatitude); //Returns the 'sign' of the angle
                                             //e.q. 78,true => N' or -162,false => 'W'

#if defined DEBUG
void test_conversions();
#endif
