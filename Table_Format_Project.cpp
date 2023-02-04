#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <bits/stdc++.h>
using namespace std;
void Fun(int kolumny, vector<string> names, string zapytanie)
{
    //connect to db and make query
    MYSQL_ROW row;
    MYSQL_RES *res;
    MYSQL *connection = mysql_init(NULL);
    MYSQL *db;
    db = mysql_real_connect(connection, "localhost", "norbert", "", "TrainDB", 0, NULL, 0);
    const char *query;
    query = zapytanie.c_str();
    mysql_query(connection, query);
    res = mysql_store_result(connection);
    //--
    vector<string> kolejka;
    queue<int> numerki;
    string LongestFName = names[0];
    vector<int> spaces;
    string TOP = "+"; 
    //------------------
    for (size_t j = 0; j < kolumny; j++)
    {
        LongestFName = names[0];
        mysql_query(connection, query);
        res = mysql_store_result(connection);
        
        while (row = mysql_fetch_row(res))
        {
            for (size_t i = j; i < kolumny; i += kolumny)
            {
                string danezbazy = row[i];
                if (names[i].length() > LongestFName.length())
                {
                    LongestFName = names[i];
                }
                else if (danezbazy.length() > LongestFName.length())
                {
                    LongestFName = danezbazy;
                }
                kolejka.push_back(row[i]);
            }
        }
        
        spaces.push_back(LongestFName.length());
        for (size_t i = 0; i < (LongestFName.length()); i++)
        {
            TOP.append("-");
        }
        TOP.append("+");
    }
    int td = kolejka.size()/kolumny;
    
    for (size_t i = 0; i < spaces.size(); i++)
    {
        for (size_t j = i * td; j < ((i * td) + td); j++)
        {
            int ilost = spaces[i] - kolejka[j].length();
            for (size_t k = 0; k < ilost; k++)
            {
                kolejka[j].append(" ");
            }
        }
    }
    
    cout << TOP << endl;
    for (size_t i = 0; i < kolumny; i++)
    {
        int ilost = spaces[i] - names[i].length();
        for (size_t k = 0; k < ilost; k++)
        {
            names[i].append(" ");
        }
        cout << "|";
        cout << names[i];
    }
    cout << "|";
    cout << endl
         << TOP << endl;
    for (size_t j = 0; j < (kolejka.size() / kolumny); j++)
    {
        cout << "|";
        for (size_t i = j; i < kolejka.size(); i += td)
        {

            cout << kolejka[i] << "|";
        }
        cout << endl;
        cout << TOP << endl;
    }
    mysql_close(db);
}
int main()
{
    vector<string> names;
    names.push_back("ID");// table headers
    names.push_back("IDStacji");
    names.push_back("NrPrzystanku");
    names.push_back("GodzinaPrzyjazduOdjazdu"); 
    string zapytanie = "SELECT `ID`,`IDStacji`,`NrPrzystanku`,`GodzinaPrzyjazduOdjazdu` FROM trasy;"; // query text
    Fun(names.size(), names, zapytanie);
    return 0;
}