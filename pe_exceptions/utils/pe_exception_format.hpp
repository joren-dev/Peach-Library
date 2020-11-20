#ifndef PE_EXCEPTION_FORMAT_HPP
#define PE_EXCEPTION_FORMAT_HPP

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>

#include "pe_exception_safety.hpp"

namespace peach::detail
{
  template< OutputStreamInsertable... Tys >
  std::string format_error( const std::size_t line_num, const std::string& file_name,
                            Tys&&... args )
  {
    std::stringstream ss { };

    const time_t t { std::time( nullptr ) };
    tm current_time { };
    localtime_s( &current_time, &t );

    ss << std::put_time( &current_time, "[%T]" )
       << " at (line:file) " << line_num << " : " << file_name << " ->\n\t\t{ ";
    ( ( ss << std::forward< Tys >( args ) << ' ' ), ... );
    ss << " }\n\n";

    return ss.str( );
  }

} // namespace peach::detail

#endif // PE_EXCEPTION_FORMAT_HPP
