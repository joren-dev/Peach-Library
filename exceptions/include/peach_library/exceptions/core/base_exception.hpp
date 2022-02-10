#ifndef PEACH_BASE_EXCEPTION_HPP
#define PEACH_BASE_EXCEPTION_HPP

#include <concepts>
#include <fstream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace peach::detail
{
  class BaseException : virtual public std::runtime_error
  {
  public:
    BaseException( ) = default;

    // clang-format off
    BaseException( const BaseException& ) noexcept = default;
    BaseException(BaseException&& ) noexcept = default;

    BaseException& operator=(BaseException&& ) = default;
    BaseException& operator=( const BaseException& ) = delete;
    // clang-format on

    virtual const std::string& what_str( ) const noexcept = 0;
    virtual void print_to_console( ) const noexcept = 0;

    virtual ~BaseException( ) { };
  };

  template< typename T >
  std::ostream& operator<<( std::ostream& output_file,
                            const T& rhs ) requires( std::derived_from< T, BaseException > )
  {
    output_file << rhs.what_str( );

    return output_file;
  }

} // namespace peach::detail

#endif // PEACH_BASE_EXCEPTION_HPP
