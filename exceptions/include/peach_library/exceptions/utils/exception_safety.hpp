#ifndef PEACH_EXCEPTION_SAFETY_HPP
#define PEACH_EXCEPTION_SAFETY_HPP

#include <concepts>
#include <ostream>
#include <type_traits>

namespace peach::detail
{

  // prevents possibility of a this pointer being passed in the format_error context
  /* TODO : Figure out if this is still needed
  
  template< typename T >
  inline std::ostream&
  operator<<( std::ostream& stream,
              [[maybe_unused]] const T& ec ) requires( std::derived_from< T, pe_base_exception > )
  {
    return stream;
  }

  */

  // clang-format off
  template< typename T > concept OutputStreamInsertable = requires( std::ostream& os, const T& arg )
  {
    { os << arg } ->std::convertible_to< std::ostream& >;
  };
  // clang-format on

} // namespace peach::detail

#endif // PEACH_EXCEPTION_SAFETY_HPP
