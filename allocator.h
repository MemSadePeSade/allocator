#pragma once

#include "memorybuffer.h"
#include <type_traits>

template <typename T = void>
struct MyAllocator
{
	template <typename U> friend struct MyAllocator;
	
	using value_type = T;
	using pointer = T *;

	explicit MyAllocator(MemoryBuffer * a) : buffer(a) {}
	
	template<typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};
	
	template <typename U>
	MyAllocator(MyAllocator<U> const & rhs) : buffer(rhs.buffer) {}
	
	pointer allocate(std::size_t n)
	{
		return static_cast<pointer>(buffer->allocate(n * sizeof(T), alignof(T)));
	}

	void deallocate(pointer p, std::size_t n)
	{
		buffer->deallocate(p, n * sizeof(T));
	}
    
	template<typename U, typename ... Args>
	void construct(U *p, Args && ...args) 
	{
		new(p) U(std::forward<Args>(args)...);
	}
	
	template<typename U>
	void destroy(U *p)
	{
		p->~U();
	}

private:
	MemoryBuffer * buffer;
};


