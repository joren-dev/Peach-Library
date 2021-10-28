#ifndef PE_BASE_EXCEPTION_HPP
#define PE_BASE_EXCEPTION_HPP

#include <concepts>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace peach::detail
{
  class pe_base_exception : virtual public std::runtime_error
  {
  public:
    pe_base_exception( ) = default;

    // clang-format off
    pe_base_exception( const pe_base_exception& ) noexcept = default;
    pe_base_exception( pe_base_exception&& ) noexcept = default;

    pe_base_exception& operator=( pe_base_exception&& ) = default;
    pe_base_exception& operator=( const pe_base_exception& ) = delete;
    // clang-format on

    virtual std::string get_error( ) const noexcept = 0;
    virtual void print_to_console( ) const noexcept = 0;

    virtual ~pe_base_exception( ) { };
  };

  template< typename T >
  std::ostream& operator<<( std::ostream& output_file,
                            const T& rhs ) requires( std::derived_from< T, pe_base_exception > )
  {
    output_file << rhs.get_error( );

    return output_file;
  }

} // namespace peach::detail

#endif // PE_BASE_EXCEPTION_HPP
