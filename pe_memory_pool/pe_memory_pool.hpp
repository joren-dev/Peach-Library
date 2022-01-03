#ifndef PE_MEMORY_POOL_HPP
#define PE_MEMORY_POOL_HPP

#include <cstdint>
#include <memory>
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

    template <typename T>
    class PoolIterator
    {
    public:
      explicit PoolIterator(const size_t index) : index_(index)
      {}

    private:
      size_t index_;

      friend MemoryPool;
    };

    /// <summary>
    /// Allocates the object with the given arguments in the pool.
    /// The user is obligated to destruct the object if necessary using the Destruct function
    /// </summary>
    /// <typeparam name="T">Type of the object to be allocated</typeparam>
    /// <typeparam name="...Args"></typeparam>
    /// <param name="...args">Params to pass to the objects constructor</param>
    /// <returns>Index of the created object</returns>
    template< typename T, typename... Args > PoolIterator<T> Allocate( Args&&... args ) requires std::is_destructible_v< T >
    {
      if ( const size_t required_size = current_size_ + sizeof( T ); required_size > max_size_ )
      {
        const size_t new_size = max_size_ * 2;
        reallocate( new_size < required_size ? required_size : new_size );
      }

      pointer_.emplace_back( std::make_unique<MemoryPoolEntry< T > >( reinterpret_cast< uintptr_t* >(
          new ( reinterpret_cast< T* >( start_ + current_size_ ) ) T { std::forward< Args >( args )... } ) ) );

      current_size_ += sizeof( T );

      return PoolIterator<T>{ pointer_.size( ) - 1 };
    }

    /// <summary>
    /// Get a reference to the object associated with the index
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="index">Index of the object to return a reference to</param>
    /// <returns></returns>
    template< typename T > [[nodiscard]] T& Get( const PoolIterator<T>& it )
    {
      if ( it.index_ >= pointer_.size( ) )
        throw std::out_of_range( "" );

      return ( dynamic_cast< MemoryPoolEntry< T >* >( pointer_[ it.index_ ].get() ) )->Get( );
    }

    template< typename T > [[nodiscard]] const T& Get( const PoolIterator<T>& it ) const
    {
      if ( it.index_ >= pointer_.size( ) )
        throw std::out_of_range( "" );

      //return *reinterpret_cast< T* >( pointer_[ index ] );
      return ( dynamic_cast< const MemoryPoolEntry< T >* >( pointer_[ it.index_ ].get() ) )->Get( );
    }

    /// Calls the destructor of the object associated with the index
    /// \tparam T
    /// \param index Index of the object to call the destructor of
    template< typename T > void Destruct( const size_t index )
    {
      //static_assert( std::is_class_v< T >, "Calling destructor on non-class type(T) is illegal." );
      ( reinterpret_cast< T* >( pointer_[ index ] ) )->~T( );
    }

    template< typename T > void Destruct( const PoolIterator<T>&& it ) // pls gib iterator
    {
      //static_assert( std::is_class_v< T >, "Calling destructor on non-class type(T) is illegal." );
      (&( dynamic_cast< MemoryPoolEntry< T >* >( pointer_[ it.index_ ].get() ) )->Get())->~T( ); // uhm... idk if this is good code
    }

  private:
    class MemoryPoolEntryBase
    {
    public:
      explicit MemoryPoolEntryBase( uintptr_t* pointer );

      virtual ~MemoryPoolEntryBase( ) = 0;

      [[nodiscard]] uintptr_t*& GetPointer( ) noexcept;

      [[nodiscard]] const uintptr_t* const & GetPointer( ) const noexcept;

    private:
      uintptr_t* ptr_;
    };

    template< typename T > class MemoryPoolEntry : public MemoryPoolEntryBase
    {
    public:
      explicit MemoryPoolEntry( uintptr_t* pointer ) : MemoryPoolEntryBase( pointer ) {}

      ~MemoryPoolEntry( ) override = default;

      [[nodiscard]] T& Get( ) noexcept { return *reinterpret_cast< T* >( GetPointer( ) ); }

      [[nodiscard]] const T& Get( ) const noexcept { return *reinterpret_cast< const T* >( GetPointer( ) ); }
    };

    size_t max_size_ { };
    size_t current_size_ { };

    uintptr_t start_ { };
    std::vector< std::unique_ptr<MemoryPoolEntryBase> > pointer_;

    void reallocate( size_t new_size );
  };
} // namespace peach

#endif // PE_MEMORY_POOL_HPP
