#include "peach_library/exceptions/core/normal_exception.hpp"

#include <iostream>
#include <string>

using namespace peach::detail;

// clang-format off
// Returning a c_str of m_err_msg is legal because `what()` can only be called as long as the pe_normal_exception 
// object still exists. Make sure to copy the contents in case u want to use this outside the scope pe_normal_exception is available.
const char* normal_exception::what( ) const noexcept 
{ 
    return m_err_msg.c_str( ); 
}
// clang-format on

void normal_exception::print_to_console( ) const noexcept
{
  // TODO: possibly determine if compiled application has a console available!
  std::cerr << R"(normal_exception( " )" << m_err_msg.substr( 0, m_err_msg.size( ) - 2 )
            << R"( " ))" << '\n';
}

// clang-format off
const std::string& normal_exception::what_str( ) const noexcept
{
  return m_err_msg;
}
// clang-format on
