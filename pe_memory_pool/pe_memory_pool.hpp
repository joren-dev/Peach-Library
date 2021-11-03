#ifndef PE_MEMORY_POOL_HPP
#define PE_MEMORY_POOL_HPP

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace peach
{
  /// <summary>
  /// A memory pool to allow for homogenous allocation on the heap
  /// </summary>
  class MemoryPool
  {
  public:
    MemoryPool( ) = default;
    explicit MemoryPool( size_t initial_size );

    ~MemoryPool( );

    /// <summary>
    /// Allocates the object with the given arguments in the pool.
    /// The user is obligated to destruct the object if necessary using the Destruct function
    /// </summary>
    /// <typeparam name="T">Type of the object to be allocated</typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <param name="...args">Params to pass to the objects constructor</param>
    /// <returns>Index of the created object</returns>
    template< typename T, typename... Args > size_t Allocate( Args&&... args )  requires std::is_destructible_v< T >
    {
      if ( const size_t required_size = current_size_ + sizeof( T ); required_size > max_size_ )
      {
        const size_t new_size = max_size_ * 2;
        reallocate( new_size < required_size ? required_size : new_size );
      }

      pointer_.push_back( reinterpret_cast< uintptr_t* >( new ( reinterpret_cast< T* >( start_ + current_size_ ) )
                                                              T{ std::forward< Args >( args )... } ) );

      current_size_ += sizeof( T );

      return pointer_.size( ) - 1;
    }

    /// <summary>
    /// Get a reference to the object associated with the index
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="index">Index of the object to return a reference to</param>
    /// <returns></returns>
    template< typename T > [[nodiscard]] T& Get( const size_t index )
    {
      if ( index >= pointer_.size( ) )
        throw std::out_of_range( "" );

      return *reinterpret_cast< T* >( pointer_[ index ] );
    }

    template< typename T > [[nodiscard]] const T& Get( const size_t index ) const
    {
      if ( index >= pointer_.size( ) )
        throw std::out_of_range( "" );

      return *reinterpret_cast< T* >( pointer_[ index ] );
    }

    /// <summary>
    /// Calls the destructor of the object associated with the index
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="index">Index of the object to call the destructor of</param>
    template< typename T > void Destruct( const size_t index )
    {
      //static_assert( std::is_class_v< T >, "Calling destructor on non-class type(T) is illegal." );
      ( reinterpret_cast< T* >( pointer_[ index ] ) )->~T( );
    }

  private:
    size_t max_size_ { };
    size_t current_size_ { };

    uintptr_t start_ { };
    std::vector< uintptr_t* > pointer_;

    void reallocate( size_t new_size );
  };
} // namespace peach

#endif // PE_MEMORY_POOL_HPP
