#include "Hashing_table.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#define pr 31
using namespace std;

Hashing_table::Hashing_table()
{
  current_size=65563; //Aρχικό μέγεθος του πίνακα.
  Ar=(char **)malloc(sizeof(char *)*current_size);
  times_in_txt=(unsigned int *)malloc(sizeof(unsigned int)*current_size); //Βλέπε αταξινόμητο.
  p=(unsigned long long int*)calloc(sizeof(unsigned long long int),current_size);
  if(p==NULL || Ar==NULL || times_in_txt==NULL)
  {
    exit(1);
  }
  occupied=0;
}

bool Hashing_table::insert(char *s)
{
  static char *temp;
  temp=transform(s);
  if(temp==NULL)
  {
    return false;
  }
  unsigned long long int sum=0,m=1e9+9,gin;
  unsigned short int i=0;
  gin=pow(pr,0);
  while(temp[i]!='\0')
  {
    sum+=(int)((temp[i]-47)*gin)%m;//Άθροισμα κωδικών ASCII
    i++;
    gin=(int)(pow(pr,i))%m;
  }
  if(found(temp,sum) && occupied>0) //Αν δεν υπάρχει συνέχησε.
  {
    return true;
  }
  if(occupied==(current_size/2))//Αν ο παράγοντας φόρτωσης ειναι 0.5
  {
    update_table();
  }
  if(p[sum%current_size]==0) //Κενή θέση.
  {
    p[sum%current_size]=sum;
    Ar[sum%current_size]=temp;
    times_in_txt[sum%current_size]=1;
    occupied++;
    return true;
  }
  else //Σύγκρουση.
  {
    unsigned long long int the=sum%current_size;
    if(the==current_size-1) //Αν είναι η τελευταία θέση του πίνακα.
    {
      the=0;
    }
    else //Αλλιώς.
    {
      the++;
    }
    while(true) //Βρόχος για να βρεθεί η θέση εισαγωγής.
    {
      if(the==current_size-1)
      {
        if(p[the]==0)
        {
          p[the]=sum;
          Ar[the]=temp;
          occupied++;
          times_in_txt[the]=1;
          return true;
        }
        else //Σύγκρουση
        {
          the=0; //Προχώρα στην πρώτη θέση του πίνακα.
        }
      }
      else
      {
        if(p[the]==0) //Κενή θέση.
        {
          p[the]=sum;
          Ar[the]=temp;
          occupied++;
          times_in_txt[the]=1;
          return true;
        }
        else //Σύγκρουση.
        {
          the++; // Προχώρα στην επόμενη θέση.
        }
      }
    }
  }
}

bool Hashing_table::found(char *s,unsigned long long int sum )
{
  if(p[sum%current_size]==0) //Αν η θέση είναι κενή τότε δεν υπάρχει το στοιχείο.
  {
    return false;
  }
  else
  { // Όμοια με την εισαγωγή.
    if(strcmp(s,Ar[sum%current_size])==0)
    {
      return true;
    }
    unsigned long int the=sum%current_size,count=0; //Το count δείχνει το πλήθος των στοιχείων που εξετάστηκαν.
    if(the==current_size-1)
    {
      the=0;
    }
    else
    {
      the++;
    }
    while(true)
    {
      if(the==current_size-1)
      {
        if(p[the]==0)
        {
          return false;
        }
        else
        {
          if(strcmp(s,Ar[the])==0) // Δυο διαφορετικά string μπορεί να έχουν ίδιο άθροισμα κωδικών ASCII
          { //Επιπλέον ελεγχος.
            times_in_txt[the]++;
            return true;
          }
          else
          {
            the=0;
            count++;
          }
        }
      }
      else
      {
        if(p[the]!=0)
        {
          if(strcmp(s,Ar[the])==0)
          {
            times_in_txt[the]++;
            return true;
          }
          else
          {
            count++;
            the++;
          }
        }
        else
        {
          return false;
        }
      }
      if(count==current_size) // Αν το count είναι ισο με το το μέγεθος του πίνακα τότε δεν υπάρχει στον πίνακα.
      {
        return false;
      }
    }
  }
}

void Hashing_table::update_table()
{
  ifstream ifs;
  unsigned long int size;
  ifs.open("primes.txt",ios::in);//΄Ανοιγμα αρχείου primes.txt
  if(ifs.is_open())
  {
    cout<<"file opened normally!"<<endl;
    while(ifs>>size)
    {
      if(size>=current_size*2) //Βρίσκει μέγεθος για τον πίνακα.
      {
        break;
      }
    }
  }
  else
  {
    cout<<"FILE ERROR!"<<endl;
    cout<<"EXITING!"<<endl;
    exit(1);
  }
  ifs.close();
  char **Ar_temp;//Πίνακες για την μεταφορά των δεδομένων.
  unsigned int *times_in_txt_temp;
  unsigned long long int *p_temp;
  unsigned long int count=0;
  times_in_txt_temp=(unsigned int *)calloc(sizeof(unsigned int),occupied);//Δυναμική δέσμευση χώρου.
  Ar_temp=(char **)malloc(sizeof(char *)*occupied);
  p_temp=(unsigned long long int *)malloc(sizeof(unsigned long long int)*occupied);
  if(times_in_txt_temp==NULL || Ar_temp==NULL || p_temp==NULL)//Δεν υπάρχει διαθέσιμος χώρος στην μνήμη.
  {
    exit(1);
  }
  for(unsigned long long int i=0;i<current_size;i++)
  {
    if(count==occupied)//Έχουν αντιγραφεί ολα τα στοιχεία.
    {
      break;
    }
    if(p[i]==0)//Κενή θέση.
    {
      continue;//Προχώρα στην επόμενη επανάληψη.
    }
    Ar_temp[count]=Ar[i];//Aντιγραφή δεδομένων.
    p_temp[count]=p[i];
    times_in_txt_temp[count]=times_in_txt[i];
    count++;
  }
  free(Ar);
  free(times_in_txt);
  free(p);
  Ar=(char **)malloc(sizeof(char *)*size);
  times_in_txt=(unsigned int *)malloc(sizeof(unsigned int)*size);
  p=(unsigned long long int *)calloc(sizeof(unsigned long long int),size);//Xρήση calloc για να δεσμεύεται χώρος με αρχική τιμή 0.
  if(p==NULL || times_in_txt_temp==NULL || Ar==NULL)
  {
    exit(1);
  }
  current_size=size;//Ενημέρωση του μεγέθους του πίνακα.
  for(unsigned long int i=0;i<occupied;i++)//Επιστροφή των δεδομένων στους αρχικούς πίνακες.
  {
    if(p[(p_temp[i])%current_size]==0)//Όμοια με την εισαγωγή
    {
      p[(p_temp[i])%current_size]=p_temp[i];
      Ar[p_temp[i]%current_size]=Ar_temp[i];
      times_in_txt[p_temp[i]%current_size]=times_in_txt_temp[i];
    }
    else
    {
       unsigned long int the=p_temp[i]%current_size;
       if(the==current_size-1)
       {
         the=0;
       }
       else
       {
        the++;
       }
       while(true)
       {
        if(the==current_size-1)
        {
          if(p[the]==0)
          {
            p[the]=p_temp[i];
            Ar[the]=Ar_temp[i];
            times_in_txt[the]=times_in_txt_temp[i];
            break;
          }
          else
          {
            the=0;
          }
        }
        else
        {
          if(p[the]==0)
          {
            p[the]=p_temp[i];
            Ar[the]=Ar_temp[i];
            times_in_txt[the]=times_in_txt_temp[i];
            break;
          }
          else
          {
            the++;
          }
        }
      }
    }
  }
}

void Hashing_table::get_info(char *f)
{
  ofstream ofs;
  ofs.open(f,ios::out|ios::app);//'Ανοιγμα του αρχείο με όνομα argv[2]
   if(!ofs.is_open())//Αποτυχία αρχείου.
  {
    cout<<"FILE ERROR!"<<endl;
    cout<<"EXITING"<<endl;
    exit(1);
  }
  srand(time(NULL));//seed ΝULL
  char **temp;
  unsigned int *temp2;
  temp=(char **)malloc(sizeof(char *)*occupied);//Δέσμευση χώρου.
  temp2=(unsigned int *)malloc(sizeof(unsigned int)*occupied);//Δέσμευση χώρου.
  if(temp==NULL || temp2==NULL)
  {
    exit(1);
  }
  unsigned long int count=0;
  for(unsigned long int i=0;i<current_size;i++)//Μεταφορά των δεδομένων σε πινακές μεγέθους ισο με το occupied.
  {
    if(count==occupied)
    {
      break;
    }
    if(p[i]!=0)//Αν δεν είναι κενή η θέση.
    {
      temp[count]=Ar[i];
      temp2[count]=times_in_txt[i];
      count++;
    }
  }
  count=0;
  unsigned long int *p2;
  p2=(unsigned long int *)malloc(sizeof(unsigned long int)*1000);
  if(p==NULL)
  {
    exit(1);
  }
  for(short int i=0;i<1000;i++)
  {
    p2[i]=rand()%occupied;//παραγωγή ψευδοτυχαίων αριθμών.
  }
  while(count!=1000)
  {
    ofs<<temp[p2[count]]<<" is in text "<<temp2[p2[count]]<<" times"<<endl;//Στέλνονται δεδομένα στο αρχείο argv[2]
    count++;
  }
  ofs.close();
  free(p2);//Αποδέσμευση.
  free(temp2);
}

bool Hashing_table::search(char *s)
{
  static char *temp;
  temp=transform(s);
  if(temp==NULL)
  {
    return false;
  }
  unsigned long long int sum=0,m=1e9+9,gin;
  unsigned short int i=0;
  gin=pow(pr,0);
  while(temp[i]!='\0')
  {
    sum+=(int)((temp[i]-47)*gin)%m;//Άθροισμα κωδικών ASCII
    i++;
    gin=(int)(pow(pr,i))%m;
  }
  if(p[sum%current_size]==0) //Αν η θέση είναι κενή τότε δεν υπάρχει το στοιχείο.
  {
    return false;
  }
  else
  { // Όμοια με την εισαγωγή.
    if(strcmp(s,Ar[sum%current_size])==0)
    {
      return true;
    }
    unsigned long int the=sum%current_size,count=0; //Το count δείχνει το πλήθος των στοιχείων που εξετάστηκαν.
    if(the==current_size-1)
    {
      the=0;
    }
    else
    {
      the++;
    }
    while(true)
    {
      if(the==current_size-1)
      {
        if(p[the]==0)
        {
          return false;
        }
        else
        {
          if(strcmp(s,Ar[the])==0) // Δυο διαφορετικά string μπορεί να έχουν ίδιο άθροισμα κωδικών ASCII
          { //Επιπλέον ελεγχος.
            return true;
          }
          else
          {
            the=0;
            count++;
          }
        }
      }
      else
      {
        if(p[the]!=0)
        {
          if(strcmp(s,Ar[the])==0)
          {
            return true;
          }
          else
          {
            count++;
            the++;
          }
        }
        else
        {
          return false;
        }
      }
      if(count==current_size) // Αν το count είναι ισο με το το μέγεθος του πίνακα τότε δεν υπάρχει στον πίνακα.
      {
        return false;
      }
    }
  }
}
