#ifndef AVL_H
#define AVL_H
#include "Array.h"

struct node2 //Υλοποίηση κόμβου ενος δέντρου.
{
  node2 *right;
  node2 *left;
  char *s; //το string.
  unsigned int times_found; //Πλήθος εμφανίσεων του string.
  int height; //Ύψος αριστερού υπόδεντρου-ύψος δεξιού υπόδεντρου.
};

class AVL:private Array //Κληρονομεί απο την κλάσης Array για να χρησιμοποιηθούν κάποιος συναρτήσεις της.
{
  struct node2 **Ar;//Πίνακας απο struct όμοια με το απλό δυαδικό.
  unsigned long int size;
  node2 *root;//Ρίζα δέντρου.
  public:
    int get_height(struct node2 *);
    int get_balance(struct node2 *);
    ~AVL();//καταστροφέας.
    AVL();// Κενός κατασκευαστής.
    int find_height(struct node2 *);//Συνάρτηση που υπολογίζει αναδρομικά το ύψος ενος δέντρου.
    using Array::transform; //Βλέπε Array.
    void set_balance_factor(struct node2 *); //Συνάρτηση που βρίσκει τον balance_factor ενός κόμβου.
    bool insert_node(char *); //Συνάρτηση για την εισαγωγή.
    void left_left_rotation(struct node2 *);//Απλή δεξιά περιστροφή.
    void right_right_rotation(struct node2 *);//Απλή αριστερή περιστροφή.
    struct node2 *find_parent(char *,bool &); // Συνάρτηση που βρίσκει τον πατέρα ενος κόμβου.
    bool found(char *);//Συνάρτηση που ελέγχει αν ενα string υπάρχει ηδη στο δέντρο.
    void inorder(struct node2 *);//Βλέπε απλο δυαδικό δέντρο.
    void preorder(struct node2 *);
    void postorder(struct node2 *);
    bool search(char *);//Συνάρτηση για την αναζήτηση string στο δέντρο.
    struct node2 *get_root() {return root;};
    bool delete_node(char *);//Συνάρτηση για την διαγραφή string.
    struct node2 *left_most(struct node2 *);//Βλέπε δυαδικό δέντρο.
    struct node2 *find_current(char *);//Συνάρτηση που επιστρέφει δεικτή σε struct όταν βρίσκει το struct που περιέχει το string.
    void find_unbalanced(struct node2 *);//Συνάρτηση για τον εντοπισμό μη ισορροπιμένων κόμβων.
    void get_info(char *);//Συνάρτηση που στέλνει δεδομένα στο αρχείο με όνομα argv[2]
};
#endif
