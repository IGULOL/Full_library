/*����������� ������ ���� ���������� ��������� � ��������� ����. ��������� ������ ��������� ��������� �����
��� ���������� ������� �������� �������. 
������������� �������� ����������, ��������� � �������� �������� ����������.
����������� ���� � ����� ��������� ���������� � �������������� ��������� ���������� �� ����� � � ����.
����������� �������� ������ �� �������� ��������� � ������� ������������ ��������� �� �������� ���������. 
����������� ����� � ���� ���������: �������� ����� � �������� ����� �� ��������������� ����������.
������������� ����� ������������ ������� �� ����� � � ����.*/

#include "my_container.h"
#include "book.h"
#include <Windows.h>
#include <locale.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <cstdio>
#include <cstring>
using namespace std;

typedef typename book type_elem;

//�������� ����� �����
char notcorrect[] = "/|\?!&^%$#*:;><-+()";
bool correct_filename(char name[])
{
	bool bad = strstr(name, ".txt") != &name[strlen(name) - 4];
	for (int i = 0; (i < (strlen(name) - 4)) && !bad; ++i)
	{
		bad = (strchr(notcorrect, name[i]) != NULL);
	}
	return !bad;
}

//������� ����
char main_menu(char max)
{
	char correct[20] = "012";

	bool ok;
	char ch;
	cout << "--------------------------------------------------------" << endl;
	cout << "                         ����" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - �������� ���������� �� �����" << endl;
	cout << "2 - ���� ���������� � ����������" << endl;
	if (max != '2')
	{
		strcpy(correct, "0123456789");
		cout << "3 - �������� �������" << endl;
		cout << "4 - ������� �������" << endl;
		cout << "5 - �������� �������" << endl;
		cout << "6 - �������� ����� ��������� (� ������������ ���������)" << endl;
		cout << "7 - �������� ����� ��������� (� ������������ ���������)" << endl;
		cout << "8 - ����� ���������� �� �����" << endl;
		cout << "9 - ���������� ���������� � ����" << endl;
	}
	cout << "0 - �����" << endl;
	cout << "--------------------------------------------------------" << endl;
	do
	{
		cout << ">> ";
		cin >> ch;
		if (cin.good())
		{
			//�������� �� ������ ������ � ������ �������
			ok = (strchr(correct, ch) != NULL);
			cin.ignore(10, '\n');
			if (ok)
			{
				return ch;
			}
		}
		else
		{
			cin.clear();
			cout << "������������ ����.";
			cin.ignore(10, '\n');
		}
	} while (!ok);
}

//���� ������
char main_search()
{
	char correct[20] = "01234";
	bool ok;
	char ch;
	cout << "--------------------------------------------------------" << endl;
	cout << "�������� �������� ������: " << endl;
	cout << "1 - ����� ������������� ������" << endl;
	cout << "2 - �����" << endl;
	cout << "3 - ������������" << endl;
	cout << "4 - ���� �������� (+������������)" << endl;
	cout << "0 - �����" << endl;
	cout << "--------------------------------------------------------" << endl;
	do
	{
		cout << ">> ";
		cin >> ch;
		if (cin.good())
		{
			//�������� �� ������ ������ � ������ �������
			ok = (strchr(correct, ch) != NULL);
			cin.ignore(10, '\n');
			if (ok)
			{
				return ch;
			}
		}
		else
		{
			cin.clear();
			cout << "������������ ����.";
			cin.ignore(10, '\n');
		}
	} while (!ok);
}

//**��� ��������� ������**
template <class TSearch>
int(*sear)(book b1, TSearch b2);

//����� �� ������������� ������
int search_number(book b1, string number_of_ticket2)
{
	if (b1.number_of_ticket > number_of_ticket2)
		return 1;
	if (b1.number_of_ticket == number_of_ticket2)
		return 0;
	return -1;
}

//����� �� ������
int search_author(book b1, string author2)
{
	if (b1.author > author2)
		return 1;
	if (b1.author == author2)
		return 0;
	return -1;
}

//����� �� ������������
int search_office_publice(book b1, string office_publice2)
{
	if (b1.office_publice > office_publice2)
		return 1;
	if (b1.office_publice == office_publice2)
		return 0;
	return -1;
}

//����� �� ���� �������� + ������������
int search_date_end(book b1, date date_end2)
{
	if (b1.date_end > date_end2)
		return 1;
	return 0;
}

void _tolower_(string * s)
{
	transform(s->begin(), s->end(), s->begin(), tolower);
	transform(s->begin(), s->begin()+1, s->begin(), toupper);
}

//���� ������
my_container<type_elem> menu_search(my_container<type_elem> c)
{
	char ch = main_search();	
	cout << endl;

	setlocale(LC_ALL, "");

	string str;
	my_container<type_elem> res;
	if (ch == '0')
	{
		return res;
	}
	else
	{
		switch (ch)
		{
		case '1':
		{
			cout << "������� ����� ������������� ������: "; 
			cin >> str;
			sear<string> = &search_number;
			res = c.search<string>(sear<string>, str);
		}
		break;
		case '2':
		{
			cout << "������� ������: ";
			cin >> str;
			_tolower_(&str);
			sear<string> = &search_author;
			res = c.search<string>(sear<string>, str);
		}
		break;
		case '3':
		{
			cout << "������� ������������: ";
			cin >> str;
			_tolower_(&str);
			sear<string> = &search_office_publice;
			res = c.search<string>(sear<string>, str);
		}
		break;
		case '4':
		{
			date dat;
			cout << "������� ���� ��������: " << endl;
			cin >> dat;
			sear<date> = &search_date_end;
			res = c.search<date>(sear<date>, dat);
		}
		break;
		}
		return res;
	}
}

//**��� ��������� ������**
bool(*sortirovka)(book el1, book el2);

//���������� �� ������������� ������
bool sort_number(book b1, book b2)
{
	return (b1.number_of_ticket < b2.number_of_ticket) ? true : false;
}

//����� �� ������
bool sort_author(book b1, book b2)
{
	return (b1.author < b2.author) ? true : false;
}

//����� �� ������������
bool sort_office_publice(book b1, book b2)
{
	return (b1.office_publice < b2.office_publice) ? true : false;
}

//����� �� ���� �������� + ������������
bool sort_date_end(book b1, book b2)
{
	return (b1.date_end < b2.date_end) ? true : false;
}

//���� ��������� ������
my_container<type_elem> menu_bin_search(my_container<type_elem> c)
{
	char ch = main_search();
	cout << endl;

	setlocale(LC_ALL, "");
	string str;
	book el;
	my_container<type_elem> res;
	if (ch == '0')
	{
		return res;
	}
	else
	{
		switch (ch)
		{
		case '1':
		{
			cout << "������� ����� ������������� ������: ";
			cin >> str;
			sear<string> = &search_number;
			sortirovka = &sort_number;
			res = c.bin_search<string>(sear<string>, str, sortirovka);
		}
		break;
		case '2':
		{
			cout << "������� ������: ";
			cin >> str;
			_tolower_(&str);
			sear<string> = &search_author;
			sortirovka = &sort_author;
			res = c.bin_search<string>(sear<string>, str, sortirovka);
		}
		break;
		case '3':
		{
			cout << "������� ������������: ";
			cin >> str;
			_tolower_(&str);
			sear<string> = &search_office_publice;
			sortirovka = &sort_office_publice;
			res = c.bin_search<string>(sear<string>, str, sortirovka);
		}
		break;
		case '4':
		{
			date dat;
			cout << "������� ���� ��������: " << endl;
			cin >> dat;
			sear<date> = &search_date_end;
			sortirovka = &sort_date_end;
			res = c.bin_search<date>(sear<date>, dat, sortirovka);
		}
		break;
		}
		return res;
	}
}

//���������� ���������� ��� ����������-���������� � ���� !!
void save_to_file(my_container<type_elem> *c, string message = "��������� �������� � ���� ")
{
	char ch;
	char name[50]; //!!
	do
	{
		cout << "C�������� � ����? (�� - y/ ��� - ����� �������)" << endl;
		cin >> ch;
		if ((ch == 'y') || (ch == 'Y'))
		{
			cout << "������� ��� �����: ";
			cin >> name;
			if (correct_filename(name))
			{
				c -> output_file(name);
				cout << message << name << ".\n";
				return;
			}
			else
			{
				cout << "������������ ��� �����." << endl;
			}
		}
	} while (true);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	my_container<type_elem> my_c;
	my_container<type_elem> res;
	char item;
	char max_item = '2';
	char ch;
	char name[] = "";
	int n;
	bool ok;

	type_elem el;

	do
	{
		item = main_menu(max_item);
		cout << endl;
		switch (item)
		{
		case '1':
		{
			do
			{
				cout << "������� ��� ����� (*.txt): ";
				cin >> name;
				ok = correct_filename(name);
				if (ok)
				{
					if (my_c.input_file(name))
					{
						cout << "�������� ����������� �� ����� � ������ " << name << ".\n";
						max_item = '8';
					}
					else
					{
						cout << "���� �� ������� �������." << endl;
					}
				}
				else
				{
					cout << "������������ ��� �����." << endl;
				}
			} while (!ok);
		}
		break;
		case '2':
		{
			cout << "���� ����������." << endl << "������� ��������:" << endl;
			my_c.input_screen();
			max_item = '9';
		}
		break;
		case '3':
		{
			cout << "������� �������:" << endl;
			cin >> el;
			if (cin.good())
			{
				my_c.push(el);
				cout << "������� ��������." << endl;
			}
			else
			{
				cin.clear();
				cout << "������������ ����.";
			}
			cin.ignore(10, '\n');
		}
		break;
		case '4':
		{
			if (my_c.size() == 0)
			{
				cout << "��������� ���.";
			}
			else
			{
				cout << "�������� �� �������." << endl << "������� ������ [0;" << my_c.size()-1 << "]: ";
				cin >> n;
				if (cin.good())
				{
					if (my_c.remove(n))
					{
						cout << "������� ������." << endl;
					}
					else
					{
						cout << "������� �� ������." << endl;
					}
				}
				else
				{
					cin.clear();
					cout << "������������ ����.";
				}
				cin.ignore(10, '\n');
			}
		}
		break;
		case '5':
		{
			if (my_c.size() == 0)
			{
				cout << "��������� ���.";
			}
			else
			{
				cout << "��������� �������� �� �������." << endl << "������� ������ [0;" << my_c.size()-1 << "]: ";
				cin >> n;
				if (cin.good())
				{
					if (!my_c.print(n))
					{
						cout << "������ �������� ���." << endl;
					}
					else
					{
						cout << "������� ����� �������:" << endl;
						cin >> el;
						if (cin.good())
						{
							my_c.edit(n, el);
							cout << "������� �������." << endl;
						}
						else
						{
							cin.clear();
							cout << "������������ ����.";
						}
					}
				}
				else
				{
					cin.clear();
					cout << "������������ ����.";
				}
				cin.ignore(10, '\n');
			}
		}
		break;
		case '6':
		{
			//�������� �����
			res = menu_search(my_c);
			cout << "��������� ��������� ������:" << endl;
			res.output_screen();
			if (res.size() > 0) 
			{
				save_to_file(&res, "��������� �������� � ���� ");
			}
		}
		break;
		case '7':
		{
			//�������� �����
			res = menu_bin_search(my_c);
			cout << "��������� ��������� ������:" << endl;
			res.output_screen();
			if (res.size() > 0)
			{
				save_to_file(&res, "��������� �������� � ���� ");
			}
		}
		break;
		case '8':
			cout << "������� ���������: " << endl;
			my_c.output_screen();
			break;
		case '9':
		{
			save_to_file(&my_c);
		}
		break;
		case '0':
			exit(0);
			break;
		default:
			cout << "����������� ����." << endl;
			break;
		}
		cout << endl;
	} while (item != 0);

    return 0;
}

