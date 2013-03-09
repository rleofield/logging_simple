/* --------------------------------------------------------------------------
    Copyright 2012 by Richard Albrecht
    richard.albrecht@rleofield.de
    www.rleofield.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ------------------------------------------------------------------------------
*/

#include <iostream>
#include <fstream>

#include "tLog.h"

using namespace std;
using namespace nsl;



int main( void ) {

   string lf = "test"; // extension is added (".log")
   bool b = logger().setLogfile( lf );

   if( b == false ) {
      cout << "setLogfile: " << lf << " path for logging dosn't exist: '" << lf <<  "'" << endl;
   }

   logger().setLogLevelDebug();
   logger().Info( lfm_, " Start  " );

   for( int i = 0; i < 100; i++ ) {
      string s = std::to_string( i );
      logger().Debug( lfm_, "test Log line: " + std::to_string( i ) );
   }

   logger().Info( lfm_, " end: " );

   return 0;
}
