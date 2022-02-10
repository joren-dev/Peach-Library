#ifndef PEACH_EXCEPTION_HPP
#define PEACH_EXCEPTION_HPP

#include "core/base_exception.hpp"
#include "core/prefix_manager.hpp"

#include "utils/exception_constants.hpp"
#include "utils/exception_format.hpp"

#include <iostream>
#include <source_location>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace peach
{
  // Short info:
  // * This has to be explicitly defined by the user inside the peach namespace
  // Link docu:
  enum class ExceptionTypes;

  // Short info:
  // * The method what() isnt templated in the base class, so we cannot override what()
  // * First ctor handles the case when std::source_location information is wanted, second does it without
  // Link docu:
  template< ExceptionTypes Val > class PeachException : virtual public detail::BaseException
  {
  public:
    template< typename... Tys >
    explicit PeachException( const std::source_location sl, Tys&&... args )
        : std::runtime_error { detail::format_error( sl.line( ), sl.file_name( ),
                                                     Prefix< Val >::get( ).get_prefix( ),
                                                     std::forward< Tys >( args )... ) }

    {
      m_err_msg = this->what( );
      m_prefix = Prefix< Val >::get( ).get_prefix( );
    }

    template< typename... Tys >
    explicit PeachException( Tys&&... args )
        : std::runtime_error { detail::format_error( detail::constants::kNoSourceLocation, "",
                                                     Prefix< Val >::get( ).get_prefix( ),
                                                     std::forward< Tys >( args )... ) }
    {
      m_err_msg = this->what( );
      m_prefix = Prefix< Val >::get( ).get_prefix( );
    }

    PeachException( const PeachException& ) noexcept = default;
    PeachException( PeachException&& ) noexcept = default;

    PeachException& operator=( PeachException&& ) = delete;
    PeachException& operator=( const PeachException& ) = delete;

    void print_to_console( ) const noexcept
    {
      // TODO: possibly determine if compiled application has a console available!
      std::cerr << m_prefix << R"(( " )" << m_err_msg.substr( 0, m_err_msg.size( ) - 2 )
                << R"( " ))" << '\n';
    }

    const std::string& what_str( ) const noexcept { return m_err_msg; }

    ~PeachException( ) = default;

  private:
    std::string m_err_msg;
    std::string m_prefix;
  };

  namespace detail
  {
    std::source_location
    get_source_location_details( const std::source_location sl = std::source_location::current()) noexcept;
  } // namespace detail

#define SL detail::get_source_location_details( )

} // namespace peach

#endif // PEACH_EXCEPTION_HPP
