#ifndef PE_EXCEPTION_FORMAT_HPP
#define PE_EXCEPTION_FORMAT_HPP

#include <sstream>

#include "pe_exception_safety.hpp"

namespace peach::detail
{
  template< OutputStreamInsertable... Tys >
  std::string format_error( const size_t line_num, const std::string& file_name, Tys&&... args )
  {
    std::stringstream ss { };

    ss << "Exception occurred on line: " << line_num << " in file: " << file_name << ".\nError details: ";
    ( ( ss << std::forward< Tys >( args ) << ' ' ), ... );

    return ss.str( );
  }

} // namespace peach::detail

#endif // PE_EXCEPTION_FORMAT_HPP
