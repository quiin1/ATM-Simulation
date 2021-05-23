#ifndef QATM_H
#define QATM_H

#include "1display.h"
#include "2account.h"


/* Login_Signup_Exit */

// Thanks
void thankyou();


// Log in
Account checkAcc(string &id, string pass, bool &checkid, bool &check);

bool login(Account &client);


// Sign up (Đăng ký)
void signup(Account &client);


// 1. Login Or Signup Or Exit:
void Login_Signup_Exit(Account &client);






/* Choice_Table */

// Chức năng History
void saveHistory(Account &client, string loaigd, long long &number, string mess="");

void seeHistory(Account &client);

void saveHistoryNoAccent(Account &client, string loaigd, long long &number, string mess="");


// Chức năng Gửi tiền
void guitien(Account &client);


// Chức năng Rút tiền
bool FantasticGreedy(int moneyout[][2], int st, int en, const int &mon);

void ruttien(Account &client);


// Chức năng Chuyển khoản
void chuyenkhoan(Account &client);


// Chức năng Change Password
void changePass(Account &client);


// 2. Choice Table
void choice_table(Account &client);



#endif // QATM_H
