#ifndef QATM_DISPLAY_H
#define QATM_DISPLAY_H


#include <iostream>
#include <windows.h>  // display Unicode: =SetConsoleOutputCP(65001) == UTF-8;
                      // for COLOR;
                      // kiểu HANDLE, COORD
#include <fcntl.h>    // display Unicode: =UTF16/UTF8 (2 dòng setmode cho wcin, wcout)
#include <locale>     // convert wstring to string 1
#include <codecvt>    // convert wstring to string 2

#include <ctime>      // for TIME, https://codelearn.io/sharing/5-phut-tim-hieu-date-va-time-trong-cpp)

#include <conio.h>    // getch();
#include <iomanip>    // setw

//#include <string>    // to_string, wstring
//#include <string.h>  // memcpy, https://www.stdio.vn/modern-cpp/hien-thuc-va-su-dung-ham-memcmp-memcpy-memset-trong-c-c-Pi3Uq

using namespace std;
using convert_type = codecvt_utf8<wchar_t>;    // convert wstring to string 3

const string vietnamesechars[15] = { //0->14
    "aAeEoOuUiIdDyY",       //0
    "áàạảãâấầậẩẫăắằặẳẵ",    //1 //->vietnamesechars[0][0]
    "ÁÀẠẢÃÂẤẦẬẨẪĂẮẰẶẲẴ",    //2 //->vietnamesechars[0][1]
    "éèẹẻẽêếềệểễ",
    "ÉÈẸẺẼÊẾỀỆỂỄ",
    "óòọỏõôốồộổỗơớờợởỡ",
    "ÓÒỌỎÕÔỐỒỘỔỖƠỚỜỢỞỠ",
    "úùụủũưứừựửữ",
    "ÚÙỤỦŨƯỨỪỰỬỮ",
    "íìịỉĩ",
    "ÍÌỊỈĨ",
    "đ",
    "Đ",
    "ýỳỵỷỹ",
    "ÝỲỴỶỸ"
};



// WINDOW SIZE
void SetWindowSize(SHORT width, SHORT height);


// COLOR
void textcolor (unsigned short color);


// MOVE cursor And CHOOSE
void gotoxy(int x, int y);

void gotoxy(int x, int y, string text, int numofcolor);

void MoveCursorUpDownAndChoose(int poz_x, int &poz_y, int poschoice[][2], string text[][2], int numofchoice, int &dowhat);

void MoveCursorLeftRightAndChoose(int &poz_x, int &poz_y, int poschoice[][2], string text[][2], int numofchoice, int &dowhat);


// WCIN
void cin_ws2s(string &converted_str);

void getline_ws2s(string &converted_str, bool &isfirstgetline);

bool isfnpress(int a, wchar_t &k); //-> cin_wchs2s (trả về ký tự k nếu ký tự nhập vào khác ký tự a, giống thì thực hiện chức năng)

void pause(unsigned int milliseconds); //-> cin_wchs2s


void cin_wchs2s_hide(string &converted_str, int &x, int&y, bool &isturnback);

void cin_wchs2s_unhide(string &converted_str, int &x, int &y, bool &isturnback);

void cin_wchs2ll(long long &converted_str, int x, int y, bool &isturnback);


// to NO ACCENT
string noaccent(const string s);



#endif // QATM_DISPLAY_H

















