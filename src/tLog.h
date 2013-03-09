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
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <iomanip>


const char pathSlash = '/';



#define LDEBUG

// set file and level
#ifdef LDEBUG
#define LOGT_SET_LOGFILE(exp)   (logger().setLogfile( exp ))
#define LOGT_SET_LOGFILE_WITHDATE(exp) (logger().setLogfileWithDate( exp ) )
#define LOGT_SET_DEBUG()  (logger().setLogLevelDebug())
#define LOGT_SET_INFO()   (logger().setLogLevelInfo())
#define LOGT_SET_WARN()   (logger().setLogLevelWarn())
#define LOGT_SET_ERROR()  (logger().setLogLevelError())
#define LOGT_SET_FATAL()  (logger().setLogLevelFatal())
#else
#define LOGT_SET_LOGFILE(exp)            (nsl::noFunc())
#define LOGT_SET_LOGFILE_WITHDATE(exp)   (nsl::noFunc())
#define LOGT_SET_DEBUG()  (nsl::noSetFunc())
#define LOGT_SET_INFO()   (nsl::noSetFunc())
#define LOGT_SET_WARN()   (nsl::noSetFunc())
#define LOGT_SET_ERROR()  (nsl::noSetFunc())
#define LOGT_SET_FATAL()  (nsl::noSetFunc())
#endif


// logline in Code
#ifdef LDEBUG
#define LOGT_DEBUG(exp)  (logger().Debug( lfm_,(exp)))
#define LOGT_INFO(exp)   (logger().Info( lfm_,(exp)))
#define LOGT_WARN(exp)   (logger().Warn( lfm_,(exp)))
#define LOGT_ERROR(exp)  (logger().Error( lfm_,(exp)))
#define LOGT_FATAL(exp)  (logger().Fatal( lfm_,(exp)))
#define LOGT_MSG(exp)    (logger().Msg(exp))
#else
#define LOGT_DEBUG(exp)   (nsl::noFunc())
#define LOGT_INFO(exp)    (nsl::noFunc())
#define LOGT_WARN(exp)    (nsl::noFunc())
#define LOGT_ERROR(exp)   (nsl::noFunc())
#define LOGT_FATAL(exp)   (nsl::noFunc())
#define LOGT_MSG(exp)     (nsl::noFunc())
#endif



namespace nsl {

   // placeholder, if logging is off
   inline bool noFunc() {
      return true;
   }
   inline void noSetFunc() {}


   const char pathSlash = '\\';



   template<class T >
   inline std::string toString( T val ) {
      std::ostringstream o;
      o << val;
      return o.str();
   }

   template<>
   inline std::string toString<double>( double val ) {
      std::ostringstream o;
      o << std::setfill( ' ' ) << std::setw( 6 ) << std::setprecision( 3 ) << val;
      return o.str();
   }
   template<>
   inline std::string toString<float>( float val ) {
      std::ostringstream o;
      o << std::setfill( ' ' ) << std::setw( 6 ) << std::setprecision( 3 ) << val;
      return o.str();
   }


   class tLfm  {
      size_t _lineIntern;
      std::string _fileIntern;
      std::string _methodIntern;
   public:
      tLfm(): _lineIntern( 0 ), _fileIntern( "" ), _methodIntern( "" ) {}

      tLfm( size_t line_, std::string const& file_, std::string const& method_ = "" )
         : _lineIntern( line_ ), _fileIntern( file_ ), _methodIntern( method_ )
      {}
      size_t getLine()const {
         return _lineIntern;
      }
      std::string const& getFilename()const {
         return _fileIntern;
      }

      std::string const& getMethod()const {
         return _methodIntern;
      }
      ~tLfm() {}
   };

   // set to 'false' disables logging for all levels at compiletime
   // the loglines stays in code, only writíng to the logfile ist suppressed
   //const bool useLogger = true;




   class cLog {

   public:
      cLog();
      ~cLog();

      // write 'txt' to logfile
      // return: true, if ok
      bool Debug( tLfm const& lfm , const std::string& txt ) const ;
      bool Info( tLfm const& lfm , const std::string& txt ) const ;
      bool Warn( tLfm const& lfm , const std::string& txt ) const ;
      bool Error( tLfm const& lfm , const std::string& txt ) const ;
      bool Fatal( tLfm const& lfm , const std::string& txt ) const ;

      // ohne Angabe, wo die Logzeile erzeugt wird
      // logging von längeren Texten
      bool Msg( const std::string& txt ) const;

      bool Debug( const std::string& txt )const {
         return Debug( tLfm(), txt );
      }
      bool Info( const std::string& txt ) const {
         return Info( tLfm(), txt );
      }
      bool Warn( const std::string& txt ) const {
         return Warn( tLfm(), txt );
      }
      bool Error( const std::string& txt ) const {
         return Error( tLfm(), txt );
      }
      bool Fatal( const std::string& txt ) const {
         return Fatal( tLfm(), txt );
      }

      enum tagLevel { CLOG_DEBUG = 1, CLOG_INFO = 2, CLOG_WARN = 3, CLOG_ERROR = 4,  CLOG_FATAL = 5, CLOG_NONE = 6 };


      tagLevel setLogLevelDebug()const {
         tagLevel tmp = _logLevel;
         _logLevel = CLOG_DEBUG;
         return tmp;
      }
      tagLevel setLogLevelInfo()const {
         tagLevel tmp = _logLevel;
         _logLevel = CLOG_INFO;
         return tmp;
      }
      tagLevel setLogLevelWarn()const {
         tagLevel tmp = _logLevel;
         _logLevel = CLOG_WARN;
         return tmp;
      }
      tagLevel setLogLevelError()const {
         tagLevel tmp = _logLevel;
         _logLevel = CLOG_ERROR;
         return tmp;
      }
      tagLevel setLogLevelFatal()const {
         tagLevel tmp = _logLevel;
         _logLevel = CLOG_FATAL;
         return tmp;
      }
      tagLevel setLogLevelNone()const {
         tagLevel tmp = _logLevel;
         _logLevel = CLOG_NONE;
         return tmp;
      }

   private:
      char const* const _LOG_DEBUG;
      char const* const _LOG_INFO;
      char const* const _LOG_WARN;
      char const* const _LOG_ERROR;
      char const* const _LOG_FATAL;
      // is mutable, to use logging in const environments
      mutable std::string  _file;
      mutable tagLevel _logLevel;


      // prevents copying of the instance
      cLog( cLog const& s );
      cLog& operator= ( cLog const& s );

   public:

      // sets the logfile, doesn't change loglevel
      bool setLogfile( std::string const& file )const;
      bool setLogfileWithDate( std::string const& file )const;


   };


}



nsl::tLfm Lfm( size_t line_, std::string const& file_, std::string const& method_ = "" );

// short macro for __LINE__,__FILE__, __FUNCTION__
// used as parameter for log methods, gets info for logging
#define lf_ __LINE__,__FILE__

#ifdef __linux__
#define lfm_ Lfm(__LINE__,__FILE__,__FUNCTION__)
#elif __BORLANDC__
#define lfm_ Lfm(__LINE__,__FILE__,__FUNC__)
#elif _WIN32
#define lfm_ Lfm(__LINE__,__FILE__,__FUNCTION__)
#endif




// global singleton instance
// bitte nicht am Ende des Programms Logzeilen verwenden,
// es ist nicht garantiert, dass der Destruktor des Loggers als letzte Operation am Programmende ausgeführt wird
nsl::cLog const& logger();




#endif  // TLOG_H

//EOF

