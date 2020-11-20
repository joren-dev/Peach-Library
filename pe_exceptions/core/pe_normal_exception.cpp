#include "pe_normal_exception.hpp"

#include <iostream>
#include <string>

using namespace peach::detail;

void pe_normal_exception::print_to_console( ) const
{
  // TODO: possibly determine if compiled application has a console available!
  std::cerr << m_err_msg << '\n';
}

// clang-format off
std::string pe_normal_exception::get_error( ) const noexcept
{
  return m_err_msg;
}
// clang-format on