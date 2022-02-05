#ifndef PEACH_EXCEPTION_HPP
#define PEACH_EXCEPTION_HPP

#include <string>

#include "core/normal_exception.hpp"
#include "utils/exception_safety.hpp"

#include <type_traits>
#include <utility>

namespace peach::detail
{

  template< typename... Tys >
  normal_exception throw_exception( const std::size_t line_num, const std::string file_name,
                                       Tys&&... error_message )
  {
    return normal_exception { line_num, file_name, std::forward< Tys >( error_message )... };
  }

} // namespace peach::detail

// TODO: use std::source_location when implemented and then wrap this into the peach namespace
#define PeachException( ... ) detail::throw_exception( __LINE__, __FILE__, ##__VA_ARGS__ )

#endif // PEACH_EXCEPTION_HPP
