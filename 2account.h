#ifndef QATM_ACCOUNT_H
#define QATM_ACCOUNT_H


#include "1display.h"
#include <fstream>

const int maxsizeOfList = 100;

/* Struct Account */
struct Account{
    int stt;
    string id,pass,name;
    long long money;
    bool unlock;

    Account(){}
    Account (int _stt, string _id, string _pass, string _name, long long _money, bool _unlock=true);

    friend istream& operator>> (istream& in, Account &x);

    friend ostream& operator<< (ostream& out, Account &x);

    void Set (int _stt, string _id, string _pass, string _name, long long _money, bool _unlock);

    void Display();
};


/* List Function */

void Set_List();

void Display_List();

void UpdatetoList(Account &client);

void Update_List();


long long calATMsmoney();

void showsATMsmoney();




#endif // QATM_ACCOUNT_H
