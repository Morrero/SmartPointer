#include<iostream> 
#include<string> 
#include <vector> 
#include <cmath> 
#include <fstream> 
#include <Windows.h> 
#include <iomanip> 
#include <ctype.h> 
#include <ctime>
#include <cstdlib>
#pragma warning(disable : 4996)
using namespace std;


class Inform_sheet {
protected:
    string bank_name;
    long int BIC;
    long int INN;
    float euro_rate;
    float dollar_rate;

public:
    Inform_sheet() {//����������� �� ���������
        bank_name = "N/A";
        BIC = 0;
        INN = 0;
        euro_rate = 0;
        dollar_rate = 0;
    }
    Inform_sheet(string bank_name, long int BIC, long int INN) {//����������� � �����������
        this->bank_name = bank_name;
        this->BIC = BIC;
        this->INN = INN;
        euro_rate = 0;
        dollar_rate = 0;
    }
    void SetBankName(string bank_name) {
        this->bank_name = bank_name;
    }
    string GetBankName() {
        return bank_name;
    }
    void SetBIC(long int BIC) {
        this->BIC = BIC;
    }
    long int GetBIC() {
        return BIC;
    }
    void SetINN(long int INN) {
        this->INN = INN;
    }
    long int GetINN() {
        return INN;
    }
    void SetEuroRate(float euro_rate) {
        this->euro_rate = euro_rate;
    }
    float GetEuroRate() {
        return euro_rate;
    }
    void SetDollarRate(float dollar_rate) {
        this->dollar_rate = dollar_rate;
    }
    float GetDollarRate() {
        return dollar_rate;
    }
    void SetRate(float dollar_rate, float euro_rate) {
        this->dollar_rate = dollar_rate;
        this->euro_rate = euro_rate;
    }
    void IssueCertificate(string full_name, float balance, string currency) {
        if (dollar_rate == 0 || euro_rate == 0) {
            cout << "���������� �������� �������, ��� ��� ���� ����� �� ����������!!!";
        }
        else {

            const time_t tm = time(nullptr);

            char buf[64];
            strftime(buf, size(buf), "%d.%m.%Y", localtime(&tm));
            cout << "�������" << endl;
            cout << "������ ��� ������� " << full_name << " � ��������� ����� " << bank_name << "  ��� ������������� ������� �������� �������" << endl;
            cout << "�� ����� � ������� " << full_name << " ���������: " << balance << " " << currency;
            cout << "\n���������� � ����:" << roundf(balance / euro_rate * 100) / 100 << endl;
            cout << "���������� � ��������:" << roundf(balance / dollar_rate * 100) / 100 << endl;
            cout << "\nP�������� �����:\n" << "BIC:" << BIC << "\nINN:" << INN << endl;
            cout << "\n���� ������:" << buf << endl;
            cout << "������� ������������� � ������� 2-� ������ � ������� ������" << endl;

        }
    }
};
class Human {
protected:
    string surname;
    string name;
    string middleName;
public:
    Human() {
        surname = "N/A";
        name = "N/A";
        middleName = "N/A";
    }
    Human(string surname, string name, string middleName) {
        this->surname = surname;
        this->name = name;
        this->middleName = middleName;
    }
    Human(string surname, string name) {
        this->surname = surname;
        this->name = name;
        this->middleName = "�";
    }
    void SetSurname(string surname) {
        this->surname = surname;
    }
    void SetName(string name) {
        this->name = name;
    }
    void SetMiddleName(string middleName) {
        this->middleName = middleName;
    }
    string GetSurname() {
        return surname;
    }
    string GetName() {
        return name;
    }
    string GetMiddleName() {
        return middleName;
    }
    string GetFullName() {
        if (middleName != "-")
            return surname + ' ' + name + ' ' + middleName;
        else
            return surname + ' ' + name;
    }

    bool stringCheck(const string string) {//�������� �� ������� �������
        int i = 0;
        while (string[i] != '\0')
            if (!isalpha(string[i]) && !(string[i] >= '�' && string[i] <= '�') && !(string[i] == '�') && !(string[i] == '�') && !(string[i] == '-'))return false;
            else i++;
        return true;
    }
    void InputFullName() {//���� ��������
        setlocale(LC_ALL, "ru");
        while (1)
        {
            cout << "������� �������: " << endl;
            cin >> surname;
            if (!stringCheck(surname)) {
                cout << "A variable cannot contain these characters" << endl;
                cin.clear();
                cin.ignore(256, '\n');
            }
            else break;
        }
        surname[0] = toupper(surname[0]);
        while (1)
        {
            cout << "������� ���: " << endl;
            cin >> name;
            if (!stringCheck(name)) {
                cout << "A variable cannot contain these characters" << endl;
                cin.clear();
                cin.ignore(256, '\n');
            }
            else break;
        }
        name[0] = toupper(name[0]);
        while (1)
        {
            cout << "������� ��������('-' � ���� �������� ���): " << endl;
            cin >> middleName;
            if (!stringCheck(middleName)) {
                cout << "A variable cannot contain these characters" << endl;
                cin.clear();//������ ����� ������
                cin.ignore(256, '\n');//�������� �������� ������
            }
            else break;
        }
        middleName[0] = toupper(middleName[0]);
    }
};

class Account {
protected:
    float money;
    string currency;
    Human full_name;
public:
    Account() {
        money = 10000;
        full_name.InputFullName();
        currency = "BYN";
    }
    Account(float money, string currency) {
        this->money = money;
        full_name.InputFullName();
        this->currency = currency;
    }
    void SetMoney(float money) {
        this->money = money;
    }
    float GetMoney() {
        return money;
    }
    void SetCurrency(string currency) {
        this->currency = currency;
    }
    string GetCurrency() {
        return currency;
    }
    string GetFullName() {//������� �������� �����
        return full_name.GetFullName();
    }
    float Debiting(float debt_money) {
        float commission = roundf(0.05 * debt_money * 100) / 100;
        if (debt_money + commission < money) {
            money = money - (debt_money + commission);
            if (money == 0.00)
                return 1;
            return money;
        }
        else {
            cout << "�� ����� ����� ������������ �������" << endl;
            return 0;
        }
    }
    bool ConfirmDebiting(float debt_money) {
        int choice;
        float commission = roundf(0.05 * debt_money * 100) / 100;
        while (1) {
            cout << "�� ������������� ������ ��������� " << debt_money << " � ��������� " << commission << "? (0 � ���, 1 � ��)\n��� �����:";
            cin >> choice;
            if (cin.fail() || (choice != 1 && choice != 0)) {
                cout << "�������� ���� �� ���������" << endl;
                cin.clear();
                cin.ignore(256, '\n');
            }
            else break;
        }
        return choice;
    }
    bool TakingLoan(float credit_money) {//������ �������
        Human guarantor;
        cout << "������� ������ ����������" << endl;
        guarantor.InputFullName();
        if (rand() % 100 > 51) {
            cout << "��� ������ ������ ������� ������" << endl;
            return 1;
        }
        else {
            cout << "��� ������ �� ����� ���� ������� ������" << endl;
            return 0;
        }
    }
    bool ConfirmLoan(float credit_money) {//������ �������
        float sum_percent = roundf((0.53260274 * credit_money) * 100) / 100;
        float sum_total = roundf((sum_percent + credit_money) * 100) / 100;
        float sum_per_month = roundf(sum_total / 36 * 100) / 100;
        cout << "�� ������������� ������ ����� ������ �� ����� " << credit_money << "?" << endl;
        cout << "\n��� ����������� ����� ��������:" << sum_per_month << endl;
        cout << "\n���� ����� ������� �� ���������:" << sum_percent << endl;
        cout << "\n���� ����� ����� ����� ��������:" << sum_total << endl;
        int choice;
        while (1) {
            cout << "�� ������������� ������ �������(0 � ���, 1 � ��)\n��� ����� : ";
            cin >> choice;
            if (cin.fail() || (choice != 1 && choice != 0)) {
                cout << "�������� ���� �� ���������" << endl;
                cin.clear();
                cin.ignore(256, '\n');
            }
            else break;
        }
        if (choice) {
            money += credit_money;
        }
        return choice;
    }
};

enum State { begin, middle };


template <class T>
class Transaction {
    T* currentState;//������� �������� ������� ������ 
    T* prevState;//���������� ��������� �������
    vector<T*> transaction_list;
public:
    Transaction() /*:prevState(NULL), currentState(new T)*/ {
        transaction_list.push_back(NULL); transaction_list.push_back(new T);
    }//����������� ��� ����������
    Transaction(const Transaction& obj) /*: currentState(new T(*(obj.currentState))), prevState(NULL)*/ {
        for (int a = 0; a < obj.transaction_list.size(); a++) {
            transaction_list.push_back(new T(*(obj.transaction_list)));
        }
    }// ����������� �����������
    ~Transaction() {
        //delete currentState; delete prevState;
        transaction_list.clear();
    }//���������� 
    Transaction& operator=(const Transaction& obj);//���������� ��������� ������������
    void showState(State state);//����������� ��������� (����������� � ��������) �������
    int beginTransactions(float sum, int type_oper);//����� ������ ����������
    void commit();//����� ������������� (�������) ���������� 
    void deleteTransactions(); //����� ������ ���������� 
    T* operator->();//���������� ��������� ������� � ����������� ������� ����� ���������
};
template <class T>
Transaction<T>& Transaction<T>::operator=(const Transaction<T>& obj) {
    if (this != &obj) {//�������� �� ������ obj=obj
        delete currentState;//�������� �������� �������� ������� 
        currentState = new T(*(obj.currentState));//�������� � ����������� �������, ��������� ������������� ����������
        //for (int a = 0; a < transaction_list.size(); a++)
    }
    return *this;
}
template <class T>
T* Transaction<T>::operator->() {
    //return currentState;
    return transaction_list.back();
}
template <class T>
void Transaction<T>::showState(State state) {//����� ����������� ��������� �������
    //cout << "��������� ������� ";
    //if (!state) cout << "�� ������ ���������� " << endl;
    //else cout << "����� ���������� ���������� " << endl;
    //if (prevState) cout << "prevState = " << prevState->GetMoney() << endl;//���������� ���������
    //else cout << "prevState = NULL" << endl;
    //cout << "currentState = " << currentState->GetMoney() << endl;//������� ���������

    for (int a = 0; a < transaction_list.size() - 1; a++) {
        if (transaction_list[a])cout << "prevState = " << transaction_list[a]->GetMoney() << endl;
        else cout << "prevState = NULL" << endl;
        cout << "currentState = " << transaction_list[a + 1]->GetMoney() << endl;
    }
}
template <class T>
int Transaction<T>::beginTransactions(float sum, int type_oper) {// ����� ������ ����������
    //delete prevState;//�������� ����������� �������� 
    //prevState = currentState;//���������� ����������� ��������� ��� ��������
    //currentState = new T(*prevState);//������� ��������� ��������� !!!!!!!!!!!!!!
    transaction_list.push_back(new T(*transaction_list[transaction_list.size() - 1]));
    if (!transaction_list.back()) return 0;

    switch (type_oper) {
    case 1:
    {
        if (!(transaction_list.back()->Debiting(sum)))return 0;
    }break;
    case 2:
    {
        if (!(transaction_list.back()->TakingLoan(sum)))return 0;
    }
    }
    return 1;
    //if (!currentState) return 0;//������ (���������� �������� ����������)
    //if (!(currentState->Debiting(debt))){
    //    return 0;
    //}//��������� ��������� �������
    //return 1;//�������� ��������� ���������� 
}
template <class T>
void Transaction<T>::commit() {
    delete prevState;//�������� ����������� �������� 
    prevState = NULL;//����������� ��������� ��� 
}
template <class T>
void Transaction<T>::deleteTransactions() {
    //if (prevState != NULL) { 
    //    delete currentState;//�������� �������� ��������  
    //    currentState = prevState;//���������� ���������� �������  
    //    prevState = NULL;//����������� ��������� ���  
    //} 
    int lastsecond = transaction_list.size() - 2;
    if (transaction_list[lastsecond] != NULL) {
        delete transaction_list[lastsecond + 1];
        transaction_list.erase(transaction_list.begin() + lastsecond + 1);
    }
}
template <class T>
struct Status {
    T* ptr;//��������� �� ������
    int counter;//������� ���������� ������ �� ������ 
};
//����� ������ ���������. ����� ��������� ������ ����� ������� ���������� ��������� ������ �� ������
template <class T>
class SmartPointer {
    Status<T>* smartPtr;// ��������� �� ������
public:
    SmartPointer(T* ptr);//����������� � ����� ���������� ���� T
    SmartPointer(const SmartPointer& obj);//����������� �����������
    ~SmartPointer();//����������
    SmartPointer& operator=(const SmartPointer& obj); //���������� ��������� ������������
    T* operator->() const;//�������� ��������� ������� � ������� ����� ���������
    void showCounter() {
        cout << "�������� �������� ��� ������� " << smartPtr << " �����: " << smartPtr->counter << endl;
    }
};
template <class T>
SmartPointer<T>::SmartPointer(T* ptr) {
    if (!ptr)
        smartPtr = NULL;//��������� �� ������ ������ 
    else {
        smartPtr = new Status<T>();
        smartPtr->ptr = ptr;//�������������� ������ ���������� 
        smartPtr->counter = 1;//������� ��������������� �������� �������������� ��������
    }
}
template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj) :smartPtr(obj.smartPtr) {
    if (smartPtr) smartPtr->counter++;//���������� ���������� ������ �� ������
}
template <class T>
SmartPointer<T>::~SmartPointer() {
    if (smartPtr) {
        smartPtr->counter--;//���������� ���������� ������ �� ������
        if (smartPtr->counter == 0) {//���� ����� ������ �� ������ ����� ����, �� ������ ����������� ������
            delete smartPtr->ptr;//������������ ������, ���������� ��� �������
            delete smartPtr;//������������ ������, ���������� ��� ���������
        }
    }
}
template <class T>
T* SmartPointer<T>::operator->() const {
    if (smartPtr) return smartPtr->ptr;
    else return NULL;
}
template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& obj) {
    if (smartPtr) {
        smartPtr->counter--;//��������� ������� ��������������� �������� ��� �������� ���������
        if (smartPtr->counter == 0) {//���� �������� ������ ���, �� ���������� ����������� ���������� ������
            delete smartPtr->ptr;
            delete smartPtr;
        }
    }
    smartPtr = obj.smartPtr;//������������ ������ ������ ��������� 
    if (smartPtr) smartPtr->counter++;//��������� ������� ��������������� ��������
    return *this;
}

int menu() {
    system("cls");
    int choice;
    cout << "1. �������� ������ �����\n"
        "2. ��������� ������\n"
        "3. ������ ������\n"
        "4. �������� ������\n"
        "5. ������� ��������\n"
        "0. �����\n"
        "��� �����: " << endl;
    rewind(stdin);
    cin >> choice;
    return choice;
}

float InputSum() {
    float sum;
    while (true) {
        cout << "\n��������� �����:" << endl;
        cin >> sum;
        if (cin.fail() || sum < 0) {
            cout << "A variable cannot contain these characters" << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else return sum;
    };
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Transaction<Account> firstAccount;
    Inform_sheet bank_sheet("������ �6 AlfaBank(���), �.�����", 420077380, 1710353606);
    while (1) {
        system("cls");
        switch (menu())
        {
        case 1:
            cout << "������ ������ �����:" << firstAccount->GetMoney() << " " << firstAccount->GetCurrency() << endl;
            break;
        case 2:
        {//firstAccount.showState(State::begin);
            float debt = 0;
            cout << "������� �����, ������� ������ ���������:";
            debt = InputSum();
            if (firstAccount.beginTransactions(debt, 1)) {//������ ���������� (��������� �������)
                    //firstAccount.showState(State::middle);
                if (firstAccount->ConfirmDebiting(debt)) {
                    cout << "������� ����� �������� �������" << endl;
                }
                else
                    firstAccount.deleteTransactions();//������ ���������� ��� ������
            }
            //firstAccount.showState(State::middle);
        }break;
        case 3:
        {
            bank_sheet.SetRate(2.51, 2.45);
            bank_sheet.IssueCertificate(firstAccount->GetFullName(), firstAccount->GetMoney(), firstAccount->GetCurrency());
        }
        break;
        case 4:
        {//firstAccount.showState(State::begin);
            float credit = 0;
            cout << "������� ����� ��������� �������:";
            credit = InputSum();
            if (firstAccount.beginTransactions(credit, 2)) {//������ ���������� (��������� �������)
                    //firstAccount.showState(State::middle);
                if (firstAccount->ConfirmLoan(credit)) {
                    cout << "������ ��� ����� �������" << endl;
                }
                else
                    firstAccount.deleteTransactions();//������ ���������� ��� ������
            }
            //firstAccount.showState(State::middle);
        }break;
        case 5:
            firstAccount.showState(State::middle);
            break;
        case 0:
            return 0;
        default:
            cout << "Wrong value! Try again..." << endl;  break;
        }
        system("pause");
    }
}
