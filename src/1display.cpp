#include "1display.h"


// Global variable - display
HANDLE qconsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int xnow=0, ynow=0;


// WINDOW SIZE
void SetWindowSize(SHORT width, SHORT height){
    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Bottom = height;
    WindowSize.Right = width;
    SetConsoleWindowInfo(qconsole, 1, &WindowSize);
}


// COLOR
void textcolor (unsigned short color){
    SetConsoleTextAttribute(qconsole,color);
}


// MOVE cursor And CHOOSE
void gotoxy(int x, int y){
  CursorPosition = {x,y};
  SetConsoleCursorPosition(qconsole, CursorPosition);
}
void gotoxy(int x, int y, string text, int numofcolor){
  CursorPosition = {x,y};
  SetConsoleCursorPosition(qconsole, CursorPosition);
  textcolor(numofcolor);
  cout << text;
}
void MoveCursorUpDownAndChoose(int poz_x, int &poz_y, int poschoice[][2], string text[][2], int numofchoice, int &dowhat){
                                            // tham chiếu ynow để tiện gọi hàm
    wchar_t keys;
    int a=-1, countchoice= poz_y - poschoice[0][1];
    gotoxy(poz_x, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
    gotoxy(poz_x, poz_y);

    while(true){
        for (int i=0; i<numofchoice; i++){
            if (poz_y==poschoice[i][1]){
                dowhat = a = getch();
                if (a==27 || a==13 || a==8){ //ESC==27; ENTER==13; BACKSPACE==8; OTHERS
                    textcolor(15);
                    return;  // Những phím có chức năng đc ấn -> dừng MoveAndChoose
                }
            }
        }

        keys = getch();

        if (keys == 72){        // Up
                gotoxy(xnow, poz_y, text[ countchoice ][0], stoi( text[ countchoice ][1] ) );
            if (countchoice+1!=1){
                countchoice--;
                poz_y = poschoice[ countchoice ][1];
                gotoxy(xnow, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(poz_x, poz_y);
            }
            else{
                countchoice = numofchoice-1;
                poz_y = poschoice[ countchoice ][1];
                gotoxy(xnow, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(xnow, poz_y);
            }
        }
        else if (keys == 80){   // Down
                gotoxy(xnow, poz_y, text[ countchoice ][0], stoi( text[ countchoice ][1] ) );
            if (countchoice+1!=numofchoice){
                countchoice++;
                poz_y = poschoice[ countchoice ][1];
                gotoxy(xnow, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(poz_x, poz_y);
            }
            else{
                countchoice = 1-1;
                poz_y = poschoice[ countchoice ][1];
                gotoxy(xnow, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(xnow, poz_y);
            }
        }
        else if (keys == 75){   // Left

        }
        else if (keys == 77){   // Right

        }
    }
}

void MoveCursorLeftRightAndChoose(int &poz_x, int &poz_y, int poschoice[][2], string text[][2], int numofchoice, int &dowhat){
    wchar_t keys;
    int a=-1, countchoice = poz_x - poschoice[0][0];
    gotoxy(poz_x, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
    gotoxy(poz_x, poz_y);

    while(true){
        for (int i=0; i<numofchoice; i++){
            if (poz_x==poschoice[i][0]){
                dowhat = a = getch(); //ESC==27; ENTER==13; BACKSPACE==8; OTHERS
                if (a==27 || a==13 || a==8){
                    textcolor(15);
                    return;  // Những phím có chức năng đc ấn -> dừng MoveAndChoose
                }
            }
        }

        keys = getch();

        if (keys == 75){   // Left
                gotoxy(poz_x, poz_y, text[ countchoice ][0], stoi( text[ countchoice ][1] ) ); // trả lại màu cũ
            if (countchoice!=0){
                countchoice--;
                poz_x = poschoice[ countchoice ][0];
                gotoxy(poz_x, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(poz_x, poz_y);
            }
            else{
                countchoice = numofchoice -1;
                poz_x = poschoice[ countchoice ][0];
                gotoxy(poz_x, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(poz_x, poz_y);
            }
        }
        else if (keys == 77){   // Right
                 gotoxy(poz_x, poz_y, text[ countchoice ][0], stoi( text[ countchoice ][1] ) );
            if (countchoice!=numofchoice-1){
                countchoice++;
                poz_x = poschoice[ countchoice ][0];
                gotoxy(poz_x, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(poz_x, poz_y);
            }
            else{
                countchoice = 1-1;
                poz_x = poschoice[ countchoice ][0];
                gotoxy(poz_x, poz_y, text[ countchoice ][0], 142); // màu nền: màu xám
                gotoxy(poz_x, poz_y);
            }
        }
        else if (keys == 72){   // Up

        }
        else if (keys == 80){   // Down

        }
    }
}


// WCIN
void cin_ws2s(string &converted_str){
    wstring string_to_convert;
    wcin >> string_to_convert;

    //setup converter
    wstring_convert<convert_type, wchar_t> converter;

    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    converted_str = converter.to_bytes( string_to_convert );
    //cout << " ID: " << converted_str << endl;                     //test
}

void getline_ws2s(string &converted_str, bool &isfirstgetline){
    wstring string_to_convert;

    getline(wcin,string_to_convert);
    isfirstgetline=false;

    //setup converter
    wstring_convert<convert_type, wchar_t> converter;

    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    converted_str = converter.to_bytes( string_to_convert );
}

bool isfnpress(int a, wchar_t &k){//-> cin_wchs2s (trả về ký tự k nếu ký tự nhập vào khác ký tự a, giống thì thực hiện chức năng)
    k = getch();
    if (k!=a){
        return false; // ký tự
    }
    else
        return true; // chức năng
}

void pause(unsigned int milliseconds){//-> cin_wchs2s
    time_t final = milliseconds + clock();
	while (milliseconds < final)
	{
		milliseconds = clock();
	}
}

void cin_wchs2s_hide(string &converted_str, int &x, int&y, bool &isturnback){  // chỉ dùng để nhập pass
                                                                                // dùng tham chiếu để lấy vị trí cho những lần nhập pass sai
    wstring string_to_convert;
    wchar_t k2;
    int firstx = x; //posXY ban đầu = (firstx,y); 11 12

    gotoxy(x,y);

    {
        while (!isfnpress(13,k2)){//Ko Enter thì nhập tiếp
            if (k2==8){ //Backspace;
                if (x>firstx){ //Pos ban đầu = firstx,y nên ko được xóa quá tọa độ x=firstx ko thì mất chữ "Mật khẩu :"
                    gotoxy(x-1,y," ",15); x--;
                    gotoxy(x,y);
                    string_to_convert = string_to_convert.substr(0,string_to_convert.length()-1);
                }
            }
            else if (k2==27){
                isturnback = true;
                return;
            }
            else {
                x++; // cho isfnpress
                cout << (char) k2;
                pause(200);
                gotoxy(x-1,y,"*",15);
                string_to_convert += k2;
            }
        }
    }

    //string_to_convert+='\0';

    //setup converter
    wstring_convert<convert_type, wchar_t> converter;

    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    converted_str = converter.to_bytes( string_to_convert );
//    y++; cout << "\nPass: " << converted_str << "\t";            //test
//    cout << "Pos: " << x << " " << y;                            //test
    cout << "\n";
}

void cin_wchs2s_unhide(string &converted_str, int &x, int &y, bool &isturnback){ // nhập từng ký tự
                                                                                // dùng tham chiếu để lấy vị trí cho những lần nhập lại
                                                                                // ấn Esc để quay lại màn hình chính

    wstring string_to_convert;
    wchar_t k2;
    int firstx = x; //posXY ban đầu = (firstx,y);

    gotoxy(x,y);
    {
        while (!isfnpress(13,k2)){//Ko Enter thì nhập tiếp
            if (k2==8){ //Backspace;
                if (x>firstx){ //Pos ban đầu = firstx,y nên ko được xóa quá tọa độ x=firstx ko thì mất chữ "... :"
                    gotoxy(x-1,y," ",15); x--;
                    gotoxy(x,y);
                    string_to_convert = string_to_convert.substr(0,string_to_convert.length()-1);
                }
            }
            else if (k2==27){
                isturnback = true;
                return;
            }
            else {
                x++; // cho isfnpress
                cout << (char) k2;
                string_to_convert += k2;
            }
        }
    }

    //setup converter
    wstring_convert<convert_type, wchar_t> converter;

    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    converted_str = converter.to_bytes( string_to_convert );
//    y++; cout << "\nPass: " << converted_str << "\t";            //test
//    cout << "Pos: " << x << " " << y;                            //test
    cout << "\n";
}

void cin_wchs2ll(long long &converted_str, int x, int y, bool &isturnback){ // nhập từng ký tự
    // posXY ban đầu nhập tiền rút = (40,20);
    converted_str = 0;
    wchar_t k2;
    int firstx = x;

    gotoxy(x,y);
    {
        while (!isfnpress(13,k2)){//Ko Enter thì nhập tiếp
            if (k2==8){ //Backspace;
                if (x>firstx){ //Pos ban đầu = firstx,y nên ko được xóa quá tọa độ x=firstx ko thì mất chữ Mật khẩu :
                    gotoxy(x-1,y," ",15); x--;
                    gotoxy(x,y);
                    converted_str /= 10;
                }
            }
            else if (k2==27){ //ấn Esc để quay lại màn hình chính
                isturnback = true;
                return;
            }
            else if (k2>='0' && k2<='9') {
                x++; // cho isfnpress
                cout << (char) k2;
                converted_str = converted_str * 10 + (k2-'0');
            }
        }
    }
    cout << "\n";
}

// to NO ACCENT
string noaccent(const string s){ // ham loc dau xau Tieng Viet -> xau ko dau
    string res=s;

    for (int i=0; i<res.length(); i++){

        for (int k=1; k<15; k++){
            if (vietnamesechars[k].find(res[i])!=-1){

                for (int numOfCha=3; numOfCha>=2; numOfCha--){
                    // ky tu co numOfChar-1 dau
                    string cha = res.substr(i,numOfCha) + '\0';
//                    cout << cha << " " << cha.length() << endl;                                    // test
                    bool check=false;


                    for (int j=1; j<15; j++){
//                        cout << "\t" << vietnamesechars[j].find(cha.substr(0,numOfCha)) << endl;          // test
                        if (vietnamesechars[j].find(cha.substr(0,numOfCha))!=-1){
                            res.replace(i,numOfCha,1,vietnamesechars[0][j-1]);
//                            cout << numOfCha << "\t" << res << endl;                               // test
                            check = true;
                            break;
                        }
                    }
                    if (check) break;

                }

            }

        }

    }
    return res;
}






















