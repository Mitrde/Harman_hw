#include <iostream>
#include <list>
#include<vector>
#include<future>

using namespace std;

template <typename T>
list<T> merge(list<T> && first, list<T> &&second)
{
	list<T> tmp;
	while (!first.empty() && !second.empty())
	{
		if (first.front() < second.front())
		{
			tmp.push_back(first.front());
			first.pop_front();
		}
		else
		{
			tmp.push_back(second.front());
			second.pop_front();
		}
	}
	if (!second.empty())
	{
		while (!second.empty())
		{
			tmp.push_back(second.front());
			second.pop_front();
		}
	}
	else
	{
		tmp.push_back(first.front());
		first.pop_front();
	}
	return tmp;
}

int main()
{
	int threads = 0;
	cout << "input amount of threads" << endl;
	cin >> threads;
	vector<future<list<int>>> results(threads);

	int num = 0;
	cout << "input amount of numbers" << endl;
	cin >> num;

	int tmp = 0;

	list<list<int>> tasks(num);

	for (auto &it : tasks)
	{
		cin >> tmp;
		it.push_back(tmp);
	}

	while (tasks.size() > 1)
	{
		int i = 0;

		for (; tasks.size() > 1 && i < threads; ++i)
		{
			auto tmp1 = tasks.front();
			tasks.pop_front();
			auto tmp2 = tasks.front();
			tasks.pop_front();
			results[i] = (async(std::launch::async, merge<int>, move(tmp1), move(tmp2)));
		}
		
		for (int j = 0; j < i; ++j)
			tasks.emplace_back(results[j].get());
		
	}

	for (auto it : tasks.front())
	{
		cout << it << " ";
	}
	cout << endl;



	system("pause");
	return 0;
}