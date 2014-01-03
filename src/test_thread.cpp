/* --------------------------------------------------------------------------
Copyright 2014 by Richard Albrecht
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



// boost
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>


#include "tLog.h"
#include "tLog_Category_default.h"

// global variables
static boost::mutex MUTEX;                  //boost mutex

// generic data storage class
class Payload {
public:
   int id;
   int other;
};


void func( Payload* in );

// example function called by the threads
void func( Payload* in ) {

   std::stringstream s;
   s << "I'm thread number " << in->id << " and my other data is " << in->other;
   LOGT_DEBUG( s.str() );

   for( int i = 0; i < 10; i++ ) {
      std::stringstream s1;
      s1 << "thread " << in->id ;
      boost::lock_guard<boost::mutex> lock( MUTEX );
      std::cout << s1.str() << std::endl;
      string s2 = std::to_string( i );
      LOGT_DEBUG( s1.str() + ",  test Log line: " + s2 );
   }

   std::stringstream s3;
   s3 << "I'm thread number " << in->id << " and ready " << in->other;
   LOGT_DEBUG( s3.str() );

   return;
}

void test_thread( ) {

   LOGT_DEBUG( "**************************** Begin ****************************" );

   // threads sample
   {
      // set number of threads
      int no_of_threads = 4;
      boost::thread_group threads;
      std::vector<Payload> payloads( no_of_threads );

      //fill with data
      for( int i = 0; i < no_of_threads; i++ ) {
         payloads[i].id    = i;
         payloads[i].other = 6;
      }

      // call threads
      for( int i = 0; i < no_of_threads; i++ ) {
         threads.add_thread( new boost::thread( func, &( payloads[i] ) ) );
      }

      // wait for threads to end
      threads.join_all();

   }//destructor of thread_group deletes all thread pointer

   LOGT_DEBUG( "****************************  End  ****************************\n\n" );

   return;

}

// EOF


