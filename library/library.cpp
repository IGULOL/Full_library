/*Результатом должна быть консольная программа с текстовым меню. Программа должна содержать шаблонный класс
для управления данными согласно заданию. 
Предусмотреть операции добавления, изменения и удаления элемента контейнера.
Реализовать ввод и вывод элементов контейнера с использованием потоковых итераторов на экран и в файл.
Реализовать операции поиска по заданным критериям и выборки подмножества элементов по заданным критериям. 
Реализовать поиск в двух вариантах: линейный поиск и двоичный поиск на отсортированном контейнере.
Предусмотреть вывод подмножества выборки на экран и в файл.*/

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

//проверка имени файла
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

//главное меню
char main_menu(char max)
{
	char correct[20] = "012";

	bool ok;
	char ch;
	cout << "--------------------------------------------------------" << endl;
	cout << "                         МЕНЮ" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Загрузка контейнера из файла" << endl;
	cout << "2 - Ввод контейнера с клавиатуры" << endl;
	if (max != '2')
	{
		strcpy(correct, "0123456789");
		cout << "3 - Добавить элемент" << endl;
		cout << "4 - Удалить элемент" << endl;
		cout << "5 - Изменить элемент" << endl;
		cout << "6 - Линейный поиск элементов (с возможностью сохранить)" << endl;
		cout << "7 - Двоичный поиск элементов (с возможностью сохранить)" << endl;
		cout << "8 - Вывод контейнера на экран" << endl;
		cout << "9 - Сохранение контейнера в файл" << endl;
	}
	cout << "0 - Выход" << endl;
	cout << "--------------------------------------------------------" << endl;
	do
	{
		cout << ">> ";
		cin >> ch;
		if (cin.good())
		{
			//проверка на пустую строку и лишние символы
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
			cout << "Неккоректный ввод.";
			cin.ignore(10, '\n');
		}
	} while (!ok);
}

//меню поиска
char main_search()
{
	char correct[20] = "01234";
	bool ok;
	char ch;
	cout << "--------------------------------------------------------" << endl;
	cout << "Выберите критерий поиска: " << endl;
	cout << "1 - Номер читательского билета" << endl;
	cout << "2 - Автор" << endl;
	cout << "3 - Издательство" << endl;
	cout << "4 - Дата возврата (+просроченные)" << endl;
	cout << "0 - Выход" << endl;
	cout << "--------------------------------------------------------" << endl;
	do
	{
		cout << ">> ";
		cin >> ch;
		if (cin.good())
		{
			//проверка на пустую строку и лишние символы
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
			cout << "Неккоректный ввод.";
			cin.ignore(10, '\n');
		}
	} while (!ok);
}

//**Для бинарного поиска**
template <class TSearch>
int(*sear)(book b1, TSearch b2);

//поиск по читательскому билету
int search_number(book b1, string number_of_ticket2)
{
	if (b1.number_of_ticket > number_of_ticket2)
		return 1;
	if (b1.number_of_ticket == number_of_ticket2)
		return 0;
	return -1;
}

//поиск по автору
int search_author(book b1, string author2)
{
	if (b1.author > author2)
		return 1;
	if (b1.author == author2)
		return 0;
	return -1;
}

//поиск по издательству
int search_office_publice(book b1, string office_publice2)
{
	if (b1.office_publice > office_publice2)
		return 1;
	if (b1.office_publice == office_publice2)
		return 0;
	return -1;
}

//поиск по дате возврата + просроченные
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

//меню поиска
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
			cout << "Введите номер читательского билета: "; 
			cin >> str;
			sear<string> = &search_number;
			res = c.search<string>(sear<string>, str);
		}
		break;
		case '2':
		{
			cout << "Введите автора: ";
			cin >> str;
			_tolower_(&str);
			sear<string> = &search_author;
			res = c.search<string>(sear<string>, str);
		}
		break;
		case '3':
		{
			cout << "Введите издательство: ";
			cin >> str;
			_tolower_(&str);
			sear<string> = &search_office_publice;
			res = c.search<string>(sear<string>, str);
		}
		break;
		case '4':
		{
			date dat;
			cout << "Введите дату возврата: " << endl;
			cin >> dat;
			sear<date> = &search_date_end;
			res = c.search<date>(sear<date>, dat);
		}
		break;
		}
		return res;
	}
}

//**Для линейного поиска**
bool(*sortirovka)(book el1, book el2);

//сортировка по читательскому билету
bool sort_number(book b1, book b2)
{
	return (b1.number_of_ticket < b2.number_of_ticket) ? true : false;
}

//поиск по автору
bool sort_author(book b1, book b2)
{
	return (b1.author < b2.author) ? true : false;
}

//поиск по издательству
bool sort_office_publice(book b1, book b2)
{
	return (b1.office_publice < b2.office_publice) ? true : false;
}

//поиск по дате возврата + просроченные
bool sort_date_end(book b1, book b2)
{
	return (b1.date_end < b2.date_end) ? true : false;
}

//меню бинарного поиска
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
			cout << "Введите номер читательского билета: ";
			cin >> str;
			sear<string> = &search_number;
			sortirovka = &sort_number;
			res = c.bin_search<string>(sear<string>, str, sortirovka);
		}
		break;
		case '2':
		{
			cout << "Введите автора: ";
			cin >> str;
			_tolower_(&str);
			sear<string> = &search_author;
			sortirovka = &sort_author;
			res = c.bin_search<string>(sear<string>, str, sortirovka);
		}
		break;
		case '3':
		{
			cout << "Введите издательство: ";
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
			cout << "Введите дату возврата: " << endl;
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

//сохранение контейнера или контейнера-результата в файл !!
void save_to_file(my_container<type_elem> *c, string message = "Контейнер сохранен в файл ")
{
	char ch;
	char name[50]; //!!
	do
	{
		cout << "Cохранить в файл? (да - y/ нет - любая клавиша)" << endl;
		cin >> ch;
		if ((ch == 'y') || (ch == 'Y'))
		{
			cout << "Введите имя файла: ";
			cin >> name;
			if (correct_filename(name))
			{
				c -> output_file(name);
				cout << message << name << ".\n";
				return;
			}
			else
			{
				cout << "Неккоректное имя файла." << endl;
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
				cout << "Введите имя файла (*.txt): ";
				cin >> name;
				ok = correct_filename(name);
				if (ok)
				{
					if (my_c.input_file(name))
					{
						cout << "Загрузка произведена из файла с именем " << name << ".\n";
						max_item = '8';
					}
					else
					{
						cout << "Файл не удалось открыть." << endl;
					}
				}
				else
				{
					cout << "Неккоректное имя файла." << endl;
				}
			} while (!ok);
		}
		break;
		case '2':
		{
			cout << "Ввод контейнера." << endl << "Введите элементы:" << endl;
			my_c.input_screen();
			max_item = '9';
		}
		break;
		case '3':
		{
			cout << "Введите элемент:" << endl;
			cin >> el;
			if (cin.good())
			{
				my_c.push(el);
				cout << "Элемент добавлен." << endl;
			}
			else
			{
				cin.clear();
				cout << "Неккоректный ввод.";
			}
			cin.ignore(10, '\n');
		}
		break;
		case '4':
		{
			if (my_c.size() == 0)
			{
				cout << "Элементов нет.";
			}
			else
			{
				cout << "Удаление по индексу." << endl << "Введите индекс [0;" << my_c.size()-1 << "]: ";
				cin >> n;
				if (cin.good())
				{
					if (my_c.remove(n))
					{
						cout << "Элемент удален." << endl;
					}
					else
					{
						cout << "Элемент не удален." << endl;
					}
				}
				else
				{
					cin.clear();
					cout << "Неккоректный ввод.";
				}
				cin.ignore(10, '\n');
			}
		}
		break;
		case '5':
		{
			if (my_c.size() == 0)
			{
				cout << "Элементов нет.";
			}
			else
			{
				cout << "Изменение элемента по индексу." << endl << "Введите индекс [0;" << my_c.size()-1 << "]: ";
				cin >> n;
				if (cin.good())
				{
					if (!my_c.print(n))
					{
						cout << "Такого элемента нет." << endl;
					}
					else
					{
						cout << "Введите новый элемент:" << endl;
						cin >> el;
						if (cin.good())
						{
							my_c.edit(n, el);
							cout << "Элемент изменен." << endl;
						}
						else
						{
							cin.clear();
							cout << "Неккоректный ввод.";
						}
					}
				}
				else
				{
					cin.clear();
					cout << "Неккоректный ввод.";
				}
				cin.ignore(10, '\n');
			}
		}
		break;
		case '6':
		{
			//линейный поиск
			res = menu_search(my_c);
			cout << "Результат линейного поиска:" << endl;
			res.output_screen();
			if (res.size() > 0) 
			{
				save_to_file(&res, "Результат сохранен в файл ");
			}
		}
		break;
		case '7':
		{
			//бинарный поиск
			res = menu_bin_search(my_c);
			cout << "Результат бинарного поиска:" << endl;
			res.output_screen();
			if (res.size() > 0)
			{
				save_to_file(&res, "Результат сохранен в файл ");
			}
		}
		break;
		case '8':
			cout << "Текущий контейнер: " << endl;
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
			cout << "Некорретный ввод." << endl;
			break;
		}
		cout << endl;
	} while (item != 0);

    return 0;
}

