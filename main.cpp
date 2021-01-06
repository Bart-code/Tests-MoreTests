#include <iostream>
#include <string>
#include <sstream>
#include "Markup.h"
#include <stdio.h>
#include <time.h>

using namespace std;

struct Date
{
    int years, months, days;
};

CMarkup initFile( string );
void addIvent( CMarkup* );
string konwersjaIntNaString( int );
int konwersjaStringNaInt( string );
void showAllIvents( CMarkup* );
Date getDateFromString( string );
void compareDates( CMarkup* );
Date getDateFromFile( string , CMarkup* );
void compareAmounts( CMarkup* );
int getAmountFromFile( string , CMarkup* );
string getCurrentDateTime( void );
int getDaysCountSelectedMonth( string );


int main()
{
    CMarkup plikXml=initFile("PlikZDatami");
    int menuPosition=0;
    string date="";

    while(1)
    {
    system("cls");
    cout<<"Chose operation"<<endl<<"------------------"<<endl<<endl;
    cout<<"1. Add new ivent"<<endl<<"2. Show all ivents"<<endl<<"3. Compare two ivents by date"<<endl;
    cout<<"4. Compare two ivents by amount"<<endl<<"5. Get current date"<<endl<<"6. Check days count selected month"<<endl<<"9. End"<<endl;
    cin>>menuPosition;
    switch (menuPosition)
    {
        case 1:
        {
            addIvent(&plikXml);
            break;
        }

         case 2:
        {
            showAllIvents(&plikXml);
            break;
        }
        case 3:
        {
            compareDates(&plikXml);
            break;
        }

        case 4:
        {
            compareAmounts(&plikXml);
            break;
        }

        case 5:
        {
            cout<<"Today is: "<<getCurrentDateTime()<<endl;
            break;
        }

        case 6:
        {

            cout<<"Enter date in mm-yyyy format: ";
            cin>>date;
            cout<<"Selected month has " << getDaysCountSelectedMonth(date) << " days"<<endl;
            break;
        }

        case 9:
        {
            return 0;
        }
    }
    system("pause");
    }
    return 0;
}

CMarkup initFile(string fileName)
{
    CMarkup plikXml;

    bool fileExists = plikXml.Load( fileName+".xml" );

    if (!fileExists)
    {
        plikXml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        plikXml.AddElem("Root");
    }

    plikXml.Save(fileName+".xml");
    return plikXml;
}

void addIvent(CMarkup * plikXml )
{

    string date, item, amount;

    cout<<"Set date of ivent (in format rrrr-mm-dd): ";
    cin>>date;
    cout<<"Set name of ivent: "<<endl;
    cin.ignore();
    getline(cin,item);
    cout<<"Set amount: "<<endl;
    cin>>amount;
    plikXml->ResetPos();
    plikXml->FindElem();
    plikXml->IntoElem();
    plikXml->AddElem( "Ivent" );
    plikXml->FindElem();
    plikXml->IntoElem();
    plikXml->AddElem( "Name" , item );
    plikXml->AddElem( "Date" , date );
    plikXml->AddElem( "Amount" , amount );
    plikXml->Save( "PlikZDatami.xml" );
}

string konwersjaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();
    return str;
}

int konwersjaStringNaInt(string liczba)
{
    int liczbaInt;
    istringstream iss(liczba);
    iss >> liczbaInt;

    return liczbaInt;
}


void showAllIvents( CMarkup* plikXml)
{
   plikXml->ResetPos();
   plikXml->FindElem();
   plikXml->IntoElem();
    while(plikXml->FindElem("Ivent"))
    {
        plikXml->IntoElem();
        plikXml->FindElem("Name");
        cout<<endl<<plikXml->GetData()<<endl;
        plikXml->FindElem("Date");
        cout<<plikXml->GetData()<<endl;
        plikXml->FindElem("Amount");
        cout<<plikXml->GetData()<<endl;
        plikXml->OutOfElem();

    }
}

Date getDateFromString(string dateInString)
{
    Date newDate;
    string someString=dateInString.substr(0,4);
    newDate.years=konwersjaStringNaInt(someString);
    someString=dateInString.substr(5,2);
    newDate.months=konwersjaStringNaInt(someString);
    someString=dateInString.substr(8,2);
    newDate.days=konwersjaStringNaInt(someString);
    return newDate;
}

void compareDates(CMarkup* plikXml)
{
    Date ivent1Date, ivent2Date;
    string ivent1Name, ivent2Name;
    cout<<"Enter name of first ivent: ";
    cin>>ivent1Name;
    cout<<"Enter name of second ivent: ";
    cin>>ivent2Name;

    ivent1Date=getDateFromFile( ivent1Name, plikXml);
    ivent2Date=getDateFromFile( ivent2Name, plikXml);

    if(ivent1Date.years<ivent2Date.years) cout<<"First ivent is older"<<endl;
    else if(ivent1Date.years>ivent2Date.years) cout<<"Second ivent is older"<<endl;
    else
    {
        if(ivent1Date.months<ivent2Date.months) cout<<"First ivent is older"<<endl;
        else if(ivent1Date.months>ivent2Date.months) cout<<"Second ivent is older"<<endl;
        else
        {
            if(ivent1Date.days<ivent2Date.days) cout<<"First ivent is older"<<endl;
            else if(ivent1Date.days>ivent2Date.days) cout<<"Second ivent is older"<<endl;
            else
            {
                cout<<"Ivent's dates are same"<<endl;

            }
        }
    }
}

Date getDateFromFile(string iventName, CMarkup* plikXml)
{
    Date date;
    date.days=0;
    date.months=0;
    date.years=0;
    string dateInString="";
    plikXml->ResetPos();
    plikXml->FindElem();
    plikXml->IntoElem();
    while(plikXml->FindElem("Ivent"))
    {
        plikXml->IntoElem();
        plikXml->FindElem("Name");

        if(plikXml->GetData()==iventName)
        {
            plikXml->FindElem("Date");
            dateInString=plikXml->GetData();
            date=getDateFromString(dateInString);
            break;
        }
        plikXml->OutOfElem();
    }
    return date;
}

void compareAmounts(CMarkup* plikXml)
{
    int ivent1Amount, ivent2Amount;
    string ivent1Name, ivent2Name;
    cout<<"Enter name of first ivent: ";
    cin>>ivent1Name;
    cout<<"Enter name of second ivent: ";
    cin>>ivent2Name;

    ivent1Amount=getAmountFromFile( ivent1Name, plikXml);
    ivent2Amount=getAmountFromFile( ivent2Name, plikXml);

    if(ivent1Amount<ivent2Amount) cout<<"First ivent's amount is less"<<endl;
    else if(ivent1Amount>ivent2Amount) cout<<"Second ivent's amount is less"<<endl;
    else
    {
        cout<<"Ivent's amounts are same"<<endl;
    }
}

int getAmountFromFile(string iventName, CMarkup* plikXml)
{
    int amount=0;
    string amountInString="";
    plikXml->ResetPos();
    plikXml->FindElem();
    plikXml->IntoElem();
    while(plikXml->FindElem("Ivent"))
    {
        plikXml->IntoElem();
        plikXml->FindElem("Name");

        if(plikXml->GetData()==iventName)
        {
            plikXml->FindElem("Amount");
            amountInString=plikXml->GetData();
            amount=konwersjaStringNaInt(amountInString);
        }
        plikXml->OutOfElem();
    }
    return amount;
}

string getCurrentDateTime(void )
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

int getDaysCountSelectedMonth( string date )
{
    int month=konwersjaStringNaInt(date.substr(0,2));
    int years=konwersjaStringNaInt(date.substr(3,4));

    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12) return 31;
    else if(month==4||month==6||month==9||month==11) return 30;
    else if(month==2 && (years % 4) == 0) return 29;
    else if(month==2 && (years % 4) != 0) return 28;
    else return 0;
}
