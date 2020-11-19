#ifndef PE_EXCEPTION_SAFETY_HPP
#define PE_EXCEPTION_SAFETY_HPP

#include <ostream>

namespace peach::detail
{

  // prevents possibility of a this pointer being passed in the format_error context
  class pe_fatal_error;
  inline std::ostream& operator<<( std::ostream& stream, [[maybe_unused]] const pe_fatal_error& ec ) { return stream; }

  template< typename T > concept OutputStreamInsertable = requires( std::ostream& os, const T& arg )
  {
    {
    os << arg
    }
    ->std::convertible_to< std::ostream& >;
  };

} // namespace peach::detail

#endif // PE_EXCEPTION_SAFETY_HPP
