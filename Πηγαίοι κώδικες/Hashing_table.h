#ifndef Hashing_table_h
#define Hashing_table_h
#include "Array.h"

class Hashing_table:public Array
{
  unsigned long long int*p; //Πίνακας που αποθηκεύεται το άθροισμα των κωδικών ASCII των χαρακτήρων του κάθε string
  unsigned long int occupied; //Αριθμός των θέσεων του πίνακα που είναι κατελλημένες.
  public:
     Hashing_table();
     bool insert(char *); //Συνάρτηση για την εισαγωγή.
     bool found(char *,unsigned long long int); //Συνάρτηση που ελέγχει αν ένα string υπάρχει ήδη στον πίνακα.
     void update_table(); //Συνάρτηση για την μετατροπή του πίνακα όταν ο παράγοντας φόρτωσης γίνει ίσος με 0.5
     unsigned int get_occupied() {return occupied;};
     void get_info(char *); // Συνάρτηση στέλνει πληροφορίες για το string και τις εμφανίσεις του στο αρχείο με όνομα argv[2].
     bool search(char *);
};
#endif
