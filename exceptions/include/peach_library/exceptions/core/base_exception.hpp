#ifndef PEACH_BASE_EXCEPTION_HPP
#define PEACH_BASE_EXCEPTION_HPP

#include <concepts>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace peach::detail
{
  class base_exception : virtual public std::runtime_error
  {
  public:
    base_exception( ) = default;

    // clang-format off
    base_exception( const base_exception& ) noexcept = default;
    base_exception(base_exception&& ) noexcept = default;

    base_exception& operator=(base_exception&& ) = default;
    base_exception& operator=( const base_exception& ) = delete;
    // clang-format on

    virtual const std::string& what_str( ) const noexcept = 0;
    virtual void print_to_console( ) const noexcept = 0;

    virtual ~base_exception( ) { };
  };

  template< typename T >
  std::ostream& operator<<( std::ostream& output_file,
                            const T& rhs ) requires( std::derived_from< T, base_exception > )
  {
    output_file << rhs.what_str( );

    return output_file;
  }

} // namespace peach::detail

#endif // PEACH_BASE_EXCEPTION_HPP
