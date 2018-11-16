#include <stdio.h>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
struct Element
{
public:
	Element(int32_t i, int32_t j)
	{
		_i = i;
		_j = j;
	}
	~Element()
	{
		std::cout << "Element destruct<<" << _i << std::endl;
	}
	int32_t _i;
	int32_t _j;
};

void SharedPtrTest()
{
	std::shared_ptr<Element> p4;
	{
		std::shared_ptr<Element> p1(new Element(1, 2));
		p4 = p1;
		p1.reset(); //这里不会调用析构函数
		//std::cout << p1->i << p1->j << std::endl;

		Element *p2 = new Element(3, 4);
		std::shared_ptr<Element> p3(p2);			//如果p2托管给一个智能指针p3，那么当p3超出作用域时，会被释放
		//p3.reset();
	}
	char c = getchar();
}

std::unique_ptr<Element> UniqePtrTest()
{
	std::unique_ptr<Element> p1(new Element(1, 2));
	return p1;
	//std::unique_ptr<Element> p2 = p1;//编译不通过，unique_ptr不可以转移给别人
	//char c = getchar();
}

//用weak_ptr来解决循环引用的问题
class Person: public enable_shared_from_this<Person>
{
public:
	Person(const string& name) :
			m_name
			{ name }
	{
	}

	~Person()
	{
		cout << "release " << m_name << endl;
	}

	string getName() const
	{
		return m_name;
	}

	void setFather(shared_ptr<Person> f)
	{
		m_father = f;
		if (f)
		{
			f->m_kids.push_back(shared_from_this());
		}
	}

	void setMother(shared_ptr<Person> m)
	{
		m_mother = m;
		if (m)
		{
			m->m_kids.push_back(shared_from_this());
		}
	}

	shared_ptr<Person> getKid(size_t idx)
	{
		if (idx < m_kids.size())
		{
			weak_ptr<Person> p = m_kids.at(idx);
			if (!p.expired())
			{
				return p.lock();
			}
		}
		return nullptr;
	}

private:
	string m_name;
	shared_ptr<Person> m_father;
	shared_ptr<Person> m_mother;
	//vector<shared_ptr<Person>>    m_kids; // 循环依赖,你中有我，我中有你，结果都不释放
	vector<weak_ptr<Person>> m_kids;
};

void TestWeakPtr()
{
	shared_ptr<Person> jack
	{ make_shared<Person>("Jack") };
	shared_ptr<Person> lucy
	{ make_shared<Person>("Lucy") };
	shared_ptr<Person> john
	{ make_shared<Person>("John") };
	john->setFather(jack);
	john->setMother(lucy);

	auto p = jack->getKid(0);
	if (p)
	{
		cout << p->getName() << endl;
	}
}
int main(int argc, const char *argv[])
{
	SharedPtrTest();
	std::unique_ptr<Element> p1 = UniqePtrTest();	//可以通过函数传递一个将亡的
	TestWeakPtr();
	char c = getchar();

}
