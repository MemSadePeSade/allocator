#pragma once

#include <memory>
#include <type_traits>

template <typename T, typename Alloc = std::allocator<T>>
class MyContainer
{
public:
	using value_type = T;
	using allocator_type = Alloc;

private:
	using traits = std::allocator_traits<allocator_type>;
	using pointer = typename traits::pointer;

public:
	using size_type = typename traits::size_type;

private:
	struct representation : allocator_type
	{
		pointer data;
		size_type capacity;

		size_type size;

		explicit representation(allocator_type const & a, size_type n)
			: allocator_type(a), capacity(n), size(0) {}
	};

	representation r;
	
	void internal_clear() noexcept
	{
		if (empty()) { return; }

		allocator_type & a = r;

		for (size_type i = 0; i != size(); ++i)
		{
			size_type k = size() - i - 1;
			traits::destroy(a, data() + k);
		}

		traits::deallocate(a, r.data, capacity());
	}

public:
	value_type       * data()       noexcept { return std::addressof(*r.data); }

	size_type size() const noexcept { return r.size; }
	size_type capacity() const noexcept { return r.capacity; }
	
	bool empty() const noexcept { return r.size == 0; }

	// Construct new container from scratch
	explicit MyContainer(size_type n)
		: MyContainer(allocator_type(), n) {}

	MyContainer(allocator_type const & alloc, size_type n)
		: r(alloc, n)
	{
		allocator_type & a = r;
		pointer p = traits::allocate(a, capacity());
		
		r.data = p;
	}

	void push_back(const value_type& val) 
	{
		allocator_type & a = r;
	
		if ( r.size < r.capacity)
		{
			traits::construct(a, std::addressof(*r.data) + size(), val);
			r.size = r.size+1;
		}
	}
	
	// Destructor
	~MyContainer()
	{
		internal_clear();
	}

	class iterator
	{
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		iterator(pointer ptr) : ptr_(ptr) { }
		self_type operator++() { self_type i = *this; ptr_++; return i; }
		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }
		bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
	private:
		pointer ptr_;
	};

	iterator begin()
	{
		return iterator(r.data);
	}

	iterator end()
	{
		return iterator(r.data + size());
	}
};