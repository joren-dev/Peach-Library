#ifndef PEACH_EXCEPTION_FORMAT_HPP
#define PEACH_EXCEPTION_FORMAT_HPP

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>

#include "exception_safety.hpp"

namespace peach::detail
{
  template< OutputStreamInsertable... Tys >
  std::string format_error( const int line_num, const std::string& file_name,
                            const std::string& prefix, Tys&&... args )
  {
    std::stringstream ss { };

    const time_t t { std::time( nullptr ) };
    tm current_time { };
    localtime_s( &current_time, &t );

    const auto put_time = std::put_time( &current_time, "[%T]" );

    if ( line_num == constants::kNoSourceLocation && file_name.empty( ) )
    {
      ss << '[' << prefix << ']' << put_time << " -> { ";
      ( ( ss << std::forward< Tys >( args ) << ' ' ), ... );
      ss << " }\n\n";
    } else
    {
      ss << '[' << prefix << ']' << put_time << " at (line:file) " << line_num << " : " << file_name
         << " ->\n\t\t{ ";
      ( ( ss << std::forward< Tys >( args ) << ' ' ), ... );
      ss << " }\n\n";
    }

    return std::string { ss.str( ) };
  }

} // namespace peach::detail

#endif // PEACH_EXCEPTION_FORMAT_HPP
