#ifndef Sorted_array_h
#define Sorted_array_h
#include "Array.h"
class Sorted_array:public Array  // Η κλάση του ταξινομημένου πίνακα κληρονομεί απο την κλάση του αταξινόμητου πίνακα.
{
  public:
    Sorted_array():Array() {}; //Κατασκευαστής
    void operator+=(char *p);  //Υπερφόρτωση τέλεστη για την εισαγωγή δεδομένου στην σωστή θέση.
    bool search(char *,long int &); // Συνάρτηση που αναζητά string και επιστρέφει με αναφορά αν αυτό υπάρχει.
    void merge(unsigned long  int,unsigned long int,unsigned long int); //Συνάρτηση για την συγχώνευση δυο πινάκων.
    void merge_sort(unsigned long int,unsigned long int); // Υλοποίηση της merge_sort για την ταξινόμηση του πίνακα.
    bool delete_str(char *); // Συνάρτηση που διαγράφει string απο τον πίνακα.
};
#endif
