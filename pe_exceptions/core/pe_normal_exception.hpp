#ifndef PE_NORMAL_EXCEPTION_HPP
#define PE_NORMAL_EXCEPTION_HPP

#include <ctime>
#include <fstream>
#include <string>
#include <string_view>
#include <utility>

#include "pe_base_exception.hpp"

#include "../utils/pe_exception_format.hpp"

namespace peach::detail
{
  // Short info:
  // * Two format_error calls are required because the order favors base classes(std::runtime_error) in the ctor init list
  // Link docu: 
  class pe_normal_exception final : virtual public pe_base_exception
  {
  public:
    template< typename... Tys >
    explicit pe_normal_exception( const std::size_t line_num, const std::string& file_name,
                                  Tys&&... args )
        : m_err_msg( format_error( line_num, file_name, std::forward< Tys >( args )... ) ),
          std::runtime_error { format_error( line_num, file_name, std::forward< Tys >( args )... ) }

    {
    }

    // clang-format off
    pe_normal_exception( const pe_normal_exception& ) noexcept = default;
    pe_normal_exception( pe_normal_exception&& ) noexcept = default;

    pe_normal_exception& operator=( pe_normal_exception&& ) = delete;
    pe_normal_exception& operator=( const pe_normal_exception& ) = delete;
    // clang-format on

    const char* what( ) const noexcept override;
    const std::string& what_str( ) const noexcept override;
    void print_to_console( ) const noexcept override;

    ~pe_normal_exception( ) = default;

  private:
    std::string m_err_msg;
  };

} // namespace peach::detail

#endif // PE_NORMAL_EXCEPTION_HPP
