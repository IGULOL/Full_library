#pragma once
#include <vector>
#include <algorithm>
using namespace std;

template <class Type>
class my_container
{
protected:	
	vector<Type> c;

public:

	//�������� �� �������
	bool is_empty()
	{
		return c.empty();
	}
	//���������� ���������
	int size()
	{
		return c.size();
	}

	//���������� � ���������
	void push(Type el)
	{
		c.push_back(el);
	}
	
	//�������� �������� ����������
	bool remove(int i)
	{
		if ((i >= c.size()) || (i < 0))
		{
			return false;
		}
		c.erase(c.begin()+i);
		return true;
	}

	//��������� ��������
	bool edit(int i, Type el)
	{
		if ((i >= c.size()) || (i < 0))
		{
			return false;
		}
		c[i] = el;
		return true;
	}
	
	//���� ���������� �� �����
	bool input_file(string name)
	{
		Type el;
		ifstream infile(name);
		string str; //��� �����������
		c.clear();
		bool ok;
		if (!infile)
		{
			ok = false;
		}
		else
		{
			ok = true;
			while ( (infile >> el) && ok )
			{
				c.push_back(el);
				getline(infile, str); //��������� �����������
				ok = (str == "");
			}
			infile.close();
		}
		if (!ok)
		{
			c.clear();
		}
		return ok;  
	}

	//���� ���������� � ����������
	void input_screen()
	{
		istream_iterator<Type> is(cin);
		Type input;

		char ans;
		do {
			input = *is;
			c.push_back(input);
			cin.ignore(10, '\n');
			cout << "�������� ��� �������? (�� - y/ ��� - ����� �������)" << endl;
			cin >> ans;
			if ((ans == 'y') || (ans == 'Y'))
				is++;
		} while ((ans == 'y') || (ans == 'Y'));
	}

	//����� ���������� � ����
	bool output_file(string name)
	{
		ofstream outfile(name);
		if (outfile)
		{
			copy(c.begin(), c.end(), ostream_iterator<Type>(outfile, "\n"));
			return true;
		}
		else
		{
			return false;
		}
	}

	//����� ���������� �� �����
	void output_screen()
	{
		if (c.size() > 0)
		{
			int i = 0;
			for (vector<Type>::const_iterator iter = c.begin(); iter != c.end(); ++iter)
			{
				cout << "������ " << i++ << "." << endl;
				cout << *iter << endl;
			}
			//copy(c.begin(), c.end(), ostream_iterator<Type>(cout, "\n"));
		}
		else
		{
			cout << "��������� ����." << endl;
		}
	}

	//������ �������� �� �������
	bool print(int i)
	{
		if ((i >= c.size()) || (i < 0))
		{
			return false;
		}
		cout << "������ " << i << "." << endl;
		cout << c[i] << endl;
		return true;
	}

	/*�������� �����
	(������� ������������ �������� ��������, TSearch - ��� ��������)*/
	template <class TSearch>
	my_container<Type> search(int(*equal)(Type el, TSearch search), TSearch sear)
	{
		my_container<Type> find;
		for (vector<Type>::const_iterator iter = c.begin(); iter != c.end(); ++iter)
		{
			if ((*equal)(*iter, sear) == 0)
			{
				find.push(*iter);
			}
		}
		return find;
	}
	
	/*�������� �����
	(������� ������������ �������� ��������, TSearch - ��� ��������, ������� ��� ���������� �� ��������)*/
	template <class TSearch>
	my_container<Type> bin_search(int(*equal)(Type el, TSearch search), TSearch sear, 
									bool(*compare)(Type el1, Type el2))
	{
		sort(c.begin(), c.end(), compare);

		int n;
		int left = 0;
		int right = c.size();
		int mid = 0;
		bool find = false;
		while ((left <= right) && !find)
		{
			mid = ((left + right) / 2);
			n = (*equal)(c[mid], sear);
			if (n == 1)        //(c[mid] > element � sear)
			{
				right = mid - 1;
			}
			else
			{
				if (n == -1)   //(element � sear < c[mid])
				{
					left = mid + 1;
				}
				else
				{
					find = true;
				}
			}				
		}

		my_container<Type> res;
		if (find)
		{
			//���� ������
			for (int i = mid; (i < c.size()) && ((*equal)(c[i], sear) == 0); ++i)
			{
				res.push(c[i]);
			}
			mid--;
			//���� �����
			for (int i = mid; (i >= 0) && ((*equal)(c[mid], sear) == 0); --i)
			{
				res.push(c[i]);
			}
		}
		return res;
	}	
};

