#ifndef PE_EXCEPTION_HPP
#define PE_EXCEPTION_HPP

#include <string>

#include "core/pe_normal_exception.hpp"
#include "utils/pe_exception_safety.hpp"

#include <type_traits>
#include <utility>

namespace peach::detail
{

  template< typename... Tys >
  pe_normal_exception throw_exception( const std::size_t line_num, const std::string file_name,
                                       Tys&&... error_message )
  {
    return pe_normal_exception { line_num, file_name, std::forward< Tys >( error_message )... };
  }

} // namespace peach::detail

// TODO: use std::source_location when implemented and then wrap this into the peach namespace
#define PeachException( ... ) detail::throw_exception( __LINE__, __FILE__, ##__VA_ARGS__ )

#endif // PE_EXCEPTION_HPP
