#include "pe_memory_pool.hpp"

#include <cstdlib>
#include <stdexcept>

namespace peach
{
  MemoryPool::MemoryPool( const size_t initial_size )
      : max_size_( initial_size ), current_size_( 0 ), start_( reinterpret_cast< uintptr_t >( std::malloc( initial_size ) ) )
  {
    if ( start_ == 0 )
      throw std::runtime_error( "" );
  }

  MemoryPool::~MemoryPool( ) { std::free( reinterpret_cast< void* >( start_ ) ); }

  void MemoryPool::reallocate( const size_t new_size )
  {
    const uintptr_t old_start { start_ };
    if ( void* const new_start = std::realloc( reinterpret_cast< void* >( start_ ), new_size ); new_start != nullptr )
      start_ = reinterpret_cast< uintptr_t >( new_start );
    else
      throw std::runtime_error( "" );

    max_size_ = new_size;
    for ( uintptr_t*& i : pointer_ )
    {
      uintptr_t offset { (uintptr_t)((uintptr_t)i - (uintptr_t)old_start) };
      i = reinterpret_cast< uintptr_t* >( start_ + offset );
    }

  }
} // namespace peach
