#ifndef PE_EXCEPTION_SAFETY_HPP
#define PE_EXCEPTION_SAFETY_HPP

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

  namespace _detail
  {
    struct okay
    {
    };
    struct swap_returns_okay_only_if_no_using_std
    {
    };

    template< typename T, typename U > okay swap( T, const U& );
  } // namespace _detail

  // security measures to ensure using namespace std is not used
  template< typename T = peach::detail::_detail::swap_returns_okay_only_if_no_using_std >
  inline constexpr bool detect_using_namespace_std =
      !std::is_same_v< decltype( swap( std::declval< T& >( ), std::declval< T& >( ) ) ),
                       peach::detail::_detail::okay >;

  static_assert( !detect_using_namespace_std<>,
                 "how dare you having an using namespace std in code, that's illegal freak!" );

} // namespace peach::detail

#endif // PE_EXCEPTION_SAFETY_HPP
