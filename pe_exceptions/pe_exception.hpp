#ifndef PE_EXCEPTION_HPP
#define PE_EXCEPTION_HPP

#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>

namespace peach
{
  class pe_fatal_error;
  inline std::ostream& operator<<( std::ostream& stream, [[maybe_unused]] const pe_fatal_error& ec );

  template< typename T > concept OutputStreamInsertable = requires( std::ostream& os, const T& arg )
  {
    {
      os << arg
    }
    ->std::convertible_to< std::ostream& >;
  };

  template< OutputStreamInsertable... Tys >
  std::string format_error( const size_t line_num, const std::string& file_name, Tys&&... args )
  {
    std::stringstream ss { };
    ( ( ss << std::forward< Tys >( args ) << " " ), ... );
    return ss.str( );
  }

  class pe_fatal_error : public std::runtime_error
  {
  public:
    template< typename... Tys >
    explicit pe_fatal_error( const size_t line_num, const std::string& file_name, Tys&&... args )
        : std::runtime_error { format_error( line_num, file_name, std::forward< Tys >( args )... ) }
    {
    }

    pe_fatal_error( const pe_fatal_error& ) noexcept = default;

    pe_fatal_error( pe_fatal_error&& ) noexcept = delete;

    pe_fatal_error& operator=( pe_fatal_error&& ) = delete;

    pe_fatal_error& operator=( const pe_fatal_error& ) = delete;

    ~pe_fatal_error( ) = default;
  };

  inline std::ostream& operator<<( std::ostream& stream, [[maybe_unused]] const pe_fatal_error& ec ) { return stream; }

  template< typename... Tys >
  pe_fatal_error throw_exception( const size_t line_num, const std::string file_name, Tys&&... err_message )
  {
    return pe_fatal_error( line_num, file_name, std::forward< Tys >( err_message )... );
  }

#define Exception( ... ) throw_exception( __LINE__, __FILE__, ##__VA_ARGS__ )

} // namespace peach

#endif //PE_EXCEPTION_HPP
