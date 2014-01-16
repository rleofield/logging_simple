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

#include "tLog.h"
#include "tLog_Category_default.h"

using namespace std;

using namespace rlf_tlog;

void test_log_A() ;
void test_log_B() ;
void test_log_C() ;
void test_log_D() ;
void test_thread();

void test_log() {
   string lf = "test"; // extension is added (".log")
   bool b = logger().setLogfile( lf );

   if( b == false ) {
      cout << "setLogfile: " << lf << " path for logging dosn't exist: '" << lf <<  "'" << endl;
   }

   // set the level for each category, must be set, default is NONE = no logging
   logger().setLogLevel( eLevel::WARN, eCategory::_default );
   logger().setLogLevel( eLevel::LDEBUG, eCategory::Cat_A );
   logger().setLogLevel( eLevel::LDEBUG, eCategory::Cat_B );
   logger().setLogLevel( eLevel::LERROR, eCategory::Cat_C );
   logger().setLogLevel( eLevel::LDEBUG, eCategory::Cat_D );

   LOGT_INFO( " Start  " );

   // use macros for logging
   LOGT_DEBUG( " Debug " );
   LOGT_INFO( " Info  " );
   LOGT_WARN( " Warn  " );
   LOGT_ERROR( " Error  " );
   LOGT_FATAL( " Fatal  " );


   test_log_A();
   test_log_B();
   test_log_C();
   test_log_D();
   test_thread();

   for( int i = 0; i < 100; i++ ) {
      string s = std::to_string( i );
      LOGT_DEBUG( "test Log line: " + s );
   }

   LOGT_INFO( " end: " );

}



int main( void ) {

   test_log();



   return 0;
}
