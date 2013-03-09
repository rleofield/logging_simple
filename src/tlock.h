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

#ifndef tMutexLock_H
#define tMutexLock_H

using namespace std;


class tMutexLock {
   pthread_mutex_t cs;
public:
   tMutexLock(): cs() {
      pthread_mutex_init( &cs, NULL );
   }
   void lock() {
      pthread_mutex_lock( &cs );
   }
   void unlock() {
      pthread_mutex_unlock( &cs );
   }

   ~tMutexLock() {
      pthread_mutex_destroy( &cs );
   }
};

class tLock {
public:
   tLock( tMutexLock& pm ): mutexPtr( pm ) {
      mutexPtr.lock();
   }

   ~tLock() {
      mutexPtr.unlock();
   }


private:
   tMutexLock& mutexPtr;

};





#endif  // TLOCK_H

//EOF
