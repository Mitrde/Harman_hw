#pragma once

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

public:
	Circular_buffer(int capacity_ = 0) : capacity(capacity_)
	{
		pCur = 0;
		size = 0;
		pArr = new T[capacity];
	}
	Circular_buffer(const Circular_buffer &other)
	{
		this->pCur = 0;
		this->capacity = other.capacity;
		this->size = other.size;
		this->pArr = new T[capacity];
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
		T* tmp = new T[other.capacity];

		for (int i = 0; i < other.size; i++)
		{
			tmp[i] = (*(other.pArr + i));
		}
		delete[] this->pArr;
		this->pArr = tmp;
		this->capacity = other.capacity;
		this->size = other.size;
		this->pCur = other.pCur;
	}
	void reserve(int cap)
	{
		T* tmp = new T[cap];
		int j = 0;
		for (int i = 0; i < size; i++)
		{
			tmp[i] = *(pArr + i);
		}
		delete[] pArr;
		pArr = tmp;
		capacity = cap;
		clamp(pCur);
		size_clamp(size);
	}
	void erase(T* it)
	{
		T* tmp = new T[capacity - 1];
		int j = 0;
		for (int i = 0; i < capacity; i++)
		{
			if (pArr + i != it)
			{
				tmp[j] = *(pArr + i);
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
	T* begin() const noexcept
	{
		return pArr;
	}
	void print() const noexcept
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << *(pArr + i) << " ";
		}
		std::cout << std::endl;
	}
	void push(T& data)
	{
		*(pArr + pCur) = data;
		clamp(++pCur);
		size_clamp(++size);
	}
	void push(T&& data)
	{
		*(pArr + pCur) = data;
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
		delete[] pArr;
	}
};