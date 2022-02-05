#ifndef PEACH_NORMAL_EXCEPTION_HPP
#define PEACH_NORMAL_EXCEPTION_HPP

#include <ctime>
#include <fstream>
#include <string>
#include <string_view>
#include <utility>

#include "base_exception.hpp"

#include "../utils/exception_format.hpp"

namespace peach::detail
{
  // Short info:
  // * Two format_error calls are required because the order favors base classes(std::runtime_error) in the ctor init list
  // Link docu: 
  class normal_exception final : virtual public base_exception
  {
  public:
    template< typename... Tys >
    explicit normal_exception( const std::size_t line_num, const std::string& file_name,
                                  Tys&&... args )
        : m_err_msg( format_error( line_num, file_name, std::forward< Tys >( args )... ) ),
          std::runtime_error { format_error( line_num, file_name, std::forward< Tys >( args )... ) }

    {
    }

    // clang-format off
    normal_exception( const normal_exception& ) noexcept = default;
    normal_exception(normal_exception&& ) noexcept = default;

    normal_exception& operator=(normal_exception&& ) = delete;
    normal_exception& operator=( const normal_exception& ) = delete;
    // clang-format on

    const char* what( ) const noexcept override;
    const std::string& what_str( ) const noexcept override;
    void print_to_console( ) const noexcept override;

    ~normal_exception( ) = default;

  private:
    std::string m_err_msg;
  };

} // namespace peach::detail

#endif // PEACH_NORMAL_EXCEPTION_HPP
