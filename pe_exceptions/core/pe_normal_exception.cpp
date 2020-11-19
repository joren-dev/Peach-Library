#include "pe_normal_exception.hpp"

#include <iostream>
#include <string>

using namespace peach::detail;

std::string pe_normal_exception::init( const std::string& exception_msg )
{
  m_err_msg = exception_msg;
  return m_err_msg;
}

bool pe_normal_exception::output_to_file( ) const
{
  // TODO: output to file!
  return { };
}
void pe_normal_exception::print_to_console( ) const
{
  // TODO: possibly determine if compiled application has a console available!
  std::cerr << m_err_msg << '\n';
}
