#ifndef __ZZ_FIXEDARRAY_H__
#define __ZZ_FIXEDARRAY_H__
#pragma once
#include <cstddef>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#if defined(WIN32) || defined(_WIN64)
#define ZZ_PLATFORM_WINDOWS
#endif
#ifdef ZZ_PLATFORM_WINDOWS
#pragma warning(push)
#pragma warning(disable:4996)
//#pragma warning(disable:4510)
//#pragma warning(disable:4610)
#endif

namespace zz_engine
{
	template<class T, std::size_t N>
	class fixedarray {
	private:
		T elems[N];

	public:
		typedef T              value_type;
		typedef T*             iterator;
		typedef const T*       const_iterator;
		typedef T&             reference;
		typedef const T&       const_reference;
		typedef std::size_t    size_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator        begin()       { return elems; }
		const_iterator  begin() const { return elems; }
		const_iterator cbegin() const { return elems; }
		iterator        end()       { return elems+N; }
		const_iterator  end() const { return elems+N; }
		const_iterator cend() const { return elems+N; }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}
		const_reverse_iterator crbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}
		const_reverse_iterator crend() const {
			return const_reverse_iterator(begin());
		}

		reference operator[](size_type i)
		{
			rangecheck(i);
			return elems[i];
		}
		const_reference operator[](size_type i) const
		{
			rangecheck(i);
			return elems[i];
		}

		reference at(size_type i) { rangecheck(i); return elems[i]; }
		const_reference at(size_type i) const { rangecheck(i); return elems[i]; }

		reference front()
		{
			return elems[0];
		}

		const_reference front() const
		{
			return elems[0];
		}

		reference back()
		{
			return elems[N-1];
		}

		const_reference back() const
		{ 
			return elems[N-1];
		}

		static size_type size() { return N; }
		static bool empty() { return false; }
		static size_type max_size() { return N; }
		enum { static_size = N };

		//linear complexity
		void swap (fixedarray<T,N>& y) {
			for (size_type i = 0; i < N; ++i)
				std::swap(elems[i],y.elems[i]);
		}

		template <typename T2>
		fixedarray<T,N>& operator= (const fixedarray<T2,N>& rhs) {
			std::copy(rhs.begin(),rhs.end(), begin());
			return *this;
		}

		void assign (const T& value) { fill ( value ); }
		void fill   (const T& value) {
			std::fill_n(begin(),size(),value);
		}

	private:
		const T* data() const { return elems; }
		T* data() { return elems; }
		T* c_array() { return elems; }
		static void rangecheck (size_type i) {
			if (i >= size()) {
				char szbuff[256]={0};
#ifdef ZZ_PLATFORM_WINDOWS
				_snprintf_s( szbuff, sizeof(szbuff), _TRUNCATE, "[fixedarray<>:index=%u out of range=%u][%s][%d][%s]\n", (unsigned int)i, (unsigned int)size(), __FILE__, __LINE__, __FUNCTION__);
#else
				snprintf( szbuff, sizeof(szbuff), "[fixedarray<>:index=%u out of range=%u][%s][%d][%s]\n", (unsigned int)i, (unsigned int)size(), __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
				std::out_of_range e(szbuff);
				throw e;
			}
		}
	};

	template<std::size_t N>
	class fixedarray<char, N>{
	public:
		//extra construct
		fixedarray<char, N>()
		{
			memset(elems,'\0',sizeof(elems));
		}
	private:
		char elems[N];

	public:
		typedef char              value_type;
		typedef char*             iterator;
		typedef const char*       const_iterator;
		typedef char&             reference;
		typedef const char&       const_reference;
		typedef std::size_t    size_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator        begin()       { return elems; }
		const_iterator  begin() const { return elems; }
		const_iterator cbegin() const { return elems; }
		iterator        end()       { return elems+N; }
		const_iterator  end() const { return elems+N; }
		const_iterator cend() const { return elems+N; }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}
		const_reverse_iterator crbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}
		const_reverse_iterator crend() const {
			return const_reverse_iterator(begin());
		}

		reference operator[](size_type i) 
		{
			rangecheck(i);
			return elems[i];
		}
		const_reference operator[](size_type i) const
		{
			rangecheck(i);
			return elems[i];
		}

		reference at(size_type i) { rangecheck(i); return elems[i]; }
		const_reference at(size_type i) const { rangecheck(i); return elems[i]; }

		reference front()
		{ 
			return elems[0];
		}

		const_reference front() const
		{
			return elems[0];
		}

		reference back()
		{ 
			return elems[N-1];
		}

		const_reference back() const 
		{ 
			return elems[N-1]; 
		}

		static size_type size() { return N; }
		static bool empty() { return false; }
		static size_type max_size() { return N; }
		enum { static_size = N };

		//linear complexity
		void swap (fixedarray<char,N>& y) {
			for (size_type i = 0; i < N; ++i)
				std::swap(elems[i],y.elems[i]);
		}

		fixedarray<char,N>& operator= (const fixedarray<char,N>& rhs) {
			std::copy(rhs.begin(),rhs.end(), begin());
			return *this;
		}

		void assign (const char& value) { fill ( value ); }
		void fill   (const char& value) {
			std::fill_n(begin(),size(),value);
		}

		//extra methods
		const char* formatstring(const char* fmt, ...)
		{
			if (!fmt)
			{
				elems[N-1] = '\0';
				return elems;
			}
			try
			{
				va_list ap;
				va_start(ap, fmt);
#ifdef ZZ_PLATFORM_WINDOWS
				_vsnprintf_s(elems, N, _TRUNCATE, fmt, ap);
#else
				vsnprintf(elems, N, fmt, ap);
#endif
				va_end(ap);
			}
			catch(...)
			{

			}
			elems[N-1] = '\0';
			return elems;
		}

		const char* appendformatstring(const char* fmt, ...)
		{
			if (!fmt)
			{
				elems[N-1]='\0';
				return elems;
			}
			try
			{
				size_type length = strnlen(elems,size());
				if (length>=N)
				{
					elems[N-1]='\0';
					return elems;
				}
				va_list ap;
				va_start(ap, fmt);
#ifdef ZZ_PLATFORM_WINDOWS
				_vsnprintf_s(elems+length, N-length, _TRUNCATE, fmt, ap);
#else
				vsnprintf(elems+length, N-length, fmt, ap);
#endif
				va_end(ap);
			}
			catch(...)
			{

			}
			elems[N-1] = '\0';
			return elems;
		}

		const char* appendstring(const char* str)
		{
			if (!str)
			{
				elems[N-1]='\0';
				return elems;
			}
			return appendformatstring("%s",str);
		}

		const char* getstring( ) const
		{
			if (elems[N-1] != '\0')
			{
				return "";
			}
			return elems;
		}

	private:
		const char* data() const { return elems; }
		char* data() { return elems; }
		char* c_array() { return elems; }
		static void rangecheck (size_type i) {
			if (i >= size()) {
				char szbuff[256]={0};
#ifdef ZZ_PLATFORM_WINDOWS
				_snprintf_s( szbuff, sizeof(szbuff), _TRUNCATE "[fixedarray<>:index=%u out of range=%u][%s][%d][%s]\n", (unsigned int)i, (unsigned int)size(), __FILE__, __LINE__, __FUNCTION__);
#else
				snprintf( szbuff, sizeof(szbuff), "[fixedarray<>:index=%u out of range=%u][%s][%d][%s]\n", (unsigned int)i, (unsigned int)size(), __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
				std::out_of_range e(szbuff);
				throw e;
			}
		}
	};

	template< class T >
	class fixedarray< T, 0 > {
	public:
		typedef T              value_type;
		typedef T*             iterator;
		typedef const T*       const_iterator;
		typedef T&             reference;
		typedef const T&       const_reference;
		typedef std::size_t    size_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator        begin()       { return       iterator( reinterpret_cast<       T * >( this ) ); }
		const_iterator  begin() const { return const_iterator( reinterpret_cast< const T * >( this ) ); }
		const_iterator cbegin() const { return const_iterator( reinterpret_cast< const T * >( this ) ); }
		iterator        end()       { return  begin(); }
		const_iterator  end() const { return  begin(); }
		const_iterator cend() const { return cbegin(); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}
		const_reverse_iterator crbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}
		const_reverse_iterator crend() const {
			return const_reverse_iterator(begin());
		}

		reference operator[](size_type /*i*/)
		{
			return failed_rangecheck();
		}
		const_reference operator[](size_type /*i*/) const
		{
			return failed_rangecheck();
		}
		reference at(size_type /*i*/)               {   return failed_rangecheck(); }
		const_reference at(size_type /*i*/) const   {   return failed_rangecheck(); }

		reference front()
		{
			return failed_rangecheck();
		}
		const_reference front() const
		{
			return failed_rangecheck();
		}
		reference back()
		{
			return failed_rangecheck();
		}
		const_reference back() const
		{
			return failed_rangecheck();
		}

		static size_type size() { return 0; }
		static bool empty() { return true; }
		static size_type max_size() { return 0; }
		enum { static_size = 0 };

		void swap (fixedarray<T,0>& /*y*/) {
		}

		template <typename T2>
		fixedarray<T,0>& operator= (const fixedarray<T2,0>& ) {
			return *this;
		}

		void assign (const T& value) { fill ( value ); }
		void fill   (const T& ) {}

	private:
		const T* data() const { return 0; }
		T* data() { return 0; }
		T* c_array() { return 0; }
		static reference failed_rangecheck () {
			char szbuff[256]={0};
#ifdef ZZ_PLATFORM_WINDOWS
			_snprintf( szbuff, sizeof(szbuff), "[attempt to access element of an empty fixedarray[%s][%d][%s]\n", __FILE__, __LINE__, __FUNCTION__) ;
#else
			snprintf( szbuff, sizeof(szbuff), "[attempt to access element of an empty fixedarray[%s][%d][%s]\n", __FILE__, __LINE__, __PRETTY_FUNCTION__) ;
#endif
			std::out_of_range e(szbuff);
			throw e;
		}
	};

	// comparisons
	template<class T, std::size_t N>
	bool operator== (const fixedarray<T,N>& x, const fixedarray<T,N>& y) {
		return std::equal(x.begin(), x.end(), y.begin());
	}
	template<class T, std::size_t N>
	bool operator< (const fixedarray<T,N>& x, const fixedarray<T,N>& y) {
		return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
	}
	template<class T, std::size_t N>
	bool operator!= (const fixedarray<T,N>& x, const fixedarray<T,N>& y) {
		return !(x==y);
	}
	template<class T, std::size_t N>
	bool operator> (const fixedarray<T,N>& x, const fixedarray<T,N>& y) {
		return y<x;
	}
	template<class T, std::size_t N>
	bool operator<= (const fixedarray<T,N>& x, const fixedarray<T,N>& y) {
		return !(y<x);
	}
	template<class T, std::size_t N>
	bool operator>= (const fixedarray<T,N>& x, const fixedarray<T,N>& y) {
		return !(x<y);
	}

	// global swap()
	template<class T, std::size_t N>
	inline void swap (fixedarray<T,N>& x, fixedarray<T,N>& y) {
		x.swap(y);
	}
}
#ifdef ZZ_PLATFORM_WINDOWS
# pragma warning(pop)
#endif
using namespace zz_engine;
#endif