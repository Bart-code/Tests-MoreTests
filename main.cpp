#include <iostream>
#include <string>
#include <sstream>
#include "Markup.h"
#include <stdio.h>
#include <time.h>

using namespace std;

CMarkup initFile( string );
void addIvent( CMarkup* );
string convertIntegerToString( int );
int convertStringToInteger( string );
void showAllIvents( CMarkup* );
int getDateFromString( string );
void compareDates( CMarkup* );
int getDateFromFile( string , CMarkup* );
void compareAmounts( CMarkup* );
int getAmountFromFile( string , CMarkup* );
string getCurrentDateTime( void );
int getDaysCountSelectedMonth( string );
bool isDateCorrect( string );
int getLastDayDateCurrentMonth( void );
string changeDateFormat( string );

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

            cout<<"Enter date in yyyy-mm-dd format: ";
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


    do
    {   cout<<"Set date of ivent (in format rrrr-mm-dd): ";
        cin>>date;
    }
    while(!(isDateCorrect(date)));
    date=convertIntegerToString(getDateFromString(date));
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

string convertIntegerToString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();
    return str;
}

int convertStringToInteger(string liczba)
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
        cout<< changeDateFormat(plikXml->GetData())<<endl;
        plikXml->FindElem("Amount");
        cout<<plikXml->GetData()<<endl;
        plikXml->OutOfElem();
    }
}

int getDateFromString(string dateInString)
{
    int newDate;
    string someString=dateInString.erase(4,1);
    someString=someString.erase(6,1);
    return convertStringToInteger(someString);
}

void compareDates(CMarkup* plikXml)
{
    int ivent1Date, ivent2Date;
    string ivent1Name, ivent2Name;
    cout<<"Enter name of first ivent: ";
    cin>>ivent1Name;
    cout<<"Enter name of second ivent: ";
    cin>>ivent2Name;

    ivent1Date=getDateFromFile( ivent1Name, plikXml);
    ivent2Date=getDateFromFile( ivent2Name, plikXml);

    if(ivent1Date<ivent2Date) cout<<"First ivent is older"<<endl;
    else if(ivent1Date>ivent2Date) cout<<"Second ivent is older"<<endl;
    else cout<<"Ivent's dates are same"<<endl;

}

int getDateFromFile(string iventName, CMarkup* plikXml)
{
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
            return convertStringToInteger(plikXml->GetData());
        }
        plikXml->OutOfElem();
    }
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
            amount=convertStringToInteger(amountInString);
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

    int years=convertStringToInteger(date.substr(0,4));
    int month=convertStringToInteger(date.substr(5,2));

    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12) return 31;
    else if(month==4||month==6||month==9||month==11) return 30;
    else if(month==2 && (years % 4) == 0) return 29;
    else if(month==2 && (years % 4) != 0) return 28;
    else return 0;
}

int getLastDayDateCurrentMonth( void )
{
    string date=getCurrentDateTime();
    string daysCountCurrentMonth=date.substr(8,2);
    int dateInteger;
    date=date.replace(8,2, daysCountCurrentMonth);
    dateInteger=getDateFromString(date);
    return dateInteger;
}

bool isDateCorrect( string date)
{
    int datePart;
    int maxDate = getLastDayDateCurrentMonth();
    int dateInteger = getDateFromString(date);
    int daysMaxCount = getDaysCountSelectedMonth( date );

    if(date.length()!=10)
    {
        cout<<"The date has incorrect format"<<"1"<<endl;
        return false;
    }
    if( dateInteger > maxDate || dateInteger < 20000101)
    {
        cout<<"The date has incorrect format"<<"2"<<endl;
        return false;
    }
    datePart=convertStringToInteger(date.substr(5,2));
    if(datePart>12 || datePart < 1)
    {
        cout<<"The date has incorrect format"<<"3"<<endl;
        return false;
    }

    datePart=convertStringToInteger(date.substr(8,2));
    if(datePart>daysMaxCount || datePart < 1)
    {
        cout<<"The date has incorrect format"<<"4"<<endl;
        return false;
    }
    return true;
}

string changeDateFormat( string date)
{
    string dateString, years, months, days;
    years = date.substr(0,4);
    months = date.substr(4,2);
    days = date.substr(6,2);
    dateString = years + "-" + months + "-" + days;
    return dateString;
}


