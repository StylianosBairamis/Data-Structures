#include "Sorted_array.h"
#include "cstring"
#include <cstdlib>

bool Sorted_array::search(char *s,long int &the)  // Συνάρτηση που αναζητά string και επιστρέφει με αναφορά αν αυτό υπάρχει.
{
  unsigned long int begin=0;
  unsigned long int mid;
  unsigned long int end=current_size-1;
  the=-999;
  while(begin<=end)  //Ξεκινάει επανάληψη.
  {
    mid=(begin+end)/2;  // Η μεταβλητή mid δείχνει στην μέση του πίνακα.
    if(strcmp(s,Ar[mid])==0)  // Με την συνάρτηση strcmp συγκρίνω αν το πρώτο string (s) είναι το ίδιο με το string που βρίσκεται στη θέση mid του πίνακα Ar.
    {      //Άν ισχύει.
      the=mid;  //Αποθηκεύω στην μεταβλήτη the την θέση στον πίνακα της λέξη που αναζητώ.
      return true; // Και βγαίνω απο την συνάρτηση επιστρέφοντας σώστο.
    }
    if(strcmp(s,Ar[mid])>0) // Άν το string s είναι μεγαλύτερο από το string Ar[mid]--> Μετατοπίζω την μεταβλητή begin μια θέση μπροστά απο την μεταβλητή mid μικραίνοντας έτσι τον πίνακα κατά το ήμισυ.
    {
      begin=mid+1;
    }
    if(strcmp(s,Ar[mid])<0)  // Άν το string s είναι μικρότερο απο το string Ar[mid]--> Μετατοπίζω την μεταβλητή begin μια θέση πίσω απο την μεταβλητή mid μικραίνοντας έτσι τον πίνακα κατά το ήμισυ.
    {
      end=mid-1;
    }
    if(begin>end)  // Αν η μεταβλητή begin γινεί μεγαλύτερη απο την end --> σπάει η επαναληπτική διαδικασία της while.
    {
      break;
    }
  }
  return false; // Αν η συναρτήση δεν βρεί την λεξή που αναζητά --> βγαίνει απο την συνάρτηση και επιστρέφει λάθος.
}

void Sorted_array::merge_sort(unsigned long int begin,unsigned long int end)  // Υλοποίηση της merge_sort για την ταξινόμηση του πίνακα.
{
  unsigned long int mid;
  if(begin<end)
  {
    mid=(begin+end)/2;
    merge_sort(begin,mid);
    merge_sort(mid+1,end);
    merge(begin,end,mid);
  }
}

void Sorted_array::merge(unsigned long int begin,unsigned long int end,unsigned long int mid)  //Συνάρτηση για την συγχώνευση δυο πινάκων.
{
  unsigned long int i,j,k; // μεταβλητές για τον χειρισμό των πινάκων.
  i=k=begin;
  j=mid+1;
  char *temp[getCurrent()-1]; // Temp πίνακας για την αποθήκευση των pointers που δείχνουν σε string;
  int temp2[getCurrent()-1]; // Temp πίνακας για την αποθήκευση τους πλήθους εμφανίσεων του κάθε string.
  while (i<=mid && j<=end)
  {
    if (strcmp(Ar[i],Ar[j])<0)//Mεταφορά δεδομένων στους πίνακες temp.
    {
      temp[k]=Ar[i];
      temp2[k]=times_in_txt[i];
      k++;
      i++;
    }
    else//Oυσιαστικά το strcmp είναι >0
    {
      temp[k]=Ar[j];
      temp2[k]=times_in_txt[j];
      k++;
      j++;
    }
  }
  while (i<=mid)//Αδειάζουμε τα στοιχεία του πίνακα απο την μέση και κάτω, διότι εχούν τοποθετηθεί ολά απο την μέση και πάνω
  {
    temp[k]=Ar[i];
    temp2[k]=times_in_txt[i];
    k++;
    i++;
  }
  while (j<=end)//Αδειάζουμε τα στοιχεία του πίνακα απο την μέση και κάτω, διότι εχούν τοποθετηθεί ολά απο την μέση και πάνω
  {
    temp[k]=Ar[j];
    temp2[k]=times_in_txt[j];
    k++;
    j++;
  }
  for (i=begin;i<k;i++)
  {
    Ar[i]=temp[i];//Μεταφορά τον δεδομένων πίσω στους αρχικόυς πίνακες
    temp2[i]=times_in_txt[i];
  }
}

void Sorted_array::operator+=(char *s) //Υπερφόρτωση τέλεστη για την εισαγωγή δεδομένου στην σωστή θέση.
{
  char *temp;
  temp=transform(s); // Μετασχηματίζει το στρίνγκ.
  if(temp==NULL)   // Aν δεν μπορέσει να μετασχηματιστεί το string --> βγές απο την συναρτήση χωρίς επιστρέψεις τίποτα.
  {
    return ;
  }
  static long int the;
  search(temp,the);  // Ψάχνει να βρεί αν η λέξη υπάρχει.
  if(the!=-999)   // Αν υπάρχει-->αυξάνει το πλήθος εμφάνισής της και βγαίνει απο την συνάρτηση χωρίς επιστρέψει τίποτα.
  {
    times_in_txt[the]++;
    return ;
  }
  for(unsigned long int i=0;i<current_size-1;i++)
  {
    if(strcmp(temp,Ar[i])>0 && strcmp(temp,Ar[i+1])<0)  // Ελέγχει σε ποιά θέση πρέπει να εισαχθεί η νέα λέξη και οταν βρεί την σωστή θέση την αποθηκεύει στην μεταβλητή the.
    {
       the=i+1;
       break;
    }
  }
  current_size++;// Αυξάνει το μέγεθος του πίνακα κατα 1.
  Ar=(char **)realloc(Ar,current_size*sizeof(char *));  //Δεσμεύει χώρο στο array.
  times_in_txt=(unsigned int *)realloc(times_in_txt,current_size*sizeof(unsigned int)); // Δεσμεύει χώρο στο array που κρατά το πλήθος εμφάνισης του κάθε string.
  if(Ar==NULL || times_in_txt==NULL)  // Αν η realloc αποτύχει--> τερματισμός του προγράμματος με αποτυχία.
  {
    exit(1);
  }
  for(unsigned long int i=current_size-1;i>the;i--)  // Μετατοπίζει τα string του πίνακα κατα μια θέση.
  {
    Ar[i]=Ar[i-1];
    times_in_txt[i]=times_in_txt[i-1];
  }
  Ar[the]=temp; //Αποθηκεύει το καινούριο string στον πίνακά μας στην σωστή θέση(the).
  times_in_txt[the]=1; // Βάζει πλήθος=1 για την καινούργιο string.
}

bool Sorted_array::delete_str(char *s) //Συνάρτηση που διαγράφει string απο τον πίνακα.
{
  char *temp;
  temp=transform(s); //Μετασχηματίζει το στρίνγκ.
  if(temp==NULL)  //Aν δεν μπορέσει να μετασχηματιστεί το string --> Επιστρέφει λαθος.
  {
    return false;
  }
  static long int the;
  search(s,the);  //Ψάχνει να βρεί αν η λέξη υπάρχει.
  if(the==-999)  //Αν η λέξη δεν υπάρχει--> Επιστρέφει λάθος.
  {
    return false;
  }
  if(times_in_txt[the]>1) //Αν η λέξη υπάρχει πάνω απο μια φορά αφαιρεί ΕΝΑ πλήθος της.
  {
    times_in_txt[the]--;
  }
  else // Αν υπάρχει μια μόνο φορά.
  {
    for(unsigned long long int i=the;i<current_size-1;i++) // Μετατοπίζει τα στρινγκ του πίνακα κατά μια θέση με σκοπό να αφαιρέσει την λέξη που θέλει από τον πίνακα.
    {
      times_in_txt[i]=times_in_txt[i+1];
      Ar[i]=Ar[i+1];
    }
    current_size--;//Μειώνει το μέγεθος του πίνακα κατα 1
    times_in_txt=(unsigned int*)realloc(times_in_txt,sizeof(unsigned int)*current_size);
    Ar=(char **)realloc(Ar,sizeof(char *)*current_size);
    if(Ar==NULL ||times_in_txt==NULL)
    {
        exit(1);
    }
  }
  free(temp); //Aπελευθέρωσε τον δεσμευμένο χώρο του string.
  return true;
}
