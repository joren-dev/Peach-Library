#include "pe_normal_exception.hpp"

#include <iostream>
#include <string>

using namespace peach::detail;

bool pe_normal_exception::output_to_file( std::ofstream& output_file ) const
{
  if ( output_file.fail( ) || !output_file.is_open( ) )
    return false;

  output_file << m_err_msg;

  return true;
}

void pe_normal_exception::print_to_console( ) const
{
  // TODO: possibly determine if compiled application has a console available!
  std::cerr << m_err_msg << '\n';
}
