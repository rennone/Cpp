#define N 100
int strage[N];

#include <vector>
#include <list>
#include <map>
#include <iostream>
using namespace std;


template<typename T>
class Pool
{
	list<int> stack_;

	int count_;

	const int MaxNum;

	char *storage_;

	const int Size;
public:
	Pool()
		:MaxNum(100),
		Size( sizeof(T)+sizeof(int)),
		count_(0)
	{
		int n = MaxNum*Size + 1;
		storage_ = new char[n];
	}

	~Pool()
	{
		delete[](storage_);
	}

	T* Get()
	{
		T* t = reinterpret_cast<T*>(&(storage_[count_ * Size]));
		count_++;
		return t;
	}

	void Release(T *memory)
	{
		memory->~T();
	}
};


class Scheduler
{
public:
	class Task
	{
		friend Scheduler;

		bool isDead;
		bool updating;

		static int global_id;

		int id;
	public:
		Task()
			:id(global_id++)
		{

		}
		void Update()
		{
			if (updating)
			{
				cout << id << ", ";
				updating = false;
			}
		}

		void Initialize()
		{
			isDead = false;
			updating = false; //‰‰ñ‚Í•K‚¸ŽÀs‚·‚é
		}

		void Get()
		{

		}

		void Set()
		{
			updating = true;
		}
	};

	int id;
	std::list<Task*> storage[2];

	std::list<Task*> dust;
	int NumOfProcessTask;

	Scheduler() :id(0), NumOfProcessTask(10)
	{

	}

	void Update()
	{
		int other = (id + 1) & 1;
		int i = 0;
		for (list<Task*>::iterator it = storage[id].begin(); it != storage[id].end() && i < NumOfProcessTask;)
		{
			if ((*it)->isDead)
			{
				dust.push_back(*it);
			}
			else
			{
				(*it)->Set();
				storage[other].push_back(storage[id].front());
				i++;
			}

			it = storage[id].erase(it);
		}

		if (i < NumOfProcessTask)
		{
			other = id;
			id = (id + 1) & 1;
			int remain = storage[id].size() - i;
			for (list<Task*>::iterator it = storage[id].begin(); i < NumOfProcessTask &&  remain > 0; remain--)
			{
				if ((*it)->isDead)
				{
					dust.push_back(*it);
				}
				else
				{
					(*it)->Set();

					storage[other].push_back(storage[id].front());
					i++;
				}
				it = storage[id].erase(it);
			}
		}
	}

	Task* GetTask()
	{
		if (dust.size() > 0)
		{
			cout << "reuse" << endl;
			Task *ret = dust.front();
			ret->Initialize();
			storage[(id + 1) & 1].push_back(ret);

			return ret;
		}
		else
		{
			Task *ret = new Task();
			ret->Initialize();
			storage[(id + 1) & 1].push_back(ret);

			return ret;
		}
	}

	void ReleaseTask(Task* t)
	{
		t->isDead = true;
	}
};

int Scheduler::Task::global_id = 0;
class Hoge
{
public:
	int x_, y_;
public:
	Hoge(int x, int y) : x_(x), y_(y)
	{

	}

	~Hoge()
	{
		cout << "x" << endl;
	}
};


int main()
{

	Pool<Hoge> hogePool;

	Hoge *h = new(hogePool.Get()) Hoge (0, 1);
	cout << h->x_ << "," << h->y_ << endl;
	hogePool.Release(h);



	Scheduler s;


	vector<Scheduler::Task*> l;
	Scheduler::Task *c, *d;
	for (int j = 0; j < 10; j++)
	{
		l.push_back(s.GetTask());
	}
	c = s.GetTask();
	cout << "AAA" << endl;
	for (int i = 0; i < 10; i++)
	{
		s.Update();
		for (vector<Scheduler::Task*>::iterator it = l.begin(); it != l.end(); it++)
		{
			(*it)->Update();
		}
		c->Update();
		cout << "----------------------------------------" << endl;
		if (i < 5)
		{
			//c->Update();
		}
		else if (i == 5)
		{
			s.ReleaseTask(c);
		}
		else if (i == 6)
		{
			d = s.GetTask();
		}
		
		else
		{
			d->Update();
		}
	}
}