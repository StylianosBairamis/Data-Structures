#ifndef Bnary_h
#define Bnary_h
#include "Array.h"

struct node  //Υλοποιήση κόμβου του δέντρου.
{
  node *right;
  node *left;
  char *s;
  unsigned long int times_found;
};

class Bnary :private Array // Η κλάση κληρονομεί τα στοιχεία της κλάσης Array και μετατρέπει τις ιδιότητες αυτές σε private.
{
  node *root; //Ρίζα του δέντρου
  node **Ar; // Πίνακας απο struct
  unsigned long int size;
  public:
    Bnary(); // Κατασκευαστής.
    ~Bnary(); // Καταστροφέας.
    bool insert_node(char *); //Εισαγωγή στο δέντρο.
    using Array::transform; //Χρήση τελεστή using βλέπε την κλάση Array.
    void get_info(char *); //Η συνάρτηση εμφανίζει πόσες φορές ενα string υπάρχει.
    bool found(char *); //Συάρτηση που ελέγχει αν ενα string υπάρχει στο δέντρο.
    void inorder(struct node *);
    void preorder(struct node *);
    void postorder(struct node *);
    struct node *get_root() {return root;};// Συνάρτηση που επιστρέφει την διεύθυνση μνήμης της ρίζας.
    bool search(char *);// Συνάρτηση για την Υλοποιήση της αναζήτησης στο δέντρο.
    bool delete_node(char *); //Συνάρτηση για την διαγραφή string απο το δέντρο.
    struct node *find_current(char *); // Συνάρτηση που επιστρέφει ενα δείκτη σε struct που περιέχει ενα συγκεκριμένο string
    struct node *find_parent(char *,bool &);//Συνάρτηση που επιστρέφει ενα δείκτη σε struct επιστρέφει επισής με αναφορα μια μεταβλήτη bool
    struct node *left_most(struct node *); // Συναρτήση που επιστρέφει δείκτη	σε struct που περιέχει το string που βρίσκεται στην πιο αριστερή θέση του δέντρου.
};
#endif
