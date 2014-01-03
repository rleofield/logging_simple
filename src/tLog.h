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


#ifndef TLOG_H
#define TLOG_H

#include <string>


#include "tLogDefs.h"
#include "tLogEnum.h"




namespace rlf_tlog {
   class tLogImpl;
}

namespace rlf_tlog {
   using std::string;


   class tLog {
      rlf_tlog::tLogImpl* pImpl;
   public:
      tLog();
      ~tLog();

      // all methods are 'const', for use in 'const' methods

      // write 'txt' to logfile
      void log( tLfmCL const& lfmc ) const ;

      eLevel setLogLevel( eLevel level, eCategory cat  = eCategory::_default )const;

      // sets the logfile, doesn't change loglevel
      bool setLogfile( std::string const& file )const;
      bool setLogfileWithDate( std::string const& file )const;


   private:
      // prevents copying of the instance
      tLog( tLog const& s );
      tLog& operator= ( tLog const& s );

   };

   // global singleton instance
   tLog const& logger();

}

#define TLOG_WITH_CATEGORY_DEBUG


#ifdef TLOG_WITH_CATEGORY_DEBUG
// enable categories A B C D
#define L_A_DEBUG
#define L_B_DEBUG
#define L_C_DEBUG
#define L_D_DEBUG

#endif

#define L_DEFAULT_DEBUG






#endif  // TLOG_WITH_CATEGORY_H

//EOF

