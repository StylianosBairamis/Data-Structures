#ifndef Array_h
#define Array_h
class Array
{
  protected:
    char **Ar; // Πίνακας πινάκων
    unsigned long int current_size; // Μέγεθος του πίνακα.
    unsigned int *times_in_txt; // πλήθος εμφανίσεων του κάθε string.
  public:
    Array(); //Κατασκευαστής.
    ~Array(); // Καταστροφέας.
    char *transform(char *); // Συνάρτηση που μετασχηματίζει string.
    bool insert(char *); // Συνάρτηση για την εισαγώγη στοιχείου στο τέλος του πίνακα.
    bool Delete(char *); // Συνάρτηση που διαγράφει ενα string.
    void search(char *,long int &); // Συνάρτηση που αναζητά ενα string.
    unsigned long int getCurrent() {return current_size;}; //getter που επιστρέφει το μέγεθος του πίνακα.
    void get_str(unsigned long int); // Συνάρτηση που επιστρέφει το string που βρίσκεται στην i-οστή θέση.
    unsigned long int * get_random(); // Συνάρτηση που επιστρέφει πίνακα με 1000 τυχαίους ακέραιους ακέραιους.
    void get_info(char *); // Συνάρτηση που επιστρέφει το πλήθος εμφανίσεων του string στο αρχείο με όνομα argv[2]
};
#endif
