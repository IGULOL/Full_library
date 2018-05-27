#pragma once
#include "atlcomtime.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*»нформационна€ запись о книге, выданной на руки абоненту представл€ет собой структуру: 
- номер читательского билета, 
- фамили€ абонента, 
- дата выдачи, 
- дата возврата, 
- автор, 
- название, 
- год издани€, 
- издательство, 
- цена. 
ѕоиск по пол€м номер читательского билета, автор, издательство и дата возврата (просроченные). 
*/

//тип дата
struct date
{
	unsigned short day;   //dd
	unsigned short month; //mm
	unsigned short year;  //yyyy

	//консольный/файловый вывод
	friend ostream& operator<< (ostream& os, const date& d)
	{
		os << d.day << "." << d.month << "." << d.year;
		return os;
	}

	//консольный ввод
	friend istream& operator>> (istream& is, date& d)
	{
		do {
			cout << "день: ";
			is >> d.day;
		} while ((d.day > 31) || (d.day < 1));
		do {
			cout << "номер мес€ца: ";
			is >> d.month;
		} while ((d.month > 12) || (d.month < 1));
		do {
			cout << "год: ";
			is >> d.year;
		} while (d.year < 1970);
		return is;
	}

	//файловый ввод
	friend ifstream& operator >> (ifstream& is, date& d)
	{
		string str;
		is >> str;
		int n, m;
		n = str.find('.');
		d.day = atoi((str.substr(0, n)).c_str());
		m = str.find('.', n + 1);
		d.month = atoi((str.substr(n + 1, m - n - 1)).c_str());
		d.year = atoi((str.substr(m + 1)).c_str());
		return is;
	}

	bool operator== (date d2) const
	{
		return ((day == d2.day) && (month == d2.month)
			&& (year == d2.year));
	}

	bool operator> (date d2) const
	{
		//если года не равны
		if (!(year == d2.year))
		{
			return ((year > d2.year)) ? true : false;
		}
		else
		{
			//если мес€цы не равны
			if (!(month == d2.month))
			{
				return ((month > d2.month)) ? true : false;
			}
			else
			{
				return ((day > d2.day)) ? true : false;
			}
		}
	}
	bool operator< (date d2) const
	{
		//если года не равны
		if (!(year == d2.year))
		{
			return ((year < d2.year)) ? true : false;
		}
		else
		{
			//если мес€цы не равны
			if (!(month == d2.month))
			{
				return ((month < d2.month)) ? true : false;
			}
			else
			{
				return ((day < d2.day)) ? true : false;
			}
		}
	}
};

//структура книга
struct book
{
	string number_of_ticket;    //номер читательского билета 
	string surname;			    //фамили€ абонента
	date date_beg; 	//дата выдачи
	date date_end; 	//дата возврата
	string author;	//автор
	string title;	//название
	unsigned short year_public; //год издани€
	string office_publice;      //издательство
	double money;   //цена
	
	//консольный/файловый вывод
	friend ostream& operator<< (ostream& os, const book& b)
	{
		os << b.number_of_ticket.c_str() << endl;
		os << b.surname.c_str() << endl;
		os << b.date_beg << endl;
		os << b.date_end << endl;
		os << b.author.c_str() << endl;
		os << b.title.c_str() << endl;
		os << b.year_public << endl;
		os << b.office_publice.c_str() << endl;
		os << b.money << endl;
		return os;
	}

	//консольный ввод
	friend istream& operator>> (istream& is, book& b)
	{
		cout << "¬ведите номер читательского билета: ";
		is >> b.number_of_ticket;
		cout << "¬ведите фамилию абонента: ";
		is >> b.surname;

		cout << "¬ведите дату выдачи: " << endl;
		is >> b.date_beg;
		cout << "¬ведите дату возврата: " << endl;
		is >> b.date_end;

		cout << "¬ведите автора: ";
		is >> b.author;
		cout << "¬ведите название: ";
		is >> b.title;
		cout << "¬ведите год издани€: ";
		is >> b.year_public;
		cout << "¬ведите издательство: ";
		is >> b.office_publice;
		cout << "¬ведите цену: ";
		is >> b.money;
		return is;
	}

	//файловый ввод
	friend ifstream& operator>> (ifstream& is, book& b)
	{
		is >> b.number_of_ticket;
		is >> b.surname;
		is >> b.date_beg;
		is >> b.date_end;
		is >> b.author;
		is >> b.title;
		is >> b.year_public;
		is >> b.office_publice;
		is >> b.money;
		return is;
	}

	bool operator== (book m2) const
	{
		return ((number_of_ticket == m2.number_of_ticket) && (surname == m2.surname) 
			&& (date_beg == m2.date_beg) && (date_end == m2.date_end)
			&& (author == m2.author) && (title == m2.title)
			&& (year_public == m2.year_public) && (office_publice == m2.office_publice)
			&& (money == m2.money))	? true : false;
	}
};

