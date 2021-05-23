#include "3feature.h"

extern int xnow,ynow;
extern int num_people;
extern int money[][2];
extern long long ATMsmoney;
extern Account List[maxsizeOfList+1]; // from 1 -> num_people

// 1. Login Or Signup Or Exit
// Thanks
void thankyou(){
    system("CLS");
    textcolor(14);  // yellow
    cout <<   "================== <<>> QUỲNH's BANK <<>> ==================\n"; //length=60
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|              Xin chân thành cảm ơn quý khách!            |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "============================================================\n";
    textcolor(15); // white
    pause(700);
}

// Log in
Account checkAcc(string &id, string pass, bool &checkid, bool &check){
    checkid = check = false;
    int remi;
    for (int i=0; i<=num_people; i++){
        if (List[i].id==id){
            checkid = true;
            remi=i;
            if (List[i].pass==pass){
                check = true;
                return List[i];         //id & pass đều đúng             -> check==true                  => welcome
            }
        }
    }
    if (checkid) return List[remi];     //chi dung id -> return per      -> check==false & checkid==true => sai 5 lần khóa thẻ
    return List[0];                     //ko dung id -> return WRONG per -> check=checkid==false         => ko tồn tại thẻ
}

bool login(Account &client){
    string id, idprev, pass;
    bool checkid, check, isturnback=false;
    int x=11,y=10; // vị trí cursor

    int c=0;
    do{
        c++;
        textcolor(15);  // white
        cout << "ID:        "; x=11; y++;  cin_wchs2s_unhide(id,x,y, isturnback); //getline_ws2s(id); //cin_ws2s(id);
        if (isturnback){
            return false;
        }
        cout << "Mật khẩu:  "; x=11; y++;  cin_wchs2s_hide(pass,x,y, isturnback); //pos: 11 12
        if (isturnback){
            return false;
        }

        client = checkAcc(id,pass,checkid,check);
        if (c!=0 && idprev!=client.id) c=1;

        if (check){
            system("CLS");
            if (!client.unlock){
                textcolor(14);  // yellow
                cout << "\n================== <<>> QUỲNH's BANK <<>> ==================\n\n"; //length=60
                textcolor(12);  // red
                cout <<   "Thẻ của quý khách đã bị khóa!\n";
                cout <<   "Xin vui lòng đến ngân hàng gần nhất để được hỗ trợ mở khóa.\n\n\n";
                textcolor(15);  // white
                system("PAUSE");
            }
            return true;
        }
        else{
            textcolor(12);  // red
            if (checkid){
                //cout << "Your password is incorrect.\n";
                cout << "Mật khẩu bạn vừa nhập không chính xác.\n"; y++;
                if (c<5){
                    //cout << "Please try again (You only have " << 6-c << " more chances)\n\n";
                    cout << "Xin vui lòng thử lại. \n"; y++;
                    cout << "(Lưu ý: Nếu nhập sai " << 6-c << " lần nữa thẻ của bạn sẽ bị khóa)\n\n"; y+=2;
                }
                else if (c==5){
                    //cout << "Please try again (YOU ONLY HAVE 1 MORE CHANCE!)\n\n";
                    cout << "Xin vui lòng thử lại. (BẠN CÒN 1 LẦN THỬ DUY NHẤT)\n\n"; y+=2;
                }
                else if (c>5){
                    //cout << "You have entered incorrect password more than 5 times.\n";
                    //cout << "Your card is locked. Bạn hãy đến ngân hàng gần nhất để được hỗ trợ mở khóa.\n";
                    cout << "Bạn đã nhập sai mật khẩu nhiều hơn 5 lần liên tiếp.\n"; y++;
                    cout << "♠ Thẻ của bạn đã bị khóa.\n"; y++;
                    cout << "Xin vui lòng đến ngân hàng gần nhất để được hổ trợ mở khóa.\n\n"; y+=2;
                    textcolor(15); //white
                    client.unlock = 0;                       // khoa the
                    UpdatetoList(client);                    // update to List
                    Update_List();                           // update List to file du lieu
                    system("PAUSE");
                    return true;

                }
            }
            else {
                //cout << "Không tồn tại thẻ. Mời nhập lại \n"; y++;
                cout << "Không tồn tại thẻ. Mời nhập lại \n"; y++; //cout << client.id << "\t" << client.pass << "\n";
                //cout << "This card does not exist. Please try again \n\n";
                c=0;
            }
        }
        idprev = client.id;
    }
    while (c<=5);
    return true;
}

// Sign up (Đăng ký)
void signup(Account &client){
    bool checkid, check, isturnback=false;
    int x=45,y=10; // vị trí cursor

    Account nacc;
    nacc.stt = num_people+1;


    do {
        textcolor(15);  // white
        cout << "ID (không dấu, không chứa dấu cách):       "; x=45; y++;     cin_wchs2s_unhide(nacc.id,x,y,isturnback); //cin_ws2s(nacc.id);
        if (isturnback){
            return;
        }
        cout << "Mật khẩu (không dấu, không chứa dấu cách): "; x=45; y++;     cin_wchs2s_unhide(nacc.pass,x,y,isturnback); //cin_ws2s(nacc.pass);
        if (isturnback){
            return;
        }

        checkAcc(nacc.id,nacc.pass,checkid,check);
        if (checkid){
            textcolor(12);  // red
            cout << "ID trên đã tồn tại. Xin vui lòng nhập số ID khác!\n\n"; y+=2;
        }
    } while (checkid);


    cout << "Nhập họ và tên:  ";
    //cin.ignore(); getline(cin,nacc.name);
    wcin.ignore(); getline_ws2s(nacc.name); y++;


    nacc.money=0;
    nacc.unlock=true;
    num_people++;

    UpdatetoList(nacc);
    Update_List();

    textcolor(10);  // green
    cout << "Đăng ký tài khoản thành công!\n\n"; y+=2;
    //cout << "Mời quý khách đăng nhập!\n";
    textcolor(15);  // white
    system("PAUSE");
    return;
}

// 1. Login Or Signup Or Exit:
void Login_Signup_Exit(Account &client){
    system("CLS");

    textcolor(14);  // yellow
    cout <<   "================== <<>> QUỲNH's BANK <<>> ==================\n"; //length=60
    cout <<   "|                                                          |\n";
    cout <<   "|        Mời quý khách chọn Đăng nhập hoặc Đăng ký:        |\n";
    cout <<   "|(Sử dụng các phím ↑ ↓ và phím Enter để chọn, Esc để thoát)|\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|    ♦ Đăng nhập                                           |\n";
    cout <<   "|    ♦ Đăng ký                                             |\n";
    cout <<   "|                                                          |\n";
    cout <<   "|                                                          |\n";
    cout <<   "============================================================\n";


    xnow=5; ynow=6;
    int poschoice[][2] = {
        {5,6}, {5,7}//, {5,8}
    };
    int fn=1;
    string text[][2] = {
        "♦ Đăng nhập ", "14",
        "♦ Đăng ký ", "14",
        //"♦ Thoát ", "14"
    };
    MoveCursorUpDownAndChoose(xnow, ynow, poschoice, text, 2, fn);

    // exit
    if (fn==27){ //Backspace 8 || Esc 27 || Thoát ynow==8
        system("CLS");
        textcolor(14);  // yellow
        cout <<   "================== <<>> QUỲNH's BANK <<>> ==================\n"; //length=60
        cout <<   "|                                                          |\n";
        cout <<   "|                                                          |\n";
        cout <<   "|                                                          |\n";
        cout <<   "|                     ♪♪♪ Tạm biệt  ♪♪♪                    |\n";
        cout <<   "|                ☺ Chúc một ngày tốt lành ☺                |\n";
        cout <<   "|                                                          |\n";
        cout <<   "|                                                          |\n";
        cout <<   "|                                                          |\n";
        cout <<   "|                                                          |\n";
        //cout <<   "|                             © Bản quyền thuộc về quynhnt |\n";
        cout <<   "|                                   © Copyright by quynhnt |\n";
        cout <<   "============================================================\n";
        textcolor(15); // white
        pause(700);
        exit(1);


    }

    // signup
    if (ynow==7){
        xnow=0; ynow=11;
        gotoxy(xnow,ynow);
        signup(client);
        Login_Signup_Exit(client);
    }


    // login
    if (ynow==6){
        xnow=0; ynow=11;
        gotoxy(xnow,ynow);
        if (!login(client)){
            Login_Signup_Exit(client);
        }
    }
}



// 2. Choice Table
// Chức năng History
void saveHistory(Account &client, string loaigd, long long &number, string mess/*=""*/){
    // loại gd: gửi(unlimited) rút (tối đa 10tr) chuyển(unlimited) nhận(unlimited)
    // number: số tiền giao dịch

    string path = client.id + "_" + noaccent(client.name) + "_history.txt";
    fstream hisfile(path, std::ios::app);
    if (hisfile.is_open()){
        //  thông tin tk
        hisfile << "Số ID TK: " << client.id << endl;


        //TIME (TIME1 or TIME2)
        // ham time: tra ve thoi gian hien tai cua he thong tinh tu 1/1/1970
        time_t now = time(0);

        //TIME1: ~English format (day month date hours:minutes:seconds year\n\0)
        // ham ctime: convert time_t => tra ve 1 con tro tro toi 1 string format (day month date hours:minutes:seconds year\n\0)
//        hisfile << ctime(&now) << endl;

        //TIME2: ~Vietnamese format (dd/mm/yy   hours:minutes:seconds)
        // ham localtime tra ve con tro toi "cau truc tm" bieu thi local time
        tm *ltm = localtime(&now);
        string date = to_string(ltm->tm_mday) + "/" + to_string(1+ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
        string time = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);

        hisfile << setw(30+1+2) << left << "Ngày giao dịch:"; //hisfile << "|";
        hisfile << setw(23) << right << date+" "+time << endl;



        //LOẠI GIAO DỊCH (Gửi tiền +number/ Rút tiền -number/ ...)
        char ch; int numch=0;
        if (loaigd=="Gửi tiền") {ch='+'; numch=2+2;}
        else if (loaigd=="Rút tiền") {ch='-'; numch=1+2;}
        else if (loaigd=="Chuyển khoản") {ch='-'; numch=3+1;}
        else if (loaigd=="Nhận chuyển khoản") {ch='+'; numch=3+1+2;}
        hisfile << setw(30+2+2) << left << "Loại giao dịch:"; //hisfile << "|";
        hisfile << setw(23+numch) << right << loaigd << endl;


        //SỐ TIỀN GIAO DỊCH
        hisfile << setw(30+2+2+2) << left << "Số tiền giao dịch:"; //hisfile << "|";
        hisfile << setw(23) << right << ch + to_string(number) + " VND" << endl;

        //  số dư
        hisfile << setw(30+2+1) << left << "Số dư TK: ";
        hisfile << setw(23) << right << to_string(client.money) + " VND" << endl;


        //ND GIAO DỊCH
        if (mess!=""){
            hisfile << "Thông điệp:  " << mess << endl;
        }

        hisfile << endl;
    }
    hisfile.close();
}

void seeHistory(Account &client){
    textcolor(15);
    string path = client.id + "_" + noaccent(client.name) + "_history.txt", s;
    fstream hisfile(path, std::ios::in);
    if (hisfile.is_open()){
        while(!hisfile.eof()){
            getline(hisfile,s);

            if (s.find("Số tiền giao dịch")!=-1){
                cout << s.substr(0,36);
                s = s.substr(36,s.length()-36);
                if (s.find('-')!=-1) textcolor(12);
                else textcolor(10);
                cout << s << endl;
                textcolor(15);
            }
            else
                cout << s << endl;
        }
    }
    hisfile.close();
}

void saveHistoryNoAccent(Account &client, string loaigd, long long &number, string mess/*=""*/){
    string path = client.id + "_" + noaccent(client.name) + "_history(noaccent).txt";
    fstream hisfile(path, std::ios::app);
    if (hisfile.is_open()){
        //  thông tin tk
        hisfile << "So ID TK: " << client.id << endl;


        //TIME (TIME1 or TIME2)
        // ham time: tra ve thoi gian hien tai cua he thong tinh tu 1/1/1970
        time_t now = time(0);

        //TIME1: ~English format (day month date hours:minutes:seconds year\n\0)
        // ham ctime: convert time_t => tra ve 1 con tro tro toi 1 string format (day month date hours:minutes:seconds year\n\0)
//        hisfile << ctime(&now) << endl;

        //TIME2: ~Vietnamese format (dd/mm/yy   hours:minutes:seconds)
        // ham localtime tra ve con tro toi "cau truc tm" bieu thi local time
        tm *ltm = localtime(&now);
        string date = to_string(ltm->tm_mday) + "/" + to_string(1+ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
        string time = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);

        hisfile << setw(30) << left << noaccent("Ngày giao dịch:"); //hisfile << "|";
        hisfile << setw(23) << right << date+" "+time << endl;



        //LOẠI GIAO DỊCH (Gửi tiền +number/ Rút tiền -number/ ...)
        char ch; int numch=0;
        if (loaigd=="Gửi tiền") {ch='+'; numch=0;}
        else if (loaigd=="Rút tiền") {ch='-'; numch=0;}
        else if (loaigd=="Chuyển khoản") {ch='-'; numch=0;}
        else if (loaigd=="Nhận chuyển khoản") {ch='+'; numch=0;}
        hisfile << setw(30) << left << noaccent("Loại giao dịch:"); //hisfile << "|";
        hisfile << setw(23+numch) << right << noaccent(loaigd) << endl;


        //SỐ TIỀN GIAO DỊCH
        hisfile << setw(30) << left << noaccent("Số tiền giao dịch:"); //hisfile << "|";
        hisfile << setw(23) << right << ch + to_string(number) + " VND" << endl;


        //  số dư
        hisfile << setw(30) << left << noaccent("Số dư TK: ");
        hisfile << setw(23) << right << to_string(client.money) + " VND" << endl;


        //ND GIAO DỊCH
        if (mess!=""){
            hisfile << noaccent("Thông điệp: ") << mess << endl;
        }

        hisfile << endl;
    }
    hisfile.close();
}

// Chức năng Gửi tiền
void guitien(Account &client){
    int menhgia;//, num;
    long long sum=0, num;
    bool check, isturnback;
    wchar_t done;

    int x,y; // vị trí chọn mệnh giá
    x=1;
    if (client.name=="ADMIN")
        y=19;
    else y=17;

    do{
        done = check = false;
//        do{
            // Nhập mệnh giá
//            textcolor(15);  // white
//            cout << "Nhập mệnh giá \n(10,000; 20,000; 50,000; 100,000; 200,000; 500,000) VND: \n";
//            textcolor(10);  // green
//            wcin >> menhgia;

            // Chọn mệnh giá
                textcolor(15);  // white
                cout << "Chọn mệnh giá: \n(10,000; 20,000; 50,000; 100,000; 200,000; 500,000) VND\n"; y+=2;

                x=1;
                int poschoice[][2] = {
                    {1,y}, {9,y}, {17,y}, {25,y}, {34,y}, {43,y}
                };
                int fn;
                string text[][2] = {
                    "10,000", "15",
                    "20,000", "15",
                    "50,000", "15",
                    "100,000", "15",
                    "200,000", "15",
                    "500,000", "15"
                };
                MoveCursorLeftRightAndChoose(x, y, poschoice, text, 6, fn);
                if (fn==27){ //ESC==27; ENTER==13; BACKSPACE==8; OTHERS
                    //choice_table(client);
                    return;
                }
                switch (x){
                    case 1: menhgia = 10000; break;
                    case 9: menhgia = 20000; break;
                    case 17: menhgia = 50000; break;
                    case 25: menhgia = 100000; break;
                    case 34: menhgia = 200000; break;
                    case 43: menhgia = 500000; break;
                }



            // Nhập số tờ
            for (int i=0; i<6; i++)
                if (menhgia==money[i][0])
                {
                    x=0; y++;
                    gotoxy(x,y);
                    textcolor(15);  // white
                    cout << "Nhập số tờ (>0 & <=500): ";
                    textcolor(10);  // green


                    // đúng mệnh giá -> nhập số tờ
                    //wcin >> num;            y++;
                    cin_wchs2ll(num,25,y,isturnback); y++;
                    if (isturnback){
                        //choice_table(client);
                        return;
                    }
                    while (num<=0 || num>500){
                        textcolor(12);  // red
                        cout << "Giá trị bạn vừa nhập không hợp lệ.\n"; y++;
                        textcolor(15);  // white
                        cout << "Nhập lại số tờ: ";
                        textcolor(10);  // green
                        cin_wchs2ll(num,16,y,isturnback); y++;//wcin >> num; y++;
                        if (isturnback){
                            //choice_table(client);
                            return;
                        }
                    }
                    textcolor(14);  // yellow
                    cout << "ATM đã nhận: " << num << " tờ " << menhgia << " VND.\n\n"; y+=2;

                    client.money += num*menhgia; // + tien vao tai khoan user
                    money[i][1] += num;      // update tien vao ATM
                    sum += num*menhgia;          // tong tien gui vao hien tai


                    UpdatetoList(client);                    // update to List
                    Update_List();                           // update List to file dữ liệu
                    saveHistory(client, "Gửi tiền", sum);
                    //saveHistoryNoAccent(client, "Gửi tiền", sum);


//                    check = true;
                    break;
                }
//            if (check) break;
//            else{
//                textcolor(12);  // red
//                cout << "Bạn đã nhập sai mệnh giá, xin vui lòng nhập lại!\n";
//            }
//
//        } while (true);

        textcolor(14);  // yellow
        //cout << "Do you want to continue? [Y/N]:  ";
        cout << "Bạn có muốn tiếp tục nạp không? [Y/N]:  ";
        wcin >> done;
        cout << endl;       y++;
    }
    while (toupper(done)=='Y');

    textcolor(14);  // yellow
    cout << "-> Tổng số tiền đã gửi: ";
    textcolor(10);  // green
    cout << sum;
    textcolor(14);  // yellow
    cout << " VND.\n\n";
    textcolor(15);  // white
}


// Chức năng Rút tiền
bool FantasticGreedy(int moneyout[][2], int st, int en, const int &mon){
    //moneyout là mảng chứa mệnh giá từ lớn -> nhỏ và số lượng tương ứng hiện có trong ATM
    //st:0 -> en: số phần tử mảng moneyout
    //mon: số tiền khách muốn rút

    int sum=0, a[6][2], p=st;
    memcpy(a, moneyout, 2*en*(sizeof(int)) );

    while (sum!=mon){
        for (int i=p; i<en; i++)
            if (mon-sum >= a[i][0] && a[i][1]>0){
                int num = (mon-sum)/a[i][0];
                num = (num<=a[i][1]? num : a[i][1]);
                a[i][1] -= num;
                //cout << a[i][0] << " * " << num << endl;
                sum += num*a[i][0];
            }
        //if (sum==mon) break;

        if (sum!=mon && p<en) {
            p++;
            sum=0;
            memcpy(a, moneyout, 2*en*(sizeof(int)) );
            //cout << "new\n";
        }
        if (sum!=mon && p>=en) return false;
    }


    if (sum==mon){
        for (int i=st; i<en; i++)
            moneyout[i][1] = a[i][1];
        return true;
    }
}

void ruttien(Account &client){
    bool isturnback = false;

    if (client.money<=0){
        textcolor(12);  // red
        cout << "Số dư tài khoản của quý khách không đủ.\n";
        cout << "Xin vui lòng nạp thêm tiền để thực hiện giao dịch này.\n";
        textcolor(15);  // white
        return;
    }


    int moneyout[6][2], c=0;
    long long sum=0;

    //Cac dieu kien rang buoc
    textcolor(15);  // white
    cout << "\n   Số tiền rút tối đa cho mỗi giao dịch là 10 triệu VND.\n\n";
    cout << "Số tiền nhập vào phải là bội số của các mệnh giá sau:\n"; // ADMIN pos x,23 OTHERS pos x,21
    for (int i=6-1; i>=0; i--){
        if (money[i][1]>0){
            moneyout[c][0] = money[i][0];
            moneyout[c][1] = money[i][1];
            c++;
            cout << c << ") " << money[i][0] << " VND\n";
        }
    }   // mang moneyout luu cac to tien menh gia tu cao -> thap va so luong tuong ung (tu phan tu 0->c-1)

    //Nhap tien muon rut
    cout << "\n   Mời quý khách nhập số tiền muốn rút (VND): ";
    textcolor(12);  // red
    if (client.name=="ADMIN")
        cin_wchs2ll(sum,46,23+c+2, isturnback); //wcin >> sum;
    else
        cin_wchs2ll(sum,46,21+c+2, isturnback);
    if (isturnback){
        //choice_table(client);
        return;
    }

    //KTRA
    //Ktra0:
    if (sum<=0){
        textcolor(14);  // yellow
        cout << "Vui lòng nhập số tiền muốn rút có giá trị > 0 VNĐ.\n\n";
        textcolor(15);  // white
        return;
    }

    //Ktra1: tiền rút có vượt quá giới hạn cho phép hay ko (10trVND)
    if (sum>10000000){
        textcolor(12);  // red
        cout << "Số tiền vừa nhập vượt quá giới hạn cho phép (10 triệu VNĐ).\n\n";
        cout << "Xin quý khách vui lòng thử lại sau.\n";
        textcolor(15);  // white
        return;
    }

    //Ktra2: có >= số dư TK hay ko
    if (sum>client.money){
        textcolor(12);  // red
      //cout << "================== <<>> QUYNH's BANK <<>> ==================\n\n"; //length=60
        cout << "Số dư TK của quý khách không đủ để thực hiện giao dịch này.\n";
        cout << "Xin vui lòng kiểm tra lại số dư TK và thử lại sau.\n\n";
        textcolor(15);  // white
        return;
    }

    //Ktra3: ATM còn đủ tiền trả hay ko
    if (calATMsmoney()<sum){
        textcolor(14);  // yellow
        cout << "Cây ATM hiện tại không đủ tiền để trả cho quý khách.\n";
        cout << "Xin quý khách vui lòng thử lại sau.\n";
        textcolor(15);  // white
        return;
    }

    //Ktra4: so tien nhap co la boi so cac to tien trong cay ATM hay ko
    if (!FantasticGreedy(moneyout,0,c,sum) ){
        textcolor(14);  // yellow
        cout << "Số tiền vừa nhập không là bội số của các mệnh giá nêu trên.\n";
        cout << "Xin quý khách vui lòng thử lại sau.\n";
        textcolor(15);  // white
        return;
    }

    else {
    //Rut tien (So to lay ra la it nhat)
    //Rut tien1: - tien vao tai khoan user
        client.money -= sum;
    //Rut tien2: update tien trong ATM
        for (int i=6-1; i>=0; i--){
            for (int j=0; j<c; j++){
                if (money[i][0]==moneyout[j][0])
                    money[i][1] = moneyout[j][1];
            }
        }
    //Rut tien3: Hien thi rut tien thanh cong
      //cout <<   "================== <<>> QUYNH's BANK <<>> ==================\n\n"; //length=60
        textcolor(14);  // yellow
        cout << "\n\tGiấy được sản xuất từ gỗ.\n";
        cout <<   "   Hàng năm, chúng ta mất đi hàng ngàn hecta rừng để phục vụ\n";
        cout <<   "   cho sản xuất giấy.\n";
        cout <<   "   Hãy bảo vệ môi trường sống và bảo vệ rừng của chúng ta\n";
        cout <<   "   bằng cách không in biên lai nếu thực sự không cần thiết.\n";
        cout << "\tXin cảm ơn quý khách!\n\n";
        textcolor(15);  // white


    //Ruttien4: In bien lai or not



    //Ruttien5: Cam on cac thu


    }

    UpdatetoList(client);                   // update to List
    Update_List();                           // update List to file du lieu
    saveHistory(client, "Rút tiền", sum);
    //saveHistoryNoAccent(client, "Rút tiền", sum);
}


// Chức năng Chuyển khoản
void chuyenkhoan(Account &client){
    bool isturnback=false;
    int x,y; //pos x,y

    if (client.money==0){
        textcolor(12);  // red
        cout << "Số dư tài khoản của quý khách không đủ.\n";
        cout << "Xin vui lòng nạp thêm tiền để thực hiện giao dịch này.\n";
        textcolor(15);  // white
        return;
    }

    string _id, _name, mess;
    bool check_id,check;
    long long cvmoney;
    textcolor(15); //white
    cout << setw(8+2) << left << "Từ: " << client.name << endl;
    cout << setw(8) << " " << "ID " + client.id << endl;
    cout << setw(8) << " " << "VND " << client.money << "\n";

    cout << "Chuyển đến:\n";
    cout << setw(8) << " " << "Nhập số ID tài khoản thụ hưởng: ";
    x=40; y=24;
    if (client.name!="ADMIN") y-=2;

    cin_wchs2s_unhide(_id,x,y,isturnback); //cin_ws2s(_id);
    if (isturnback){
        //choice_table(client);
        return;
    }

    Account desti = checkAcc(_id,"",check_id,check);
    if (check_id){
        if (desti.id==client.id){
            textcolor(12);  // red
            cout << "Bạn không thể thực hiện thao tác này. \nXin vui lòng thử lại sau.\n\n";
            textcolor(15);  // white
            return;
        }
        else{
            cout << setw(8) << " " << desti.name << endl;
        cout << "Nhập số tiền (VND): ";
        wcin >> cvmoney;
            if (cvmoney>client.money || cvmoney<=0){
                textcolor(12);  // red
                cout << "Số tiền không hợp lệ.\n";
                textcolor(15);  // white
            }
            else{
                cout << "\nNội dung thông điệp (ấn phím Enter để gửi): \n";
                //cout << setw(8) << " " ;
                textcolor(11); // cyan
                wcin.ignore(); getline_ws2s(mess);
                textcolor(15); // white
                cout << endl;

                client.money -= cvmoney;
                desti.money += cvmoney;

                UpdatetoList(client);                   // update to List
                UpdatetoList(desti);

                Update_List();                           // update List to file du lieu
                saveHistory(client, "Chuyển khoản", cvmoney, mess);
                saveHistory(desti, "Nhận chuyển khoản", cvmoney, mess);
                //saveHistoryNoAccent(client, "Chuyển khoản", cvmoney, mess);
            }
        }
    }
    else{
        textcolor(12);  // red
        cout << "Tài khoản này không tồn tại. \nXin quý khách vui lòng thử lại sau.\n";
        textcolor(15);  // white
    }
}

// Chức năng Change Password
void changePass(Account &client){
    bool isturnback = false;
    int x,y;
    string opass,npass1,npass2;
  //cout << "================== <<>> QUYNH's BANK <<>> ==================\n\n"; //length=60
    textcolor(14);  // yellow
    cout << "          ĐỔI MẬT KHẨU ĐĂNG NHẬP - CHANGE PASSWORD          \n";
    textcolor(15);  // white
    cout << setw(53) << "Mật khẩu là một xâu ký tự không chứa dấu cách, \ntiếng Việt không dấu.\n";
    if (client.name=="ADMIN") y=23;
    else y=21;
    cout << "Nhập mật khẩu hiện tại:   ";   x=27;       cin_wchs2s_hide(opass,x,y,isturnback); //cin_ws2s(opass);
    if (isturnback){
        //choice_table(client);
        return;
    }
    cout << "Nhập mật khẩu mới:        ";   x=27; y++;  cin_wchs2s_hide(npass1,x,y,isturnback); //cin_ws2s(npass1);
    if (isturnback){
        //choice_table(client);
        return;
    }
    cout << "Nhập lại mật khẩu mới:    ";   x=27; y++;  cin_wchs2s_hide(npass2,x,y,isturnback); //cin_ws2s(npass2);
    if (isturnback){
        //choice_table(client);
        return;
    }

    if (opass!=client.pass){
        textcolor(12);  // red
        cout << opass << "\t" << client.pass << " Mật khẩu hiện tại không chính xác!\n";
        textcolor(15);  // white
        return;
    }
    if (npass1!=npass2){
        textcolor(12);  // red
        cout << "Mật khẩu mới không khớp!\n";
        textcolor(15);  // white
        return;
    }
    if (npass1=="" || npass1==opass){
        textcolor(12);  // red
        cout << "Mật khẩu mới không hợp lệ!\n";
        textcolor(15);  // white
        return;
    }

    client.pass = npass1;
    UpdatetoList(client);                    // update client to List
    Update_List();                           // update List to file du lieu

    textcolor(10);  // green
    cout << "Đổi mật khẩu thành công!\n\n";
    textcolor(15);  // white
}


// 2. Choice Table
void choice_table(Account &client){
    system("CLS");
    int ischoice=1, fn;
    xnow=3;
    int poschoice[10][2];
    poschoice[0][0]=2;
    poschoice[0][1]=7;
    for (int i=1; i<9; i++){
        poschoice[i][0] = 2;
        poschoice[i][1] = poschoice[i-1][1]+1;
    }

    if (client.id!=List[0].id && client.unlock)
        do{
            textcolor(14);  // yellow
            cout <<   "================== <<>> QUỲNH's BANK <<>> ==================\n\n"; //length=60
            cout <<   "                     Welcome - Chào mừng                    \n";
            textcolor(11);  // cyan ~ xanh ngoc
            cout << setw((60-noaccent(client.name).length())/2) << " " << client.name << "\n";

            textcolor(14);  // yellow
            cout << "\n============== Xin vui lòng lựa chọn giao dịch =============\n";
            cout <<   "|                                                          |\n";
            cout <<   "|  Gửi tiền                                                |\n";
            cout <<   "|  Rút tiền                                                |\n";
            cout <<   "|  Xem số dư tài khoản                                     |\n";
            cout <<   "|  Xem lịch sử giao dịch                                   |\n";
            cout <<   "|  Chuyển khoản                                            |\n";
            cout <<   "|  Đổi mật khẩu                                            |\n";

            if (client.name=="ADMIN"){

            cout <<   "|  ";
            textcolor(11);  // cyan ~ xanh ngoc
            cout <<       "Xem danh sách Account                                   ";
            textcolor(14);  // yellow
            cout << "|\n";


            cout <<   "|  ";
            textcolor(11);  // cyan ~ xanh ngoc
            cout <<       "Xem trạng thái ATM                                      ";
            textcolor(14);  // yellow
            cout << "|\n";

            }
            cout <<   "|  Đăng xuất                                               |\n";
            cout <<   "|                                                          |\n";
            cout <<   "============================================================\n";
            //cout << "\nBạn chọn? \n";
            textcolor(15);  // white



            if (client.name=="ADMIN"){
                string text[][2]={
                "Gửi tiền ", "14",
                "Rút tiền ", "14",
                "Xem số dư tài khoản ", "14",
                "Xem lịch sử giao dịch ", "14",
                "Chuyển khoản ", "14",
                "Đổi mật khẩu ", "14",

                "Xem danh sách Account ", "11",
                "Xem trạng thái ATM ", "11",

                "Đăng xuất ", "14"
                };
                MoveCursorUpDownAndChoose(xnow, ynow, poschoice, text, 9, fn);

                gotoxy(0,20);
            }
            else {
                string text[][2]={
                "Gửi tiền ", "14",
                "Rút tiền ", "14",
                "Xem số dư tài khoản ", "14",
                "Xem lịch sử giao dịch ", "14",
                "Chuyển khoản ", "14",
                "Đổi mật khẩu ", "14",

                "Đăng xuất ", "14"
                };
                MoveCursorUpDownAndChoose(xnow, ynow, poschoice, text, 7, fn);

                gotoxy(0,18);
            }

            if (fn==27){ //Esc 27, Backspace 8
                thankyou();
                return;
            }
            else if (fn==8){}
            else{
                switch(ynow){
                case 7: guitien(client); break;
                case 8: ruttien(client); break;
                case 9: client.Display(); break;
                case 10: seeHistory(client); break;
                case 11: chuyenkhoan(client); break;
                case 12: changePass(client); break;
                case 13:
                    if (client.name!="ADMIN") return;
                    else Display_List();
                    break;
                case 14:
                    if (client.name=="ADMIN") showsATMsmoney(); break;
                case 15:
                    if (client.name=="ADMIN") return; break;
                }
                system("PAUSE");
                system("CLS");
            }

        } while (true);
    textcolor(15); // white
}


