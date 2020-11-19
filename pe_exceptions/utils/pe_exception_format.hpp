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

    ss << "Exception occurred at: " << std::put_time( &current_time, "[%T]" )
       << " on line: " << line_num << " in file: " << file_name << ".\nException details: ";
    ( ( ss << std::forward< Tys >( args ) << ' ' ), ... );

    return ss.str( );
  }

} // namespace peach::detail

#endif // PE_EXCEPTION_FORMAT_HPP
