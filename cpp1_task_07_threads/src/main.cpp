#include <iostream>
#include <list>
#include<vector>
#include<future>
#include <condition_variable>
#include <functional>
#include <thread>
#include <queue>

using namespace std;


class ThreadPool
{
public:
	using Task = std::function<void()>;

	explicit ThreadPool(std::size_t numThreads)
	{
		start(numThreads);
	}

	~ThreadPool()
	{
		stop();
	}

	template<class T>
	auto enqueue(T task)->std::future<decltype(task())>
	{
		auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>(std::move(task));

		{
			std::unique_lock<std::mutex> lock{ mEventMutex };
			cout << "task added" << endl;
			mTasks.emplace([=] {
				(*wrapper)();
			});
		}

		mEventVar.notify_one();
		return wrapper->get_future();
	}

private:
	std::vector<std::thread> mThreads;

	std::condition_variable mEventVar;

	std::mutex mEventMutex;
	bool mStopping = false;

	std::queue<Task> mTasks;

	void start(std::size_t numThreads)
	{
		for (auto i = 0u; i < numThreads; ++i)
		{
			mThreads.emplace_back([=] {
				while (true)
				{
					Task task;

					{
						std::unique_lock<std::mutex> lock{ mEventMutex };

						mEventVar.wait(lock, [=] { return mStopping || !mTasks.empty(); });

						if (mStopping && mTasks.empty())
							break;

						task = std::move(mTasks.front());
						mTasks.pop();
						//cout << "task poped" << endl;
					}

					task();
					
				}
			});
		}
	}

	void stop() noexcept
	{
		{
			std::unique_lock<std::mutex> lock{ mEventMutex };
			mStopping = true;
		}

		mEventVar.notify_all();

		for (auto &thread : mThreads)
			thread.join();
	}
};
//
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
	while (!second.empty())
	{
		tmp.push_back(second.front());
		second.pop_front();
	}
	while (!first.empty())
	{
		tmp.push_back(first.front());
		first.pop_front();
	}
	for (auto it : tmp)
		cout << it << " ";
	cout << endl;
	return tmp;
}

//

int main()
{
	std::mutex glb_mtx;
	int threads = 0;
	using type = int;


	cout << "input amount of threads" << endl;
	cin >> threads;
	ThreadPool pool(threads);

	
	

	int num = 0;
	cout << "input amount of numbers" << endl;
	cin >> num;

	int val = (num+1)/2;
	int iterations = 0;
	
	while (val != 1)
	{
		int tmp;		
		tmp = val % 2;
		val >>= 1;
		iterations += val;
		val += tmp;
	}
	
	list<list<int>> items(num);
	list<future<list<int>>> futures;

	for (auto &it: items)
	{
		cin >> val;
		it.push_back(val);
	}

	for (int i = 0; i<(num+1)/2;++i)
	{		
		futures.emplace_back(pool.enqueue([&items,&glb_mtx]() {//HOW TO STORE A FUNCTION WITH A VALUE?
			list<type> first = {};
			list<type> second = {};
			{
				unique_lock<mutex> lock{ glb_mtx };
				first = items.front();
				items.pop_front();
				if (!items.empty())
				{
					second = items.front();
					items.pop_front();
				}
				//cout << "items poped<<<<<<<<<<<<<<<<< "/*<<items.size()*/ << endl;
			}			
			return merge(move(first),move(second));
		}));		
	}
	//cout <<"number of futures "<< futures.size() << endl;

	for (int i = 0; i < iterations; ++i)
	{
		futures.emplace_back(pool.enqueue([&futures, &glb_mtx]() {
			list<type> first = {};
			list<type> second = {};
			{
				unique_lock<mutex> lock{ glb_mtx };
				first = futures.front().get();
				futures.pop_front();
				if (!futures.empty())
				{
					second = futures.front().get();
					futures.pop_front();
				}
				//cout << "futures poped<<<<<<<<<<<<<<" /*<< futures.size()*/ << endl;
			}
			
			return merge(move(first), move(second));
		}));
	}
	//cout << "number of futures " << futures.size() << endl;
	while (futures.size() >1)
	{
	
	}
	//cout << "number of futures " << futures.size() << endl;

	list<type> promises = futures.front().get();
	for (auto it : promises)
	{
		cout << it << " ";
	}
	cout << promises.size() << endl;



	system("pause");
	return 0;
}