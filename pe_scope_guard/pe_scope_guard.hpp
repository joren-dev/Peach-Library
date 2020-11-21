#ifndef PE_SCOPE_GUARD_HPP
#define PE_SCOPE_GUARD_HPP

#include <concepts>
#include <tuple>
#include <type_traits>
#include <utility>

namespace peach
{

  template< typename... Tys > class ScopeGuard
  {
  public:
    constexpr ScopeGuard( Tys... callables ) requires( ( std::same_as< std::invoke_result_t< Tys >, void > && ... ) )
        : m_callables( std::make_tuple( callables... ) )
    {
    }

    ~ScopeGuard( ) noexcept
    {
      std::apply( []( auto&&... args ) { ( ( args( ) ), ... ); }, m_callables );
    }

  private:
    std::tuple< Tys... > m_callables;
  };

} // namespace peach

#endif // PE_SCOPE_GUARD_HPP
