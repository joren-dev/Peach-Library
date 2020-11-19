#ifndef PE_EXCEPTION_SAFETY_HPP
#define PE_EXCEPTION_SAFETY_HPP

#include <concepts>
#include <ostream>
#include <type_traits>

namespace peach::detail
{

  // prevents possibility of a this pointer being passed in the format_error context
  class pe_fatal_error;
  inline std::ostream& operator<<( std::ostream& stream, [[maybe_unused]] const pe_fatal_error& ec )
  {
    return stream;
  }

  template< typename T > concept OutputStreamInsertable = requires( std::ostream& os, const T& arg )
  {
    {
      os << arg
    }
    ->std::convertible_to< std::ostream& >;
  };

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

} // namespace peach::detail

// security measures to ensure using namespace std is not used
template< typename T = peach::detail::_detail::swap_returns_okay_only_if_no_using_std >
inline constexpr auto detect_using_namespace_std =
    !std::is_same_v< decltype( swap( std::declval< T& >( ), std::declval< T& >( ) ) ),
                     peach::detail::_detail::okay >;

static_assert( !detect_using_namespace_std<>,
               "including any peach header after a `using namespace std` is illegal!" );

#endif // PE_EXCEPTION_SAFETY_HPP
