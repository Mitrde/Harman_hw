#pragma once

template <class T1, class T2>
void construct(T1 *pT1, T2 &&rrT2)
{
	new (pT1) T1(rrT2);
}

template <class T>
void destroy(T *pT)
{
	pT->~T();
}

template <class FwdIter>
void destroy(
	FwdIter first, FwdIter last)
{
	while (first != last)
	{
		destroy(&*first);
		++first;
	}
}





template<typename T>
class Circular_buffer
{
private:
	void clamp(int &pCur)
	{
		if (pCur >= capacity)
			pCur = 0;
	}
	void size_clamp(int &size)
	{
		if (size > capacity)
			size = capacity;
	}
	int capacity;
	T* pArr;
	int pCur;
	int size;
	using iterator = T * ;

public:
	Circular_buffer(int capacity_ = 0) : capacity(capacity_)
	{
		pCur = 0;
		size = 0;
		pArr = static_cast <T *> (0 == capacity ? 0 :
			operator new (capacity * sizeof(T)));
	}
	Circular_buffer(const Circular_buffer &other)
	{
		pCur = 0;
		capacity = other.capacity;
		size = other.size;
		pArr = static_cast <T *> (0 == capacity ? 0 : operator new (capacity * sizeof(T)));
		for (int i = 0; i < capacity; i++)
		{
			this->push(*(other.pArr + this->pCur));
		}
		this->pCur = other.pCur;
	}
	Circular_buffer(Circular_buffer && other) noexcept
	{
		swap(other);
	}
	Circular_buffer& operator=(Circular_buffer && other) noexcept
	{
		swap(other);
		return *this;
	}
	Circular_buffer& operator=(const Circular_buffer & other)
	{
		T* tmp = static_cast <T *> (0 == other.capacity ? 0
			: operator new (other.capacity * sizeof(T)));

		for (int i = 0; i < other.size; i++)
		{
			construct(&tmp[i], std::move(*(other.pArr + i)));
		}
		delete[] this->pArr;
		this->pArr = tmp;
		this->capacity = other.capacity;
		this->size = other.size;
		this->pCur = other.pCur;
		return *this;
	}
	void reserve(int cap)
	{
		T* tmp = static_cast <T *> (0 == cap ? 0
			: operator new (cap * sizeof(T)));

		for (int i = 0; i < cap; i++)
		{
			construct(&tmp[i], move(*(pArr + i)));
		}
		delete[] pArr;
		pArr = tmp;
		capacity = cap;
		clamp(pCur);
		size_clamp(size);
	}
	void erase(T* it)
	{
		T* tmp = static_cast <T *> (0 == (capacity - 1) ? 0
			: operator new ((capacity - 1) * sizeof(T)));
		int j = 0;
		for (int i = 0; i < size; i++)
		{
			if (pArr + i != it)
			{
				construct(&tmp[j], move(*(pArr + i)));
				j++;
			}
		}
		delete[] pArr;
		pArr = tmp;
		capacity--;
		size--;
		clamp(pCur);
	}
	void swap(Circular_buffer &other) noexcept
	{
		std::swap(pCur, other.pCur);
		std::swap(capacity, other.capacity);
		std::swap(size, other.size);
		std::swap(pArr, other.pArr);
	}
	iterator begin() const noexcept
	{
		return pArr;
	}
	iterator end() const noexcept
	{
		return pArr + size;
	}
	void print() const noexcept
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << *(pArr + i) << " ";
		}
		std::cout << std::endl;
	}
	void push(const T &rcT/*, std::enable_if_t <std::is_copy_constructible_v <std::remove_reference_t <T>>> **/)
	{
		construct(pArr + pCur, std::forward <const T>(rcT));
		clamp(++pCur);
		size_clamp(++size);
	}
	void push(T &&rrT/*, std::enable_if_t <std::is_move_constructible_v <std::remove_reference_t <T>>> **/)
	{
		construct(pArr + pCur, std::forward <T>(rrT));
		clamp(++pCur);
		size_clamp(++size);
	}
	int get_capacity()
	{
		return capacity;
	}
	int get_size()
	{
		return size;
	}
	~Circular_buffer()
	{
		::destroy(pArr, pArr + size);
		operator delete (pArr);
	}
};

