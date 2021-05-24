#include "2account.h"

//Global variable - account
int num_people;
int money[][2]={
    {10000,0},{20000,0},{50000,0},{100000,0},{200000,0},{500000,0} //VND
};
long long ATMsmoney=0;

Account List[maxsizeOfList+1]; // from 1 -> num_people


/* Struct Account */
Account::Account (int _stt, string _id, string _pass, string _name, long long _money, bool _unlock /*=true*/){
    stt = _stt;
    id = _id;
    pass = _pass;
    name = _name;
    money = _money;
    unlock = _unlock;
}

istream& operator>> (istream& in, Account &x){
    in >> x.stt;
    in >> x.id;
    in >> x.pass;
    in.ignore(); getline(in,x.name);
    in >> x.money;
    in >> x.unlock;
    return in;
}

ostream& operator<< (ostream& out, Account &x){
    out << x.stt << endl;
    out << x.id << endl;
    out << x.pass << endl;
    out << x.name << endl;
    out << x.money << endl;
    out << x.unlock << endl;
    return out;
}

void Account::Set (int _stt, string _id, string _pass, string _name, long long _money, bool _unlock){
    stt = _stt;
    id = _id;
    pass = _pass;
    name = _name;
    money = _money;
    unlock = _unlock;
}

void Account::Display(){
    textcolor(15);  //white
    //cout << "Stt: \t" << stt << "\n";
    cout << "ID:          " << setw(20) << right << id + "\n";
    cout << "Họ tên:      " << setw(20+name.length()-noaccent(name).length()) << right << name + "\n";
    cout << "Số dư:       " << setw(20) << right << to_string(money) + " VND\n";
    cout << "Trạng thái:  ";
    //cout << "Status: ";
    if (unlock){
        textcolor(10); // green
        cout << setw(20+2+2) << right << "mở khóa\n\n";
        textcolor(15); // white
    }
    else{
        textcolor(12); // red
        cout << setw(20+2) << right << "khóa\n\n";
        textcolor(15); // white
    }
}





/* List Function */
void Set_List(){
    ifstream file("Dulieu.txt");
    if (file.is_open()){
        file >> num_people;
        for (int i=0; i<=num_people; i++)
            file >> List[i];
        for (int i=0; i<6; i++)
            file >> money[i][1]; // so luong to tien theo cac menh gia VND tang dan
    }
    file.close();
}

void Display_List(){
    textcolor(15); //white
    cout << num_people << " Account:" << endl << endl;
    for (int i=1; i<=num_people; i++){
        List[i].Display();
    }
    //system("PAUSE");
}

void UpdatetoList(Account &client){ /* Update Account client to List */
    List[client.stt].Set(client.stt,client.id,client.pass,client.name,client.money,client.unlock);
}

void Update_List(){
    ofstream udfile("Dulieu.txt");
    if (udfile.is_open()){
        udfile << num_people << endl << endl;
        for (int i=0; i<=num_people; i++){
            udfile << List[i] << endl;
        }
        for (int i=0; i<6; i++){
            udfile << money[i][1] << " "; // so luong to tien theo cac menh gia VND tang dan
        }
    }
    udfile.close();
}










long long calATMsmoney(){
    ATMsmoney=0;
    for (int i=0; i<6; i++){
        if (money[i][1])
            ATMsmoney += money[i][0]*money[i][1];
    }
    return ATMsmoney;
}

void showsATMsmoney(){ // dung bien global: int money[][2], long long ATMsmoney
    calATMsmoney();
    textcolor(14); //yellow
    //cout <<   "================== <<>> QUỲNH's BANK <<>> ==================\n\n"; //length=60
    cout <<     "                       TRẠNG THÁI ATM                       \n";
    cout <<     "♦ Số dư: " << ATMsmoney << " VND\n";
    cout <<     "♦ Các mệnh giá: \n";

    for (int i=0; i<6; i++){
        if (money[i][1]){
            cout << "Mệnh giá " << setw(6) << right << money[i][0] << " VND: ";
            cout << setw(5) << right << money[i][1] << " tờ\n";
        }
    }
    textcolor(15); // white
    cout << endl;
    //system("PAUSE");
}



