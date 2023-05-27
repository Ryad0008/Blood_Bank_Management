/*

Requrment for this project...
1.Knowledge of c++
2.Basics of OOP // Main things
3.main features of OOP 

i) Abstruction
ii) Encapsulation
iii) Inheritance
iv) polymorphism

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
using namespace std;

string getCurrentDateTime();

//It is a Abstruct class we can't create any objects

class FileOperation{

//This function is used to occur Run time Polymorphism

    virtual void Save() = 0;
};

//This calss 
class Donar : virtual public FileOperation //Daimond shape problem aries here
{
private:
    //Encapsulated properties

    string name1,name2;
    long long roll;
    string dept;
    string bg;
    string phn;

public:
    //Constructors

    Donar() {}
    Donar(string name1,string name2, long long roll, string dept, string bg,string phn) {
        this->name1 = name1;
        this->name2 = name2;
        this->roll = roll;
        this->dept = dept;
        this->bg = bg;
        this->phn = phn;
    }
    //Memberfunctions to access private properties

    string getName1() const {
        return name1;
    }
    string getName2() const {
        return name2;
    }

    long long getRoll() const {
        return roll;
    }

    string getDept() const {
        return dept;
    }

    string getBg() const {
        return bg;
    }
    string getPhn() const{
        return phn;
    }
    // To save into a file
    //here runtime polymorphism is occur for save function

    void Save() {
        ofstream fout("donar.txt", ios::app);
        if (!fout) {
            cout << "Error opening file." << endl;
            return;
        }

        fout << name1<<" "<<name2 << " " << roll << " " << dept << " " << bg <<" "<<phn<< endl;
        fout.close();
    }
    //To show donar list from file on console

    void showDonar() const {

        cout <<"name:"<< name1<<" " <<name2<<" " << "roll: " << roll << " " <<"dept:"<< dept << " " <<"blood_group:"<< bg <<" "<<"phone_number:"<<phn<< endl;

    }

    string showBloodGroup() const {
        return bg;
    }
    //here i use friend function to overload istream

    friend istream& operator>>(istream& in, Donar& donar) {
        in >> donar.name1>>donar.name2 >> donar.roll >> donar.dept >> donar.bg>>donar.phn;
        return in;
    }

};


class Acceptor : virtual public FileOperation //Dimond shape problem aries here
{
private:
    //Encapsulated properties

    string name1,name2;
    long long id;
    string phn;
    string acbg;

public:
    // Constructors

    Acceptor() {}
    Acceptor(string name1,string name2, long long id, string phn,string acbg) {
        this->name1 = name1;
        this->name2 = name2;
        this->id = id;
        this->phn = phn;
        this->acbg = acbg;
    }
    // to write into a file
    // here runtime polymorphism is occur for save function

    void Save() {
        ofstream fout("acceptor.txt", ios::app);
        if (!fout) {
            cout << "Error opening file." << endl;
            return;
        }

        fout << name1<<" "<<name2<<" " << " " << id << " " << phn <<" "<<acbg<< endl;

        fout.close();
    }

    // to show acceptor list on console

    void showAcceptor() const {
        cout <<"name: "<< name1<<" "<<name2<<" " << "NID: " << id << " " <<"phone: "<< phn << " "<<"acceptor_blood_group: "<<acbg<<endl;
    }

    // member functions to acces private properties 

    string getACname1() const {
        return name1;
    }
    string getACname2() const {
        return name2;
    }

    long long getACid() const {
        return id;
    }

    string getACphn() const {
        return phn;
    }
    string getacbg() const{
        return acbg;
    }

    //using friend function overloading istream

    friend istream& operator>>(istream& in, Acceptor& ac) {
        in >> ac.name1>>ac.name2 >> ac.id >> ac.phn>>ac.acbg;
        return in;
    }
};


class BloodBank : public Donar, public Acceptor 
{
private:
    string date;
public:
    //Constructors

    BloodBank() {}
    BloodBank(Donar d, Acceptor ac, string date=getCurrentDateTime()) : Donar(d.getName1(),d.getName2(), d.getRoll(), d.getDept(), d.getBg(),d.getPhn()), Acceptor(ac.getACname1(),ac.getACname2(), ac.getACid(), ac.getACphn(),ac.getacbg()) {
        this->date = date;
    }
    //to save bank list into a file

    void Save() {
        ofstream fout("bank.txt", ios::app);
        if (!fout) {
            cout << "Error opening file." << endl;
            return;
        }
        fout << getName1()<<" "<<getName2() << " " << getRoll() << " " << getDept() << " " << getBg() << " " <<getPhn()<<" "<< getACname1()<<" "<<getACname2() << " " << getACid() << " " << getACphn() << " "<< date << endl;
        fout.close();
    }

    // to show bank list on console

    void viewBank() const {
    cout <<"Donar_Name:"<< Donar::getName1()<<" "<<Donar::getName2() <<endl<<"roll:"<< Donar::getRoll() <<endl<<"Dept:"<< Donar::getDept() <<endl<<"blood_group:"<< Donar::getBg()
        <<endl<<"phone_number:"<< Donar::getPhn() << endl <<"Acceptor_name:"<< Acceptor::getACname1()<<" "<<Acceptor::getACname2() <<endl<<"NID:"<< Acceptor::getACid()
        <<endl<<"phone_number:"<< Acceptor::getACphn() <<endl<<"Date:"<< date << endl;
}

// to call all constructors to set values

friend istream& operator>>(istream& in, BloodBank& bd) {

    string sname1,sname2,dept,bg,ph,aph,aname1,aname2;
    long long id,roll;

    in >> sname1>>sname2 >> roll >> dept >> bg >> ph >> aname1>>aname2 >> id >> aph >> bd.date;

    Donar d(sname1,sname2,roll,dept,bg,ph);
    Acceptor a(aname1,aname2,id,ph,bg);

    BloodBank h(d,a,bd.date);
    bd = h;

    return in;
}

};

//This function is used to show all donar list
void viewAllDonar() {

    Donar tmp;
    //this is used to open file as a read mode
    ifstream fin("donar.txt");
    if (!fin) {
        cout << "File not found." << endl;
    }
    else {
        cout<<"Donar List:"<<endl;
cout<<"|****************************************************************************|"<<endl;
        while (fin >> tmp) {
            tmp.showDonar();
        }
cout<<"|****************************************************************************|"<<endl;
        fin.close();
    }
}

//This function is used to show all acceptor list
void viewAllAcceptor() {
    Acceptor tmp;
    ifstream fin("acceptor.txt");
    if (!fin) {
        cout << "File not found." << endl;
    }
    else {
        cout<<"Acceptor List:"<<endl;
cout<<"|****************************************************************************|"<<endl;
        while (fin >> tmp) {
            tmp.showAcceptor();
        }
cout<<"|****************************************************************************|"<<endl;
        fin.close();
    }
}

Acceptor UpdateAcceptor(string acbg) {
    cout << "Blood Found" << endl;
    cout << "Enter first name: ";
    string name1,name2;
    cin>>name1;
    cout<<"Enter last name: ";
    cin>>name2;
    cout << "Enter national id number: ";
    long long id;
    cin >> id;
    cout << "Enter phone Number: ";
    string phn;
    cin >> phn;
    //temporary object to set values
    Acceptor ac(name1,name2,id,phn,acbg);
    ac.Save();
    return ac;
}

//This function is used to match blood group(donar and acceptor)
bool searchBlood(string bloodGroup) {
    //STL is used to store donar object
    vector<Donar> v;
    Donar dnr;
    bool found = false;
    Donar tmp;

    ifstream fin("donar.txt");
    if (!fin) {
        cout << "File not found." << endl;
    }
    else {
        while (fin >> tmp) {
            if (tmp.getBg() == bloodGroup && !found) {
                found = true;
                dnr = tmp;
                Acceptor ac = UpdateAcceptor(bloodGroup);
                BloodBank bd(tmp, ac);
                bd.Save();
            }
            else {
                v.push_back(tmp);
            }
        }
        fin.close();
    }

    if (found) {
        ofstream fout;
        fout.open("donar.txt", ios::out);
        for (int i = 0; i < v.size(); i++) {
            v[i].Save();
        }
        fout.close();
        return true;
    }
    return false;
}


//This function is used to show current date on console
string getCurrentDateTime() {

    time_t now = time(nullptr);
    char formattedDateTime[12];
    strftime(formattedDateTime, sizeof(formattedDateTime), "%m/%d/%Y", localtime(&now));
    return formattedDateTime;
}

//This function is used to see all donar and acceptor details
void viewAllBank() {

    BloodBank tmp;
    ifstream fin("bank.txt");
    if (!fin) {
        cout << "File not found." << endl;
    }
    else {
        cout<<"Total Blood Bank List:"<<endl;
cout<<"|***************************************************************************|"<<endl;
        while (fin >> tmp) {
            tmp.viewBank();
        }
cout<<"|***************************************************************************|"<<endl;
        fin.close();
    }
}

//This function is used to verify blood group is valid or not?

bool check(const string& bg) {
    switch (bg[0]) {
        case 'A':
            switch (bg[1]) {
                case 'B':
                    if (bg == "AB+" || bg == "AB-")
                        return true;
                    break;
                case '+':
                    if (bg == "A+" || bg == "AB+")
                        return true;
                    break;
                case '-':
                    if (bg == "A-" || bg == "AB-")
                        return true;
                    break;
            }
            break;
        case 'B':
            switch (bg[1]) {
                case '+':
                    if (bg == "B+" || bg == "AB+")
                        return true;
                    break;
                case '-':
                    if (bg == "B-" || bg == "AB-")
                        return true;
                    break;
            }
            break;
        case 'O':
            switch (bg[1]) {
                case '+':
                    if (bg == "O+")
                        return true;
                    break;
                case '-':
                    if (bg == "O-" || bg == "A-" || bg == "B-" || bg == "AB-")
                        return true;
                    break;
            }
            break;
        case 'a':
            switch (bg[1]) {
                case '+':
                    if (bg == "a+" || bg == "ab+")
                        return true;
                    break;
                case '-':
                    if (bg == "a-" || bg == "ab-")
                        return true;
                    break;
            }
            break;
        case 'b':
            switch (bg[1]) {
                case '+':
                    if (bg == "b+" || bg == "ab+")
                        return true;
                    break;
                case '-':
                    if (bg == "b-" || bg == "ab-")
                        return true;
                    break;
            }
            break;
    }
    
    return false;
}

//This function is used for security purpose
bool adminAuth(){

    cout<<"Enter Admin ID : ";
    string s1;
    cin>>s1;
    cout<<"Enter Password: ";
    string s2;
    cin>>s2;
    ifstream adf("admin.txt");
    
    if (!adf) {
        cout << "Error opening the file." << endl;
        return false;
    }
    
    string first;
    string second;
    
    if (adf >> first >> second){
        
    if(s1==first && s2==second){
    sleep(3);
    system("cls");
    return true;
    }
    return false;

    } 

    else {
        cout<< "Error reading from file" << std::endl;
    }
    
    adf.close();
}

//using this function admin can access all information of bloodbank

void callAdminProcess(){

    while(1)
    {
        cout << "1. View donor list" << endl;
        cout << "2. View acceptor list" << endl;
        cout << "3. View blood bank list" << endl;
        cout<<"4. LogOut"<<endl;
        
        int choice;
        cin >> choice;

        if (choice == 1) {
            viewAllDonar();
            sleep(5);
            system("cls");
        }
        else if (choice == 2) {
            viewAllAcceptor();
            sleep(5);
            system("cls");
        }
        else if (choice == 3) {
            viewAllBank();
            sleep(5);
            system("cls");
        }
        else if (choice == 4){
            cout<<"Successfully logged out"<<endl;
            break;
        }
        else{
            cout<<"Invalid choise ..."<<endl;
        }
        
    }
}

int main(){

    // Donar is only KUETian But Acceptor can any person

    cout<<"==============================================================="<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|             Blood Bank Management System                     |"<<endl;
    cout<<"|                      KUET                                    |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"================================================================"<<endl;

    while (true) {
        cout<<"Enter choise:"<<endl;
        cout<<"press 1. Admin"<<endl;
        cout<<"press 2. User"<<endl;
       int x;
       cin>>x;
       
       if(x==1){
          
        bool checkAuth=adminAuth();

        if(checkAuth==true) callAdminProcess();
        else cout<<"Wrong password"<<endl;

       }

       else if (x==2){
            cout << "Enter your choice:" << endl;
            cout << "1. Donor" << endl;
            cout << "2. Acceptor" << endl;

            int choice;
            cin >> choice;

            if (choice == 1) {
                string name1,name2, dept, bg;
                int roll;
                cout << "Enter first name: ";
                cin>>name1;
                cout<<"Enter last name: ";
                cin>>name2;
                cout << "Enter donor roll: ";
                cin >> roll;
                cout << "Enter department: ";
                cin >> dept;
                cout << "Enter blood group: ";
                cin >> bg;
                //To check valid blood group
                if(!check(bg)){
                    cout<<"Sorry you can't donate blood..."<<endl;
                    sleep(3);
                    system("cls");
                    continue;
                }
                cout<<"Enter phone Number: ";
                string phn;
                cin>>phn;
                Donar d(name1,name2, roll, dept, bg,phn);
                d.Save();
                cout<<"Donar added on database"<<endl;
                sleep(3);
                system("cls");
            }
            else if (choice == 2) {
                string bloodGroup;
                cout << "Enter blood group: ";
                cin >> bloodGroup;
                bool found = searchBlood(bloodGroup);
                if (!found) {
                    cout << "Sorry! Required blood of this group is not found" << endl;
                }
                else{

                    cout<<"Successfully Blood Donated to Acceptor..."<<endl;
                }
                sleep(3);
                system("cls");
                
            }
            else{
                cout<<"Invalid choise ..."<<endl;
            }
       }

       else{
            cout<<"Invalid choise ..."<<endl;

        }
    }

    return 0;
}


