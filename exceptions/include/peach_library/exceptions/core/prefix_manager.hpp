#ifndef PEACH_PREFIX_MANAGER_HPP
#define PEACH_PREFIX_MANAGER_HPP

#include <string>

namespace peach
{
  enum class ExceptionTypes;
} // namespace peach

namespace peach
{

  // Short info:
  // * Provides general way to set default prefix
  // Link docu:
  class PrefixManager
  {
  public:
    PrefixManager( ) noexcept = default;

    PrefixManager( const PrefixManager& ) noexcept = delete;
    PrefixManager( PrefixManager&& ) noexcept = delete;

    PrefixManager& operator=( PrefixManager&& ) = delete;
    PrefixManager& operator=( const PrefixManager& ) = delete;

    // clang-format off
    static void set_default_prefix( const std::string& prefix ) noexcept
    { 
        m_default_prefix = prefix; 
    }
    // clang-format on

    inline static std::string m_default_prefix = { "LOG" };

    ~PrefixManager( ) noexcept = default;
  };

  // Short info:
  // * Defines and manages a prefix for each specific ExceptionType
  // Link docu:
  template< ExceptionTypes V > class Prefix : private PrefixManager
  {
  public:
    static Prefix& get( ) noexcept
    {
      static Prefix< V > instance { };
      return instance;
    }

    Prefix( ) noexcept = default;

    Prefix( const Prefix& ) noexcept = delete;
    Prefix( Prefix&& ) noexcept = delete;

    Prefix& operator=( Prefix&& ) = delete;
    Prefix& operator=( const Prefix& ) = delete;

    // clang-format off
    void set_prefix( const std::string& prefix ) noexcept 
    { 
      m_prefix = prefix; 
    }

    std::string get_prefix( ) const noexcept
    {
      if ( m_prefix.empty( ) )
        return m_default_prefix;

      return m_prefix;
    }
    // clang-format on

    std::string m_prefix;

    ~Prefix( ) noexcept = default;
  };

} // namespace peach

#endif // PEACH_PREFIX_MANAGER_HPP
