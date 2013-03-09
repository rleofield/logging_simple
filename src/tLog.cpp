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


#include <limits.h>
#include <string.h>
#include <sstream>
#include <string>



#include "tLog.h"
#include "tlock.h"


namespace nsl {


   tMutexLock&  getLockObjekt() {
      static tMutexLock lock; // executed only once, static
      return lock;
   }


   namespace {


      static size_t runningnumber = 0;

      // writes __LINE,__FILE__ to log stream
      void lfm_InfoToStream( std::ofstream& o, long line, const string&  cppfile, string const& method = "" ) {
         if( cppfile.length() == 0 ) {
            return;   // never happens, see __FILE__
         }

         runningnumber++;
         string num = toString( runningnumber );
         o << num;
         o << ' ';
         o << std::setfill( ' ' ) << std::left << std::setw( 20 );
         size_t i = cppfile.rfind( pathSlash );

         if( i  != string::npos ) {
            o << cppfile.substr( i + 1 );
         } else {
            o << cppfile;
         }

         o << std::setfill( ' ' ) << std::right << std::setw( 5 );
         o << line;
         o << ' ';

         if( method.size() > 0 ) {
            o << std::setfill( ' ' ) << std::left << std::setw( 40 );
            string m = method;

            if( m.size() > 40 ) {
               m  = m.substr( 0, 40 );
            }

            o << m;
            o << ": ";
         }
      }

      void fill( std::ostream& o, size_t w, int val ) {
         char fill = '0';
         o << std::setfill( fill ) << std::setw( w )  << val;
      }
      void fill1( std::ofstream& o, size_t w, int val ) {
         char fill = '0';
         o << std::setfill( fill ) << std::setw( w )  << val;
      }


      // writes current time to log stream, no year
      void logTime( std::ofstream& o ) {
         time_t osBinaryTime;  // C run-time time (defined in <time.h>)
         time( &osBinaryTime ) ;  // Get the current time from the os
         struct tm* today = localtime( &osBinaryTime );
         fill1( o, 2, today->tm_mon + 1 );
         o << ".";
         fill1( o, 2, today->tm_mday );
         o <<  " ";
         fill1( o, 2, today->tm_hour );
         o << ":";
         fill1( o, 2, today->tm_min );
         o << ":";
         fill1( o, 2, today->tm_sec );
         o << ":";
      }

      string date_time() {
         time_t osBinaryTime;  // C run-time time (defined in <time.h>)
         time( &osBinaryTime ) ;  // Get the current time from the os
         struct tm* today = localtime( &osBinaryTime );
         stringstream o;
         fill( o, 4, today->tm_year + 1900 );
         fill( o, 2, today->tm_mon + 1 );
         fill( o, 2, today->tm_mday );
         o <<  "_";
         fill( o, 2, today->tm_hour );
         fill( o, 2, today->tm_min );
         fill( o, 2, today->tm_sec );
         return o.str();
      }
      string date() {
         time_t osBinaryTime;  // C run-time time (defined in <time.h>)
         time( &osBinaryTime ) ;  // Get the current time from the os
         struct tm* today = localtime( &osBinaryTime );
         stringstream o;
         fill( o, 4, today->tm_year + 1900 );
         fill( o, 2, today->tm_mon + 1 );
         fill( o, 2, today->tm_mday );
         return o.str();
      }

      // internal writer to logfile
      bool write_( std::string const& logfile, tLfm const& lfm , string const& level, string const& txt )  {

         int line = lfm.getLine();
         std::string cppfile = lfm.getFilename();
         std::string method = lfm.getMethod();

         // lock for a second thread
         // sets a lock at the CriticalSection object
         // releases the lock at end of scope
         tLock l( getLockObjekt() );

         // open log file
         std::ofstream fp( logfile.c_str(), std::ios_base::app );

         if( fp.bad() ) {
            string s;
            s  = "logfile: " + logfile + " not found." ;
            std::cout << s << std::endl;
            return false;
         }

         // set time an start if line
         logTime( fp );

         // level
         fp << " " << level  << " ";

         // append __LINE,__FILE__ to line
         lfm_InfoToStream( fp, line, cppfile, method );

         // write the log message an finish the line
         fp << " " << txt << std::endl;
         return true;
         // log file is implicitly closed by destructor
      }

      // internal writer to logfile
      bool write_( std::string const& logfile, string const& txt )  {


         // lock for a second thread
         // sets a lock at the CriticalSection object
         // releases the lock at end of scope
         tLock l( getLockObjekt() );

         // open log file
         std::ofstream fp( logfile.c_str(), std::ios_base::app );

         if( fp.bad() ) {
            string s;
            s  = "logfile: " + logfile + " not found." ;
            std::cout << s << std::endl;
            return false;
         }

         // write the log message an finish the line
         fp << txt << std::endl;
         return true;
      }

      // entferne den Filenamen aus dem Pfad
      string extractPath( string const&  file ) {
         size_t i = file.rfind( pathSlash );

         if( i  != string::npos ) {
            return file.substr( 0, i + 1 );
         }

         return file;
      }

   }


   bool write( string const& _file, string const& level, tLfm const& lfm , string const& txt )  {
      if( _file.length() == 0 ) {
         return false;
      }

      return write_( _file, lfm, level, txt );
   }
   bool write( string const& _file, string const& txt )  {
      if( _file.length() == 0 ) {
         return false;
      }

      return write_( _file, txt );
   }

   bool checkPath( string const& f ) {
      string path = extractPath( f );

      if( path == f ) {
         return true;   // f has no path
      }

      int fp = access( path.c_str(), R_OK );

      if( fp == -1 ) {
         return false;
      }

      return true;
   }

   bool cLog::setLogfile( string const& file )const {
      bool b = checkPath( file );

      if( !b ) {
         return false;
      }

      _file = file + ".log";
      return true;
   }
   bool cLog::setLogfileWithDate( string const& file )const {
      bool b = checkPath( file );

      if( !b ) {
         return false;
      }

      _file = file + "_" + date() + ".log";
      return true;
   }

   cLog::cLog():
      _LOG_DEBUG( "DEBUG" ),
      _LOG_INFO( "INFO " ),
      _LOG_WARN( "WARN " ),
      _LOG_ERROR( "ERROR" ),
      _LOG_FATAL( "FATAL" ), _file(), _logLevel( CLOG_DEBUG ) {

   }

   cLog::~cLog() {

   }

   bool cLog::Debug( tLfm const& lfm , const std::string& txt ) const {
      if( _logLevel > CLOG_DEBUG ) {
         return true;
      }

      return write( _file, _LOG_DEBUG, lfm, txt );
   }
   bool cLog::Info( tLfm const& lfm , const std::string& txt ) const {
      if( _logLevel > CLOG_INFO ) {
         return true;
      }

      return write( _file, _LOG_INFO, lfm, txt );
   }
   bool cLog::Warn( tLfm const& lfm , const std::string& txt ) const {
      if( _logLevel > CLOG_WARN ) {
         return true;
      }

      return write( _file, _LOG_WARN, lfm, txt );
   }
   bool cLog::Error( tLfm const& lfm , const std::string& txt ) const {
      if( _logLevel > CLOG_ERROR ) {
         return true;
      }

      return write( _file, _LOG_ERROR, lfm, txt );
   }
   bool cLog::Fatal( tLfm const& lfm , const std::string& txt ) const {
      if( _logLevel > CLOG_ERROR ) {
         return true;
      }

      return write( _file, _LOG_FATAL, lfm, txt );
   }
   bool cLog::Msg( std::string const& txt ) const {
      return write( _file, txt );
   }

   //nsl::cLog* ptrLoggerInstance = 0; // executed only once, static


}


nsl::tLfm Lfm( size_t line_, std::string const& file_, std::string const& method_ ) {
   return nsl::tLfm( line_, file_, method_ );
}



// gets singleton instance
nsl::cLog const& logger() {
   static nsl::cLog loggerInstance;
   return  loggerInstance;
}





//EOF

