#ifndef PE_NORMAL_EXCEPTION_HPP
#define PE_NORMAL_EXCEPTION_HPP

#include <string>
#include <utility>

#include "pe_base_exception.hpp"

#include "../utils/pe_exception_format.hpp"

namespace peach::detail
{
  // Short info:
  // Link docu:
  class pe_normal_exception final : virtual public pe_base_exception
  {
  public:
    template< typename... Tys >
    explicit pe_normal_exception( const std::size_t line_num, const std::string& file_name, Tys&&... args )
        : std::runtime_error { init( format_error( line_num, file_name, std::forward< Tys >( args )... ) ) }
    {
    }

    std::string init( const std::string& exception_msg );

    // clang-format off
    pe_normal_exception( const pe_normal_exception& ) noexcept = default;
    pe_normal_exception( pe_normal_exception&& ) noexcept = delete;

    pe_normal_exception& operator=( pe_normal_exception&& ) = delete;
    pe_normal_exception& operator=( const pe_normal_exception& ) = delete;
    // clang-format on

    std::string m_err_msg;

    bool output_to_file( ) const override;
    void print_to_console( ) const override;

    ~pe_normal_exception( ) = default;
  };

} // namespace peach::detail

#endif // PE_NORMAL_EXCEPTION_HPP
