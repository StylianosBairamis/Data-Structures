#include "Array.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

Array::Array() // Κατασκευαστής.
{
  current_size=0;
  Ar=NULL;
  times_in_txt=NULL;
}

Array::~Array()// Καταστροφέας.
{
  free(times_in_txt);
  times_in_txt=NULL;
 /* for(unsigned long long int i=0;i<current_size;i++)
  {
    free(Ar[i]);// Aποδεύσμευση του πίνακα.
  } */
  free(Ar);
  Ar=NULL;
}

char *Array::transform(char *s)  // Συνάρτηση που μετασχηματίζει string.
{
  for(unsigned short int i=0;i<strlen(s);i++)
  {
     if(s[i]>=65 && s[i]<=90)   // Mετατροπή κεφαλαίων σε μικρά.
     {
       s[i]+=32;
     }
  }
  char *p;
  p=(char *)malloc(sizeof(char)*(strlen(s)+1));  // Δεσμεύω χώρο για το string.
  if(p==NULL)  // Αν η malloc αποτύχει--> τερματισμός του προγράμματος με αποτυχία.
  {
    exit(1);
  }
  unsigned short int co=0;
  for(short int i=0;i<strlen(s);i++)
  {
    if((s[i]>=97 && s[i]<=122) || (s[i]>=48 && s[i]<=57))  // Ελέγχει αν ο χαρακτήρας είναι αποδεκτός                                                                γράμμα της αλφαβήτου ή αριθμός.
    {
      p[co]=s[i];   //Aντιγράφει τους αποδεκτούς χαρακτήρες του προηγούμενου στρίνγκ σε ενα καινούριο.
      co++;
    }
  }
  p[co]='\0';
  if(strlen(p)>0) // Αν δόθηκαν αποδεκτοί χαρακτήρες.
  {
    return p;  // Επέστρεψε το στρίνγκ.
  }
  else // Αλλίως.
  {
    return NULL; // Επέστρεψε null.
  }
}

bool Array::insert(char *s)  // Eισαγωγή στοιχείου στο τέλος του πίνακα.
{
  static bool b=0;
  static char *temp;
  static long int th;
  temp=transform(s);   // Μετασχηματίζει το στρίνγκ.
  if(temp==NULL) // Aν δεν μπόρεσε να μετασχηματιστεί το string --> Επέστρεψε λαθος.
  {
    return false;
  }
  search(temp,th);    // Ψάχνει να βρεί αν η λέξη υπάρχει.
  if(th!=-999)        // Αν υπάρχει-->αυξάνει το πλήθος εμφάνισής της.
  {
    times_in_txt[th]++;
    return true;
  } //Αλλιώς δεσμεύει μια ακόμα θέση στο array και στο αντίστοιχο μονοδιάστατο array που κρατά το πλήθος εμφάνισης του κάθε string.
  times_in_txt=(unsigned int *)realloc(times_in_txt,sizeof(unsigned int)*(current_size+1));
  Ar=(char **)realloc(Ar,sizeof(char *)*(current_size+1));
  if(Ar==NULL || times_in_txt==NULL) // Αν η realloc αποτύχει--> Επέστρεψε λαθος.
  {
   return false;
  }
  times_in_txt[current_size]=1;   // Βάζει πλήθος=1 για την καινούργια λέξη(στην τελεύταία θέση του πίνακα)
  Ar[current_size]=temp; //Αποθηκεύει το καινούριο string στον πίνακά μας.
  if(current_size==0)
  {
    current_size++;
     b=0;
  }
  if(current_size>=1 && b==1)
  {
    current_size++;
  }
  b=1;
  return true;
}

unsigned long int *Array::get_random() // Συνάρτηση που επιστρέφει πίνακα με 1000 τυχαίους ακέραιους ακέραιους.
{
  short int count=0;
  unsigned long int *p;
  p=(unsigned long int *)malloc(sizeof(unsigned long int)*1000);  // Δεσμεύω χώρο για τον πίνακα τυχαίων αριθμών.
  if(p==NULL) // Αν η malloc αποτύχει--> τερματισμός του προγράμματος με αποτυχία.
  {
    exit(1);
  }
  srand(time(NULL));
  while(count!=1000)
  {
    p[count]=rand()%current_size;
    count++;
  }
  return p;  // Eπιστρέφει τον πίνακα των τυχαίων αριθμών.
}

void Array::get_info(char *f) // Συνάρτηση που επιστρέφει το πλήθος εμφανίσεων του string στο αρχείο με όνομα argv[2]
{
  ofstream ofs;
  ofs.open(f,ios::out|ios::app); //Άνοιγμα αρχείου και γράψιμο στο τέλος του.
  if(!ofs.is_open())
  {
    cout<<"FILE ERROR!"<<endl;
    cout<<"EXITING!"<<endl;
    exit(1);
  }
  unsigned long int *p;
  p=get_random(); // Παραγωγή 1000 ψευδό-τυχαίων αριθμών.
  for(short int i=0;i<1000;i++)
  {
    ofs<<Ar[p[i]]<<" "<<"is in text "<<times_in_txt[p[i]]<<" "<<"times."<<endl;
  }
  ofs.close();//Κλείσιμο αρχείου.
  free(p);//Αποδέσμευση του δείκτη
}

void Array::search(char *s,long int &the)   // Συνάρτηση που αναζητά ενα string.
{
  char *temp;
  temp=(transform(s));   // Μετασχηματίζει το στρίνγκ.
  if(temp==NULL)  // Aν δεν μπόρεσε να μετασχηματιστεί το string --> βγές απο την συναρτήση χωρίς να επιστρέψεις τίποτα.
  {
    return ;
  }
  the=-999;
  for(unsigned long int i=0;i<current_size;i++)
  {
    if(strcmp(s,Ar[i])==0) //Συγκρίνει με την συναρτήση strcmp αν η πρώτη λέξη (s) είναι ίδια με την δεύετερη λέξη Ar[i] δηλάδη αν η λέξη που αναζητά υπάρχει στον πίνακα μας.
    {
      the=i;  // Αν υπάρχει-->κρατάει στην μεταβλητή the την θέση της λέξης στον πίνακα.
      return ; // Βγές απο την συναρτήση χωρίς να επιστρέψεις τίποτα.
    }
  }
}

bool Array::Delete(char *s)  // Συνάρτηση που διαγράφει ενα string.
{
  static long  int br;
  static char *temp;
  temp=transform(s);   // Μετασχηματίζει το στρίνγκ.
  if(temp==NULL)  // Aν δεν μπορέσει να μετασχηματιστεί το string --> Επιστρέφει λαθος.
  {
    return false;
  }
  search(temp,br);   // Ψάχνει να βρεί αν η λέξη υπάρχει.
  if(br==-999)  // Αν η λέξη δεν υπάρχει--> Επιστρέφει λάθος.
  {
    return false;
  }
  if(times_in_txt[br]>1)    //Αν η λέξη υπάρχει πάνω απο μια φορά αφαιρεί ΕΝΑ πλήθος της.
  {
    times_in_txt[br]--;
  }
  else // Αν υπάρχει μια μόνο φορά.
  {
    for(unsigned long int i=br;i<current_size-1;i++) // Μετατοπίζει τα στρινγκ του πίνακα κατά μια θέση με σκοπό να αφαιρέσει την λέξη που θέλει από τον πίνακα.
    {
      times_in_txt[i]=times_in_txt[i+1];
      Ar[i]=Ar[i+1];
    }
    current_size--; // Μειώνει το μέγεθος του πίνακα κατα 1.
    Ar=(char **)realloc(Ar,sizeof(char *)*current_size);
    times_in_txt=(unsigned int *)realloc(times_in_txt,sizeof(unsigned int)*current_size);
    if(Ar==NULL || times_in_txt==NULL)
    {
      exit(1);
    }
  }

  free(temp); // Aπελευθέρωσε τον δεσμευμένο χώρο του string.
  return true;
}
