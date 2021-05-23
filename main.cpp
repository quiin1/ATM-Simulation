#include "1display.h"
#include "2account.h"
#include "3function.h"

extern int ynow;

int main(){
    _setmode(_fileno(stdin), _O_U16TEXT);
    //_setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(65001);
    SetWindowSize(62,40);

    //set up du lieu
    Set_List();

    while (true){
        Account client;
        Login_Signup_Exit(client); // đăng nhập đăng ký, thoát thì cảm ơn + exit

        if (client.unlock){
            ynow=7;
            choice_table(client);
        }
    }

    return 0;
}
