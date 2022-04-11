#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
int bill_count = 0; //keep total count of prize
int reward = 0;     //keep count of reward point
int co = 0;         //remember slot no for add seat at time of cancelation
struct flight       //contains data of flight
{
    // string name;
    int time[3];
    int av_seats[3];
    char destination[20];
    int prize;
    int duration;
    struct flight *next;
};
struct airport //contains data of airport with flight node
{
    char Name[20];
    struct flight *Head = NULL;
    struct flight *Tail = NULL;
    struct airport *Next;
};
class mangment
{
private:
    struct airport *head;   //head of airport linked list
    struct airport *tail;   // tail of airport linked list
    struct flight *Stack_h; //head of stack using linked list
    struct flight *Stack_t; // tail of stack using linked list
public:
    mangment();                               //constructor
    void add_flight();                        //add flight in airport
    void add_airport();                       //add airport in linked list
    void bill();                              //generate bill
    void show();                              //print data of airport and their flights
    bool check_for_flight(char *x, char *y);  //check for flight
    void check_for_flight2(char *z, char *w); //check for flight in other airport if not get book by check_for_flight
    void cancel();                            //cancel last booked flight
    void push(struct flight *);               //add booked flight pointer in stack
    char *pop();                              //remove flight pointer from stack
    void top();                               //print last booked flight data
};
mangment::mangment()
{
    head = NULL;    //head pointer of airpot linkedlist
    tail = NULL;    //tail pointer of airport linked list
    Stack_h = NULL; //head pointer of stack
    Stack_t = NULL; //tail pointer of stack
}
void mangment::add_airport()
{
    struct airport *tmp = (struct airport *)malloc(sizeof(struct airport));
    cout << "\tName of Airport" << endl;
    cin >> tmp->Name;
    tmp->Next = NULL;
    tmp->Head = NULL;
    tmp->Tail = NULL;
    if (head == NULL)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->Next = tmp;
        tail = tmp;
    }
}
void mangment::add_flight()
{
    int flag = 0;
    string x;
    cout << "\tENTER THE NAME OF AIRPORT TO ADD FLIGHT " << endl;
    cin >> x;
    struct airport *n = head;
    while (n != NULL)
    {
        if (x == n->Name)
        {
            flag = 1;
            goto add;
        }
        n = n->Next;
    }
add:
    if (flag == 1)
    {
        struct flight *tmp = (struct flight *)malloc(sizeof(struct flight));
        tmp->next = NULL;
        cout << "DESTINATION OF FLIGHT" << endl;
        cin >> tmp->destination;
        cout << "DURATION OF FLIGHT" << endl;
        cin >> tmp->duration;
        cout << "COST OF FLIGHT" << endl;
        cin >> tmp->prize;
        for (int i = 0; i < 3; i++)
        {
            cout << "TIME OF SLTOT-" << i + 1 << endl;
            cin >> tmp->time[i];
            cout << "AVAILABLE SEATS IN SLOT-" << i + 1 << endl;
            cin >> tmp->av_seats[i];
        }
        if (n->Head == NULL)
        {

            n->Head = tmp;
            n->Tail = tmp;
        }
        else
        {
            n->Tail->next = tmp;
            n->Tail = tmp;
        }
    }
    else
    {
        cout << "NO AIRPORT WITH THAT NAME IN OUR SYSTEM!!! " << endl;
    }
}

bool mangment::check_for_flight(char *x, char *y)
{
    int flag = 0;
    char *z, *w;
    z = new char[20];
    w = new char[20];

    int h;
    struct airport *tmp = head;
    while (tmp != NULL)
    {
        w = tmp->Name;
        if (!(strcmp(y, w)))
        {

            flag = 1;
            goto check;
        }
        tmp = tmp->Next;
    }
check:
    if (flag == 1)
    {
        struct flight *n = tmp->Head;
        while (n != NULL)
        {
            z = n->destination;

            if (!(strcmp(x, z)))
            {
                cout << "SLOTS AND AVAILABLE SEATS FOR" << endl
                     << w << " To " << z << endl;
                for (int i = 0; i < 3; i++)
                {
                    cout << "SLOT- " << i + 1 << " OF TIME " << n->time[i] << " AVAILABLE SEATS " << n->av_seats[i] << endl;
                }
                cout << "ENTER NO. TIME SLOT YOU PREFER" << endl;
                cin >> h;
                if (n->av_seats[h - 1] > 0)
                {
                    cout << "YOUR FLIGHT IS BOOKED SUCCESSFULLY!!!" << endl;
                    cout << "IN SLOT " << h << " IN TIME " << n->time[h - 1] << endl;
                    cout << "DURATION OF FLIGHT " << n->duration << endl;
                    n->av_seats[h - 1] -= 1;
                    co = h - 1;
                    bill_count += n->prize;
                    push(n);
                    reward += (n->prize * 0.1);
                    return true;
                }
                else
                {
                    cout << "SORRY NO SEATS AVAILABLE IN THIS SLOT" << endl;
                    return false;
                }
            }
            n = n->next;
        }
        return false;
    }
    else
    {
        cout << "NO AIRPORT IS IN OUR SYSTEM" << endl;
        return false;
    }
}
void mangment::check_for_flight2(char *z, char *w)
{
    struct airport *n = head;
    struct airport *l = head;
    struct flight *tmp = n->Head;
    struct flight *x = n->Head;
    while (n != NULL)
    {
        if (!(strcmp(z, n->Name)))
        {
            x = n->Head;
            while (x != NULL)
            {

                while (l != NULL)
                {
                    if (!(strcmp(x->destination, l->Name)))
                    {

                        if (check_for_flight(l->Name, z))
                        {
                            if (check_for_flight(w, l->Name));
                        }
                    }

                    l = l->Next;
                }
                x = x->next;
            }
        }

        n = n->Next;
    }
}
void mangment::bill()
{
    cout << "YOUR BILL AMOUNT IS " << bill_count - reward << endl;
}
void mangment::show()
{
    struct airport *tmp = head;
    struct flight *n = NULL;
    while (tmp != NULL)
    {

        n = tmp->Head;
        if (n == NULL)
        {
            cout << tmp->Name << "-NO FLIGHT IS ADDED TO THIS AIRPORT" << endl;
        }
        else
        {
            cout << "AIRPORT-" << tmp->Name << endl
                 << "FLIGHTS-" << endl;
            while (n != NULL)
            {
                cout << "\t" << tmp->Name << " TO " << n->destination << endl;
                n = n->next;
            }
        }
        cout << endl;
        tmp = tmp->Next;
    }
}
void mangment::push(struct flight *tmp)
{
    if (Stack_h == NULL)
    {

        Stack_h = tmp;
        Stack_t = tmp;
    }
    else
    {
        Stack_t->next = tmp;
        Stack_t = tmp;
    }
}
void mangment::top()
{
    if (Stack_h == NULL)
    {
        cout << "NO FLIGHT WAS BOOKED!!" << endl;
    }
    else
    {
        cout << "YOU HAVE BOOKED FLIGHT TO GO " << Stack_t->destination << endl;
    }
}
char *mangment::pop()
{
    if (Stack_h == NULL)
    {
        cout << "NO FLIGHT WAS BOOKED" << endl;
        return NULL;
    }
    else if (Stack_h == Stack_t)
    {
        char *h = Stack_h->destination;
        bill_count -= Stack_t->prize;
        reward -= (Stack_t->prize * 0.1);
        for (int i = 0; i < 3; i++)
        {
            if (co == i)
            {
                Stack_t->av_seats[i] += 1;
            }
        }
        Stack_h = NULL;
        Stack_t = NULL;
        return h;
    }
    else
    {
        struct flight *x = Stack_t;
        struct flight *n = Stack_h;
        struct flight *tmp = Stack_h;
        while (n != NULL)
        {
            tmp = tmp->next;
            if (tmp == Stack_t)
            {
                char *l = Stack_t->destination;
                bill_count -= Stack_t->prize;
                reward = reward - (Stack_t->prize * 0.1);
                for (int i = 0; i < 3; i++)
                {
                    if (co == i)
                    {
                        Stack_t->av_seats[i] += 1;
                    }
                }
                n->next = NULL;
                Stack_t = n;
                return l;
            }
            n = n->next;
        }
    }
}
void mangment::cancel()
{
    char *y = NULL;
    y = new char[20];
    y = pop();
    if (y == NULL)
    {
        cout << "NO FLIGHT IS BOOKED" << endl;
    }
    else
    {

        cout << "YOUR FLIGHT FOR DESTINATION-" << y << " IS SUCCESFULLY CANCELED" << endl;
    }
}
string USER, PASS; //to update reward
//login-and-register system for passanger
bool p_login()
{
    int count = 0, re;
    string user, pass, u, p;
    system("cls");
menu:
    cout << "please enter the following details" << endl;
    cout << "USERNAME :";
    cin >> user;
    cout << "PASSWORD :";
    cin >> pass;
    ifstream input("p.txt");
    while (input >> u >> p >> re)
    {
        if (u == user && p == pass)

        {
            USER = user;
            PASS = pass;
            count = 1;
            reward = re;
            //reward = re;
            input.close();

            break;
        }
    }
    if (count == 1)
    {
        cout << "You are Successfully Logged-in" << endl;
        return true;
    }
    else
    {
        char c;
        cout << "Invalid user-id or password" << endl;
        cout << "Do you want ot countinue?(y/n)" << endl;
        cin >> c;
        if (c == 'y')
        {
            goto menu;
        }
        else
            return false;
    }
    input.close();
    return false;
}

void p_registr()
{

    string reguser, regpass, ru, rp;
    system("cls");
    cout << "Enter the username :";
    cin >> reguser;
    cout << "\nEnter the password :";
    cin >> regpass;
    USER = reguser;
    PASS = regpass;
    ofstream reg("p.txt", ios::app);
    reg << reguser << ' ' << regpass << ' ' << '0' << endl;
    system("cls");
    cout << "\nRegistration Sucessful\n";
    reward = 0;
}
void a_registr()
{

    string reguser, regpass, ru, rp;
    system("cls");
    cout << "Enter the username :";
    cin >> reguser;
    cout << "\nEnter the password :";
    cin >> regpass;

    ofstream reg("a.txt", ios::app);
    reg << reguser << ' ' << regpass << endl;
    system("cls");
    cout << "\nRegistration Sucessful\n";
}
bool a_login()
{
    int count = 0;
menu:
    string user, pass, u, p;
    system("cls");
    cout << "please enter the following details" << endl;
    cout << "USERNAME :";
    cin >> user;
    cout << "PASSWORD :";
    cin >> pass;
    int h, i;
    ifstream input("a.txt");
    while (input >> u >> p)
    {
        if (u == user && p == pass)

        {
            count = 1;
            input.close();
            goto lable;
        }
    }
lable:
    if (count == 1)

    {
        cout << "You are successfully Logged-In" << endl;
        return true;
    }

    else
    {
        char c;
        cout << "Invalid user-id or password" << endl;
        cout << "Do you want ot countinue?(y/n)" << endl;
        cin >> c;
        if (c == 'y')
        {
            goto menu;
        }
        else
            return false;
    }
    input.close();
    return false;
}
void add()
{
    int count;
    string user, pass, u, p;
    system("cls");
    user = USER;
    pass = PASS;

    int re;
    int c = 0;
    ifstream input("p.txt");
    ofstream take("tmp.txt");
    while (input >> u >> p >> re)
    {
        c++;
        if (user == u && pass == p)

        {
            count = 1;
            take << u << ' ' << p << ' ' << reward << endl;
            system("cls");
        }
        else
            take << u << ' ' << p << ' ' << re << endl;
    }
    input.close();
    take.close();
    remove("p.txt");
    ofstream input1("p.txt");
    ifstream take1("tmp.txt");
    while (take1 >> u >> p >> re)
    {

        input1 << u << ' ' << p << ' ' << re << endl;
    }
    input1.close();
    take1.close();
    remove("tmp.txt");
}
int main()
{

    mangment m;
    int j;
    cout << "\t\t========================================" << endl;
    cout << "\t\t\tAIRPORT MANGMENT SYSTEM" << endl;
    cout << "\t\t========================================" << endl;

    do
    {
        cout << "\tPress 1 To Enter as Authority" << endl
             << "\tPress 2 To Enter as Passanger" << endl
             << "\tPress 0 To Exit" << endl;
        cin >> j;
        switch (j)
        {

        case 1:
            int a;
            do
            {
                cout << "\tPress 1 To login" << endl
                     << "\tPress 2 To register" << endl
                     << "\tPress 0 To return main menu" << endl;
                cin >> a;
                switch (a)
                {
                case 1:

                    int b;

                    if (a_login())
                    {
                        do
                        {
                        lable1:
                            cout << "\tPress 1 To new Airport" << endl
                                 << "\tPress 2 To add flights" << endl
                                 << "\tPress 3 To manegment system" << endl
                                 << "\tPress 0 To log out" << endl;
                            cin >> b;
                            switch (b)
                            {
                            case 1:
                                m.add_airport();
                                break;
                            case 2:
                                m.add_flight();
                                break;
                            case 0:
                                cout << "Successfully log-out" << endl;

                                b = 0;
                                break;
                            case 3:
                                m.show();
                                break;
                            default:
                                cout << "Enter a valid choice!!!" << endl;
                                break;
                            }
                        } while (b != 0);
                    }
                    break;
                case 2:
                    a_registr();
                    goto lable1;
                    break;
                case 0:
                    cout << "Thank You for visiting us" << endl;
                    break;
                default:
                    cout << "Enter a valid choice!!" << endl;
                    break;
                }
            } while (a != 0);

            break;
        case 2:
            int k;
            do
            {
                cout << "\tPress 1 For login" << endl
                     << "\tPress 2 For register" << endl
                     << "\tPress 0 For Main Menu" << endl;
                cin >> k;
                switch (k)
                {
                case 1:
                    int l;
                    if (p_login())
                    {
                    menu:
                        do
                        {
                            cout << "\tPress 1 To book flight" << endl
                                 << "\tPres 2 To view Your reward points" << endl
                                 << "\tPress 3 For generate bill" << endl
                                 << "\tPress 4 For view last booking" << endl
                                 << "\tPress 5 For cancel last booking" << endl
                                 << "\tPress 0 To Log-out" << endl;
                            cin >> l;
                            switch (l)
                            {
                            case 1:

                                char x[20], y[20];
                                cout << "Enter the airport name from you want to start" << endl;
                                cin >> y;
                                cout << "Enter the destination you want to go" << endl;
                                cin >> x;
                                if (m.check_for_flight(x, y))
                                    ;

                                else
                                {
                                    m.check_for_flight2(y, x);
                                }
                                add();
                                break;
                            case 2:
                                cout << "You have " << reward << " points" << endl;
                                break;
                            case 3:
                                m.bill();
                                break;
                            case 4:
                                m.top();
                                break;
                            case 5:
                                m.cancel();
                                break;
                            case 0:
                                cout << "Successfully log out" << endl;
                                add();
                                l = 0;
                                break;
                            default:
                                cout << "Enter a valid choice" << endl;
                                break;
                            }
                        } while (l != 0);
                    }

                    break;
                case 2:
                    p_registr();
                    goto menu;
                    break;
                case 0:
                    k = 0;
                    cout << "Thank You For Visiting Us" << endl;
                    break;
                default:
                    cout << "Enter a valid choice" << endl;
                    break;
                }
            } while (k != 0);
            break;
        case 0:
            break;
        default:
            cout << "Enter a valid Choice" << endl;
            break;
        }

    } while (j != 0);
    return 0;
}