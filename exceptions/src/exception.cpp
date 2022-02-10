#include <peach_library/exceptions/exception.hpp>

#include <source_location>

namespace peach::detail
{
  std::source_location get_source_location_details( const std::source_location sl ) noexcept
  {
    return sl;
  }
} // namespace peach::detail
