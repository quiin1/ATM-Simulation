#include "1display.h"
#include "2account.h"
#include "3feature.h"

extern int ynow;

int main(){
    _setmode(_fileno(stdin), _O_U16TEXT);
    //_setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(65001);
    SetWindowSize(62,40);

    Set_List(); //set up du lieu

    while (true){
        Account client;
        Login_Signup_Exit(client);

        if (client.unlock){
            ynow=7;
            choice_table(client);

            thankyou();
            system("PAUSE");
        }
    }

    return 0;
}
