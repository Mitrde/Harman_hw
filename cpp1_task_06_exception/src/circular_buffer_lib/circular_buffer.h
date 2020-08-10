#pragma once
#include <iterator>
#include <cassert>


template <class T1, class T2>
void construct(T1 *pT1, T2 &&rrT2)
{	         
	new (pT1) T1(std::forward <T2>(rrT2));
}

template <class T>
void destroy(T *pT)
{
	pT->~T();
}

template <class FwdIter>
void destroy(FwdIter first, FwdIter last)
{
	while (first != last)
	{
		destroy(&*first);
		++first;
	}
}

template<typename T>
class CircularIterator
	: public std::iterator<std::forward_iterator_tag, T>
{
	template <typename T>
	friend class ConstCircularIterator;
public:
	
	explicit CircularIterator(T* other, size_t size = 0)
		:pBegin(other), pCur(other), pEnd(other + size)
	{}

	CircularIterator<T> & operator=(const CircularIterator<T> & other)
	{
		pBegin = other.pBegin;
		pEnd = other.pEnd;
		pCur = other.pCur;
		return *this;
	}
	CircularIterator<T>(const CircularIterator<T>& other)
	{
		pBegin = other.pBegin;
		pEnd = other.pEnd;
		pCur = other.pCur;
	}

	CircularIterator& operator++()
	{
		if (++pCur > pEnd)
		{
			pCur = pBegin;
		}
		return *this;
	}

	T& operator*()
	{
		return *pCur;
	}

	T* operator->() const {
		return &(*pCur);
	}
	

	CircularIterator& operator--() {
		if (--pCur < pBegin)
		{
			pCur = pEnd;
		}
		return *this;
	}

	CircularIterator operator++(int) {
		T* tmp = pCur;
		if (++pCur > pEnd)
		{
			pCur = pBegin;
		}
		return *tmp;
	}

	CircularIterator operator--(int) {
		T* tmp = pCur;
		if (--pCur < pBegin)
		{
			pCur = pBegin;
		}
		return *tmp;
	}

	CircularIterator& operator+=(int n) {
		n %= pEnd - pBegin + 1;		
		if (n <= pEnd - pCur && n>= 0)
			pCur += n;
		else
		{
			if (n < 0)
				*this -= (-n);
			else
				pCur = pBegin + n - 1 - (pEnd - pCur);
		}
			
		return *this;
	}

	CircularIterator operator+(int n) const 
	{
		CircularIterator<T> tmp(*this);
		tmp += n;
		return tmp;
	}

	CircularIterator& operator-=( int n) {
		n %= pEnd - pBegin + 1;
		if (n <= pCur - pBegin && n>=0)
			pCur -= n;
		else
		{
			if (n < 0)
				*this += (-n);
			else
				pCur = pEnd - n + 1 + (pCur - pBegin);
				
		}

		return *this;
	}

	CircularIterator operator-(const int n) const {
		CircularIterator<T> tmp(*this);
		tmp -= n;
		return tmp;
	}


	T& operator[](const size_t n) const {
		T* tmp = pCur;
		if (n <= pEnd - pCur)
			tmp += n;
		else
		{
			tmp = pBegin + n % (pEnd - pCur);
		}

		return *(tmp);
	}

	bool operator==(const CircularIterator& other) const {
		return pCur == other.pCur;
	}

	bool operator!=(const CircularIterator& other) const {
		return pCur != other.pCur;
	}

	bool operator<(const CircularIterator& other) const {
		return pCur < other.pCur;
	}

	bool operator>(const CircularIterator& other) const {
		return pCur > other.pCur;
	}

	bool operator<=(const CircularIterator& other) const {
		return pCur <= other.pCur;
	}

	bool operator>=(const CircularIterator& other) const {
		return pCur >= other.pCur;
	}

	size_t operator+(const CircularIterator& other) const {
		return pCur + other.pCur;
	}

	size_t operator-(const CircularIterator& other) const {
		return pCur - other.pCur;
	}
	T* begin()
	{
		return pBegin;
	}
	T* end()
	{
		return pEnd;
	}
	T* getptr()
	{
		return pCur;
	}

private:
	T* pBegin;
	T* pEnd;
	T* pCur;
};

template<typename T>
class ConstCircularIterator
	: public std::iterator<std::forward_iterator_tag, T>
{
public:
	explicit ConstCircularIterator(T* other, size_t size = 0)
		:pBegin(other), pCur(other), pEnd(other + size)
	{}
	explicit ConstCircularIterator(const CircularIterator<T>& other)
		:pBegin(other.pBegin), pCur(other.pCur), pEnd(other.pEnd)
	{}

	ConstCircularIterator<T> & operator=(const ConstCircularIterator<T> & other)
	{
		pBegin = other.pBegin;
		pEnd = other.pEnd;
		pCur = other.pCur;
		return *this;
	}
	ConstCircularIterator<T>(const ConstCircularIterator<T>& other)
	{
		pBegin = other.pBegin;
		pEnd = other.pEnd;
		pCur = other.pCur;
	}

	ConstCircularIterator& operator++()
	{
		if (++pCur > pEnd)
		{
			pCur = pBegin;
		}
		return *this;
	}

	T& operator*()
	{
		return *pCur;
	}

	T* operator->() const {
		return &(*pCur);
	}


	ConstCircularIterator& operator--() {
		if (--pCur < pBegin)
		{
			pCur = pEnd;
		}
		return *this;
	}

	ConstCircularIterator operator++(int) {
		T* tmp = pCur;
		if (++pCur > pEnd)
		{
			pCur = pBegin;
		}
		return *tmp;
	}

	ConstCircularIterator operator--(int) {
		T* tmp = pCur;
		if (--pCur < pBegin)
		{
			pCur = pBegin;
		}
		return *tmp;
	}

	ConstCircularIterator& operator+=(int n) {
		n %= pEnd - pBegin + 1;
		if (n <= pEnd - pCur && n >= 0)
			pCur += n;
		else
		{
			if (n < 0)
				*this -= (-n);
			else
				pCur = pBegin + n - 1 - (pEnd - pCur);
		}

		return *this;
	}

	ConstCircularIterator operator+(int n) const
	{
		ConstCircularIterator<T> tmp(*this);
		tmp += n;
		return tmp;
	}

	ConstCircularIterator& operator-=(int n) {
		n %= pEnd - pBegin + 1;
		if (n <= pCur - pBegin && n >= 0)
			pCur -= n;
		else
		{
			if (n < 0)
				*this += (-n);
			else
				pCur = pEnd - n + 1 + (pCur - pBegin);

		}

		return *this;
	}

	ConstCircularIterator operator-(const int n) const {
		ConstCircularIterator<T> tmp(*this);
		tmp -= n;
		return tmp;
	}


	T& operator[](const size_t n) const {
		T* tmp = pCur;
		if (n <= pEnd - pCur)
			tmp += n;
		else
		{
			tmp = pBegin + n % (pEnd - pCur);
		}

		return *(tmp);
	}

	bool operator==(const ConstCircularIterator& other) const {
		return pCur == other.pCur;
	}

	bool operator!=(const ConstCircularIterator& other) const {
		return pCur != other.pCur;
	}

	bool operator<(const ConstCircularIterator& other) const {
		return pCur < other.pCur;
	}

	bool operator>(const ConstCircularIterator& other) const {
		return pCur > other.pCur;
	}

	bool operator<=(const ConstCircularIterator& other) const {
		return pCur <= other.pCur;
	}

	bool operator>=(const ConstCircularIterator& other) const {
		return pCur >= other.pCur;
	}

	size_t operator+(const ConstCircularIterator& other) const {
		return pCur + other.pCur;
	}

	size_t operator-(const ConstCircularIterator& other) const {
		return pCur - other.pCur;
	}
	const T* begin() const
	{
		return pBegin;
	}
	const T* end() const 
	{
		return pEnd;
	}
	const T* getptr() const
	{
		return pCur;
	}

private:
	T* pBegin;
	T* pEnd;
	T* pCur;
};

template <typename T>
class Impl
{
public: 
	Impl(const Impl &) = delete;
	Impl &operator = (const Impl &) = delete;
	size_t capacity, size;
	CircularIterator<T> pCur;
	size_t refs;	

	explicit Impl(size_t size = 0);
	~Impl();
	void swap(Impl &other) noexcept;
};




template<typename T>
class Circular_buffer
{
private:	
	static const size_t unshareable = static_cast <size_t> (-1);
	Impl<T> *m_pImpl;
		
	void size_clamp(size_t &size)
	{
		if (size > m_pImpl->capacity)
			size = m_pImpl->capacity;
	}
	//
	template <class T1>
	struct param_type
	{
		template <class T2>
		static const T2 &apply(const T2 &rcT)
		{
			return rcT;
		}
	};
	//
	template <class T1>
	struct param_type <T1 &&>
	{
		template <class T2>
		static T2 &&apply(T2 &&rrT)
		{
			return std::move(rrT);
		}
	};
	//
	template <class T1>	
	void copy_or_move(T1 &&other)
	{
		int min;
		min = m_pImpl->pCur.begin() - m_pImpl->pCur.end() > other->m_pImpl->size ?
			other->m_pImpl->size 
			: m_pImpl->pCur.begin() - m_pImpl->pCur.end();
		for (int i = 1; i <= min; ++i)
		{
			if (other->m_pImpl->pCur.getptr() < other->m_pImpl->pCur.begin() + other->m_pImpl->size)
			{
				construct(
					m_pImpl->pCur.getptr(),
					param_type <T1>::apply(*(other->m_pImpl->pCur + i)));
			}
			else 
			{
				construct(
					m_pImpl->pCur.getptr(),
					param_type <T1>::apply(*(other->m_pImpl->pCur.begin() + i - 1)));
			}
			++m_pImpl->pCur;
			
		}
		//m_pImpl->pCur = other->m_pImpl->pCur;		
		m_pImpl->size = other->m_pImpl->size;
	}
	//
	template <class T1>
	void push_copy_or_move(T1 &&rrT1)
	{
		if (m_pImpl->refs == 1 || m_pImpl->refs == unshareable)
		{
			construct(m_pImpl->pCur.getptr(), std::forward <T1>(rrT1));

			++m_pImpl->pCur;
			if(m_pImpl->pCur.getptr() < m_pImpl->pCur.begin() + m_pImpl->size)
				destroy(m_pImpl->pCur.getptr());
			size_clamp(++m_pImpl->size);
		}
		else
		{
			Circular_buffer<T> tmp(this->m_pImpl->capacity);
			tmp.copy_or_move(this);
			swap(tmp);

			construct(m_pImpl->pCur.getptr(), std::forward <T1>(rrT1));

			++m_pImpl->pCur;
			if (m_pImpl->pCur.getptr() < m_pImpl->pCur.begin() + m_pImpl->size)
				destroy(m_pImpl->pCur.getptr());
			size_clamp(++m_pImpl->size);
		}				
	}

public:
	explicit Circular_buffer(int capacity = 0) :
		m_pImpl(new Impl<T>(capacity))
	{}
	//
	Circular_buffer(const Circular_buffer &other)
	{
		//static_assert(
		//	std::is_copy_constructible <T>::value,
		//	"T must be copy constructible");
		std::cout << "Circular buffer copy ctor" << std::endl;
		if (other.m_pImpl->refs != unshareable)
		{
			m_pImpl = other.m_pImpl;
			++m_pImpl->refs;
		}
		else
		{			
			m_pImpl = new Impl<T>(other.m_pImpl->capacity);
			copy_or_move(&other); //////////////////////////////////////////
		}
			
	}
	
	Circular_buffer& operator=(Circular_buffer && other) noexcept
	{
		swap(other);
		return *this;
	}
	Circular_buffer& operator=(const Circular_buffer & other)  //+
	{
		std::cout << "Copy operator =" << std::endl;		
			
		
		if (other.m_pImpl->refs == unshareable)
		{
			Circular_buffer<T> tmp(other.m_pImpl->capacity);
			tmp.copy_or_move(&other);
			swap(tmp);
		}
		else
		{
			--m_pImpl->refs;
			delete m_pImpl;
			this->m_pImpl = other.m_pImpl;
			++m_pImpl->refs;
		}
			

		return *this;
	}

	~Circular_buffer()
	{
		if (m_pImpl->refs == unshareable || --m_pImpl->refs == 0)
			delete m_pImpl;
	}
	void reserve(int cap)
	{
		Circular_buffer<T> tmp(cap);
		tmp.copy_or_move(this);
		swap(tmp);		
	}
	void erase(T* it)////////////////////////////////////////////??????????????????????????????
	{
		/*if (m_pImpl->refs == 1)
		{
									
		}
		else
		{
			Circular_buffer<T> tmp(this->m_pImpl->capacity);
			tmp.copy_or_move(this);
			swap(tmp);

			construct(
				m_pImpl->pCur.getptr(), std::forward <T1>(rrT1));

			++m_pImpl->pCur;
			size_clamp(++m_pImpl->size);
		}

		Circular_buffer tmp(m_pImpl->capacity);
		
		int j = 0;
		for (size_t i = 0; i < m_pImpl->size; ++i)
		{
			if (m_pImpl->pArr + i != it)
			{
				construct(tmp.m_pImpl->pArr + j, *(m_pImpl->pArr + i));
				j++;
			}
		}
		tmp.m_pImpl->pCur = m_pImpl->pArr+m_pImpl->pCur < it ? m_pImpl->pCur
			: --m_pImpl->pCur;
		tmp.m_pImpl->size = --m_pImpl->size;
		swap(tmp);*/
		
	}
	void swap(Circular_buffer &other) noexcept
	{
		std::swap(other.m_pImpl, m_pImpl);
	}
	
	//const CircularIterator<T> begin() const
	//{
	//	return m_pImpl->pCur + 1;
	//}

	CircularIterator<T> begin() 
	{
		if (m_pImpl->refs != unshareable)
		{
			Circular_buffer<T> tmp(m_pImpl->capacity);
			tmp.copy_or_move(this);
			swap(tmp);
			m_pImpl->refs = unshareable;
		}
		if (m_pImpl->pCur.getptr() < m_pImpl->pCur.begin() + m_pImpl->size)// Is it full?
			return m_pImpl->pCur + 1;
		else
			return m_pImpl->pCur - (m_pImpl->pCur.getptr() - m_pImpl->pCur.begin());
	}
	CircularIterator<T> end() 
	{
		if (m_pImpl->refs != unshareable)
		{
			Circular_buffer<T> tmp(m_pImpl->capacity);
			tmp.copy_or_move(this);
			swap(tmp);
			m_pImpl->refs = unshareable;
		}
			return m_pImpl->pCur - 1;
	}
	ConstCircularIterator<T> cbegin()
	{		
		if (m_pImpl->pCur.getptr() < m_pImpl->pCur.begin() + m_pImpl->size)// Is it full?
			return ConstCircularIterator<T>(m_pImpl->pCur + 1);
		else
			return ConstCircularIterator<T>(m_pImpl->pCur - (m_pImpl->pCur.getptr() - m_pImpl->pCur.begin()));
	}
	ConstCircularIterator<T> cend()
	{		
		return ConstCircularIterator<T>(m_pImpl->pCur - 1);
	}

	size_t refs()
	{
		return m_pImpl->refs;
	}

	template <class T1>
	void push(T1 &&rrT, std::enable_if_t <std::is_move_constructible_v <std::remove_reference_t <T1>>>* = 0)
	{
		push_copy_or_move(std::move(rrT));
	}
	template <class T1>
	void push(const T1 &rcT, std::enable_if_t <std::is_copy_constructible_v <std::remove_reference_t <T1>>>* = 0)
	{
		push_copy_or_move(rcT);
	}
	
	int get_capacity()
	{
		return m_pImpl->capacity;
	}
	int get_size()
	{
		return m_pImpl->size;
	}	
};

template<class T> Impl<T>::Impl(size_t capacity)
	:pCur(static_cast <T*> (
	0 == capacity ? 0 : operator new ((capacity + 1) * sizeof(T))), capacity),
	size(0),	
	refs(1),
	capacity(capacity)
{}

template<typename T>
Impl<T>::~Impl()
{
	if (pCur.getptr() < pCur.begin() + size) //is Full
		::destroy(pCur + 1, pCur - 1);
	else                                     //isn't Full
		::destroy(pCur.begin(), pCur.begin() + size);

	operator delete (pCur.begin());
}

template<typename T>
void Impl<T>::swap(Impl & other) noexcept
{	
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
	std::swap(pCur, other.pCur);
	std::swap(refs, other.refs);
}
