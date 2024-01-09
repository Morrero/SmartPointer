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
    Inform_sheet() {//конструктор по учолчанию
        bank_name = "N/A";
        BIC = 0;
        INN = 0;
        euro_rate = 0;
        dollar_rate = 0;
    }
    Inform_sheet(string bank_name, long int BIC, long int INN) {//конструктор с параметрпми
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
            cout << "Невозможно получить справку, так как курс валют не установлен!!!";
        }
        else {

            const time_t tm = time(nullptr);

            char buf[64];
            strftime(buf, size(buf), "%d.%m.%Y", localtime(&tm));
            cout << "Справка" << endl;
            cout << "Выдана для клиента " << full_name << " в отделении банка " << bank_name << "  для подтверждения наличия денежных средств" << endl;
            cout << "На счёте у клиента " << full_name << " находится: " << balance << " " << currency;
            cout << "\nЭквивалент в евро:" << roundf(balance / euro_rate * 100) / 100 << endl;
            cout << "Эквивалент в долларах:" << roundf(balance / dollar_rate * 100) / 100 << endl;
            cout << "\nPеквизиты банка:\n" << "BIC:" << BIC << "\nINN:" << INN << endl;
            cout << "\nДата выдачи:" << buf << endl;
            cout << "Справка действительна в течение 2-х недель с момента выдачи" << endl;

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
        this->middleName = "—";
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

    bool stringCheck(const string string) {//проверка на русский алфавит
        int i = 0;
        while (string[i] != '\0')
            if (!isalpha(string[i]) && !(string[i] >= 'А' && string[i] <= 'я') && !(string[i] == 'ё') && !(string[i] == 'Ё') && !(string[i] == '-'))return false;
            else i++;
        return true;
    }
    void InputFullName() {//ввод фаммилии
        setlocale(LC_ALL, "ru");
        while (1)
        {
            cout << "Введите Фамилию: " << endl;
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
            cout << "Введите Имя: " << endl;
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
            cout << "Введите Отчество('-' — если отчества нет): " << endl;
            cin >> middleName;
            if (!stringCheck(middleName)) {
                cout << "A variable cannot contain these characters" << endl;
                cin.clear();//сянтие флага ошибок
                cin.ignore(256, '\n');//очищение входонго потока
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
    string GetFullName() {//функция перевода денег
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
            cout << "На вашем счёте недостаточно средств" << endl;
            return 0;
        }
    }
    bool ConfirmDebiting(float debt_money) {
        int choice;
        float commission = roundf(0.05 * debt_money * 100) / 100;
        while (1) {
            cout << "Вы действительно хотите перевести " << debt_money << " с комиссией " << commission << "? (0 — нет, 1 — да)\nВаш выбор:";
            cin >> choice;
            if (cin.fail() || (choice != 1 && choice != 0)) {
                cout << "Выберите один из вариантов" << endl;
                cin.clear();
                cin.ignore(256, '\n');
            }
            else break;
        }
        return choice;
    }
    bool TakingLoan(float credit_money) {//взятие кредита
        Human guarantor;
        cout << "Введите данные поручителя" << endl;
        guarantor.InputFullName();
        if (rand() % 100 > 51) {
            cout << "Ваш кредит будедт одобрен банком" << endl;
            return 1;
        }
        else {
            cout << "Ваш кредит не может быть одобрен банком" << endl;
            return 0;
        }
    }
    bool ConfirmLoan(float credit_money) {//кредит одобрен
        float sum_percent = roundf((0.53260274 * credit_money) * 100) / 100;
        float sum_total = roundf((sum_percent + credit_money) * 100) / 100;
        float sum_per_month = roundf(sum_total / 36 * 100) / 100;
        cout << "Вы действительно хотите взять кредит на сумму " << credit_money << "?" << endl;
        cout << "\nВаш ежемесячный платёж составит:" << sum_per_month << endl;
        cout << "\nВаша сумма кредита по процентам:" << sum_percent << endl;
        cout << "\nВаша общая сумма долга составит:" << sum_total << endl;
        int choice;
        while (1) {
            cout << "Вы подтверждаете взятие кредита(0 — нет, 1 — да)\nВаш выбор : ";
            cin >> choice;
            if (cin.fail() || (choice != 1 && choice != 0)) {
                cout << "Выберите один из вариантов" << endl;
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
    T* currentState;//текущее значение объекта класса 
    T* prevState;//предыдущее состояние объекта
    vector<T*> transaction_list;
public:
    Transaction() /*:prevState(NULL), currentState(new T)*/ {
        transaction_list.push_back(NULL); transaction_list.push_back(new T);
    }//конструктор без параметров
    Transaction(const Transaction& obj) /*: currentState(new T(*(obj.currentState))), prevState(NULL)*/ {
        for (int a = 0; a < obj.transaction_list.size(); a++) {
            transaction_list.push_back(new T(*(obj.transaction_list)));
        }
    }// конструктор копирования
    ~Transaction() {
        //delete currentState; delete prevState;
        transaction_list.clear();
    }//деструктор 
    Transaction& operator=(const Transaction& obj);//перегрузка оператора присваивания
    void showState(State state);//отображение состояний (предыдущего и текущего) объекта
    int beginTransactions(float sum, int type_oper);//метод начала транзакции
    void commit();//метод подтверждения (коммита) транзакции 
    void deleteTransactions(); //метод отката транзакции 
    T* operator->();//перегрузка оператора доступа к содержимому объекта через указатель
};
template <class T>
Transaction<T>& Transaction<T>::operator=(const Transaction<T>& obj) {
    if (this != &obj) {//проверка на случай obj=obj
        delete currentState;//удаление текущего значения объекта 
        currentState = new T(*(obj.currentState));//создание и копирование объекта, используя присваеваемую транзакцию
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
void Transaction<T>::showState(State state) {//метод отображение состояния объекта
    //cout << "Состояние объекта ";
    //if (!state) cout << "до начала транзакции " << endl;
    //else cout << "после выполнения транзакции " << endl;
    //if (prevState) cout << "prevState = " << prevState->GetMoney() << endl;//предыдущее состояние
    //else cout << "prevState = NULL" << endl;
    //cout << "currentState = " << currentState->GetMoney() << endl;//текущее состояние

    for (int a = 0; a < transaction_list.size() - 1; a++) {
        if (transaction_list[a])cout << "prevState = " << transaction_list[a]->GetMoney() << endl;
        else cout << "prevState = NULL" << endl;
        cout << "currentState = " << transaction_list[a + 1]->GetMoney() << endl;
    }
}
template <class T>
int Transaction<T>::beginTransactions(float sum, int type_oper) {// метод начала транзакции
    //delete prevState;//удаление предыдущего значения 
    //prevState = currentState;//сохранение предыдущего состояния как текущего
    //currentState = new T(*prevState);//текущее состояние создается !!!!!!!!!!!!!!
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
    //if (!currentState) return 0;//ошибка (необходимо отменить транзакцию)
    //if (!(currentState->Debiting(debt))){
    //    return 0;
    //}//изменение состояния объекта
    //return 1;//успешное окончание транзакции 
}
template <class T>
void Transaction<T>::commit() {
    delete prevState;//удаление предыдущего значения 
    prevState = NULL;//предыдущего состояния нет 
}
template <class T>
void Transaction<T>::deleteTransactions() {
    //if (prevState != NULL) { 
    //    delete currentState;//удаление текущего значения  
    //    currentState = prevState;//предыдущее становится текущим  
    //    prevState = NULL;//предыдущего состояния нет  
    //} 
    int lastsecond = transaction_list.size() - 2;
    if (transaction_list[lastsecond] != NULL) {
        delete transaction_list[lastsecond + 1];
        transaction_list.erase(transaction_list.begin() + lastsecond + 1);
    }
}
template <class T>
struct Status {
    T* ptr;//указатель на объект
    int counter;//счетчик количества ссылок на объект 
};
//Класс умного указателя. Умный указатель должен вести подсчет количества созданный ссылок на объект
template <class T>
class SmartPointer {
    Status<T>* smartPtr;// указатель на объект
public:
    SmartPointer(T* ptr);//конструктор с одним параметром типа T
    SmartPointer(const SmartPointer& obj);//конструктор копирования
    ~SmartPointer();//деструктор
    SmartPointer& operator=(const SmartPointer& obj); //перегрузка оператора присваивания
    T* operator->() const;//оператор получения доступа к объекту через указатель
    void showCounter() {
        cout << "Значение счетчика для объекта " << smartPtr << " равно: " << smartPtr->counter << endl;
    }
};
template <class T>
SmartPointer<T>::SmartPointer(T* ptr) {
    if (!ptr)
        smartPtr = NULL;//указатель на объект пустой 
    else {
        smartPtr = new Status<T>();
        smartPtr->ptr = ptr;//инициализирует объект указателем 
        smartPtr->counter = 1;//счетчик «прикрепленных» объектов инициализируем единицей
    }
}
template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj) :smartPtr(obj.smartPtr) {
    if (smartPtr) smartPtr->counter++;//увеличение количества ссылок на объект
}
template <class T>
SmartPointer<T>::~SmartPointer() {
    if (smartPtr) {
        smartPtr->counter--;//уменьшение количества ссылок на объект
        if (smartPtr->counter == 0) {//если число ссылок на объект равно нулю, то должен уничтожится объект
            delete smartPtr->ptr;//освобождение памяти, выделенной для объекта
            delete smartPtr;//освобождение памяти, выделенной для указателя
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
        smartPtr->counter--;//уменьшаем счетчик «прикрепленных» объектов для текущего указателя
        if (smartPtr->counter == 0) {//если объектов больше нет, то необходимо освобождить выделенную память
            delete smartPtr->ptr;
            delete smartPtr;
        }
    }
    smartPtr = obj.smartPtr;//присваивание нового адреса указателю 
    if (smartPtr) smartPtr->counter++;//увеличить счетчик «прикрепленных» объектов
    return *this;
}

int menu() {
    system("cls");
    int choice;
    cout << "1. Показать баланс счёта\n"
        "2. Перевести деньги\n"
        "3. Выдать спраку\n"
        "4. Оформить кредит\n"
        "5. История операций\n"
        "0. Выход\n"
        "Ваш выбор: " << endl;
    rewind(stdin);
    cin >> choice;
    return choice;
}

float InputSum() {
    float sum;
    while (true) {
        cout << "\nТребуемая сумма:" << endl;
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
    Inform_sheet bank_sheet("ФИЛИАЛ №6 AlfaBank(ОАО), г.Минск", 420077380, 1710353606);
    while (1) {
        system("cls");
        switch (menu())
        {
        case 1:
            cout << "Баланс вашего счёта:" << firstAccount->GetMoney() << " " << firstAccount->GetCurrency() << endl;
            break;
        case 2:
        {//firstAccount.showState(State::begin);
            float debt = 0;
            cout << "Введите сумму, которую хотите перевести:";
            debt = InputSum();
            if (firstAccount.beginTransactions(debt, 1)) {//начало транзакции (изменение объекта)
                    //firstAccount.showState(State::middle);
                if (firstAccount->ConfirmDebiting(debt)) {
                    cout << "Перевод денег выполнен успешно" << endl;
                }
                else
                    firstAccount.deleteTransactions();//отмена транзакции при ошибке
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
            cout << "Введите сумму желаемого кредита:";
            credit = InputSum();
            if (firstAccount.beginTransactions(credit, 2)) {//начало транзакции (изменение объекта)
                    //firstAccount.showState(State::middle);
                if (firstAccount->ConfirmLoan(credit)) {
                    cout << "Кредит был выдан успешно" << endl;
                }
                else
                    firstAccount.deleteTransactions();//отмена транзакции при ошибке
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
