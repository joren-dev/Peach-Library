#ifndef PE_BASE_EXCEPTION_HPP
#define PE_BASE_EXCEPTION_HPP

#include <fstream>
#include <stdexcept>
#include <string_view>

namespace peach::detail
{
  class pe_base_exception : virtual public std::runtime_error
  {
  public:
    pe_base_exception( ) = default;

    // clang-format off
    pe_base_exception( const pe_base_exception& ) noexcept = default;
    pe_base_exception( pe_base_exception&& ) noexcept = delete;

    pe_base_exception& operator=( pe_base_exception&& ) = delete;
    pe_base_exception& operator=( const pe_base_exception& ) = delete;
    // clang-format on

    virtual bool output_to_file( std::ofstream& output_file ) const = 0;
    virtual void print_to_console( ) const = 0;

    virtual ~pe_base_exception( ) { };
  };
} // namespace peach::detail

#endif // PE_BASE_EXCEPTION_HPP
