#include "Bnary.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ctime>

Bnary::Bnary()
{
  root=NULL; //κενό δέντορ.
  size=0;
  Ar=NULL;
}

bool Bnary::insert_node(char *s)
{
  static char *temp;
  temp=transform(s); //Τροποποίηση του string
  if(temp==NULL)
  {
    return false;
  }
  if(found(temp) && root!=NULL) // Αναζήτητηση αν το string υπάρχει ηδη στο δέντρο.
  {
    return true;
  }
  node *create; //Δημιουργεία κόμβου.
  create=(node *)malloc(sizeof(node));
  if(create==NULL)
  {
    exit(1);
  }
  (*create).right=(*create).left=NULL;
  (*create).s=(char *)malloc((strlen(temp)+1)*sizeof(char));
  if((*create).s==NULL)
  {
    exit(1);
  }
  strcpy((*create).s,temp);
  free(temp);
  (*create).times_found=1;
  if(root==NULL) //Αν το δέντρο είναι άδειο.
  {
    root=create;
    Ar=(node **)realloc(Ar,sizeof(node *)*(size+1)); //Γέμισμα του πίνακα απο struct.
    if(Ar==NULL)
    {
      exit(1);
    }
    Ar[0]=create;
    size++;
    return true;
  }
  static bool isleft;
  node *current=root,*next;
  while(true) //Βρόγχος για την εισαγωγή στο δέντρο.
  {
    if(strcmp(temp,(*current).s)>0)
    {
      isleft=false;
      next=(*current).right;
    }
    else
    {
      isleft=true;
      next=(*current).left;
    }
    if(next==NULL) // Βρέθηκε η θέση που θα τοποθετηθεί ο κόμβος.
    {
      if(isleft) //Θα τοποθετηθεί αριστερά του τωρινού κόμβου.
      {
        (*current).left=create;
      }
      else //Θα τοποθετηθεί δεξία του τωρινού κόμβου.
      {
        (*current).right=create;
      }
      Ar=(node **)realloc(Ar,sizeof(node *)*(size+1)); // Ενημέρωση του πίνακα των struct.
      if(Ar==NULL)
      {
        exit(1);
      }
      Ar[size]=create;
      size++;
      return true;
    }
    current=next;
  }
  return true;
}

bool Bnary::found(char *s)
{
  node *current=root;
  if(root==NULL) // Κένο δέντρο.
  {
    return false;
  }
  while(strcmp(s,(*current).s)!=0)
  {
    if(strcmp(s,(*current).s)>0)
    {
      current=(*current).right;
    }
    else
    {
      current=(*current).left;
    }
    if(current==NULL)
    {
      return false;
    }
  }
  (*current).times_found++; //Αυξήση του πλήθους εμφανίσεων αν υπάρχει το string στο δέντρο.
  return true;
}

void Bnary::inorder(struct node *other) //Υλοποιήση της διάσχισης κατά σειρά.
{
  if(other==NULL) //Αν δεν υπάρχει κόμβος επέστρεψε
  {
    return;
  }
  inorder((*other).left);//Πάνε στομ αριστερό κόμβο.
  puts(((*other).s)); //Εμφάνισε το string του κόμβου.
  inorder( (*other).right); //Πανε στον δεξί κόμβο.
}

//Τα υπόλοιπα είναι η ίδια η λογική.

void Bnary::postorder(struct node *other) //Υλοποιήση της διάσχισης κατά προδιάταξη.
{
  if(other==NULL)
  {
    return;
  }
  postorder((*other).left);
  postorder( (*other).right);
  puts(((*other).s));
}

void Bnary::preorder(struct node *other) //Υλοποιήση της διάσχισης κατά μεταδιάταξη.
{
  if(other==NULL)
  {
    return;
  }
  puts(((*other).s));
  preorder((*other).left);
  preorder( (*other).right);
}

bool Bnary::search(char *s)
{
  node *current=root;
  if(root==NULL)
  {
    return false;
  }
  while(strcmp(s,(*current).s)!=0)
  {
    if(strcmp(s,(*current).s)>0)
    {
      current=(*current).right; //Πάνε στο δεξί υπόδεντρο.
    }
    else
    {
      current=(*current).left; // Πάνε στο αριστερό υπόδεντρο.
    }
    if(current==NULL)//Δεν βρέθηκε το στοιχείο.
    {
      return false;
    }
  }
  return true;
}

bool Bnary::delete_node(char *s)
{
  static char *temp;
  temp=transform(s);
  if(temp==NULL)
  {
    return false;
  }
  if(root==NULL)
  {
    return false;
  }
  if(!found(temp)) // Αν δεν υπάρχει επέστρεψε.
  {
    return false;
  }
  static bool isleft;
  static node *child;
  child=find_current(temp);
  if((*child).right==NULL && (*child).left==NULL) // Ο κόμβος προς διαγραφή δεν έχει παιδιά
  {
    if(child==root) // Αν είναι η ρίζα.
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else //Αν υπάρχει μια φορά το αφαιρώ απο το δέντρο.
      {
        free(root);
        root=NULL;
      }
      return true;
    }
    else // Αν είναι οποιοδήποτε άλλος κόμβος.
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else
      {
        static node *parent;
        parent=find_parent(temp,isleft); // Βρες τον πατέρα του κόμβου που πρόκειται να διαγραφεί.
        if(isleft)
        {
          free((*parent).left);
          (*parent).left=NULL;
        }
        else //Αν υπάρχει μια φορά το αφαιρώ απο το δέντρο.
        {
          free((*parent).right);
          (*parent).right=NULL;
        }
        return true;
      }
    }
  }
  else if((*child).right!=NULL && (*child).left==NULL) // έχει μόνο δεξί παιδί.
  {
    static node* temp2;
    if(child==root)
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else //Αν υπάρχει μια φορά το αφαιρώ απο το δέντρο.
      {
        temp2=(*root).right;
        free(root);
        root=temp2; // Δεξί παιδί γίνεται η ρίζα.
      }
      return true;
    }
    else
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else //Αν υπάρχει μια φορά το αφαιρώ απο το δέντρο.
      {
        static node *parent;
        temp2=(*child).right;
        parent=find_parent(temp,isleft); // Βρες τον πατέρα του κόμβου που πρόκειται να διαγραφεί
        if(isleft)
        {
          free((*parent).left);
          (*parent).left=temp2;
        }
        else
        {
          free((*parent).right);
          (*parent).right=temp2;
        }
        return true;
      }
    }
  }
  else if((*child).right==NULL && (*child).left!=NULL) // Έχει μόνο αριστερό παιδι.
  {
    static node* temp2;
    if(child==root) //Ο κόμβος που πρόκυται να διαγραφεί είναι η ρίζα.
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else //Αν υπάρχει μια φορά το αφαιρώ απο το δέντρο.
      {
        temp2=(*root).left;
        free(root);
        root=temp2;
      }
      return true;
    }
    else
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else //Αν υπάρχει μια φορά το αφαιρώ απο το δέντρο.
      {
        static node *parent;
        temp2=(*child).left;
        parent=find_parent(temp,isleft);  // Βρες τον πατέρα του κόμβου που πρόκειται να διαγραφεί
        if(isleft)
        {
          free((*parent).left);
          (*parent).left=temp2;
        }
        else
        {
          free((*parent).right);
          (*parent).right=temp2;
        }
        return true;
      }
    }
  }
  else  //Αν έχει δυο παιδιά.
  {
    if(child==root)
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else
      {
        static node *temp3,*temp4;
        temp3=left_most((*child).right); // Βρες το μικρότερο στοιχείο του δεξιού υποδέντρου.
        temp4=find_parent((*temp3).s,isleft); //Βρες τον πατέρα του μικρότερου στοιχείου.
        if((*temp3).right==NULL) //Αν το μικρότερο στοιχείο δεν έχει κανένα στοιχείο (μπορεί να έχει το πολύ ενα και αυτό να είναι δεξί παιδί)
        {
          (*temp3).right=(*root).right;//Ενημέρωση των δεικτών για να δείχνουν στο αριστερό και δεξί υποδεντρό της ρίζας.
          (*temp3).left=(*root).left;
          free(root);
          root=temp3;
          (*temp4).left=NULL; //Αποδέσμευση του πατέρα του μικρότερου στοιχείου απο αυτό.
        }
        else
        {
          (*temp4).left=(*temp3).right;// Δεσμεύση του παιδιού του μικρότερου στοιχείου στον πατέρα του μικρότερου στοιχείου.
          (*temp3).right=(*root).right;
          (*temp3).left=(*root).left;
          free(root);
          root=temp3;
        }
      }
      return true;
    }
    else
    {
      if((*child).times_found>1)
      {
        (*child).times_found--;
      }
      else
      {
        static bool isleft2;
        static node *temp5,*temp6,*temp7;
        temp5=left_most((*child).right);
        temp7=find_parent((*temp5).s,isleft2);
        temp6=find_parent((*child).s,isleft);
        if((*temp5).right==NULL) //Όμοια με πιο πάνω.
        {
          (*temp5).right=(*child).right;
          (*temp5).left=(*child).left;
          free(child);
          if(isleft)
          {
            (*temp6).left=temp5;
          }
          else
          {
            (*temp6).right=temp5;
          }
          (*temp7).left=NULL;
        }
        else
        {
          (*temp7).left=(*temp5).right;
          (*temp5).right=(*child).right;
          (*temp5).left=(*child).left;
          free(child);
          if(isleft)
          {
            (*temp6).left=temp5;
          }
          else
          {
            (*temp6).right=temp5;
          }
        }
      }
    }
    return true;
  }
  return true;
}

inline struct node *Bnary::find_parent(char *s,bool &isleft) //Επιστρέφει με αναφορά αν είναι δεξί ή αριστερό παιδί.
{
  node *current,*previous;
  current=root;
  while(strcmp(s,(*current).s)!=0)
  {
    previous=current; //Γονέας του κόμβου
    if(strcmp(s,(*current).s)>0)
    {
      current=(*current).right;
      isleft=false;
    }
    else
    {
      isleft=true;
      current=(*current).left;
    }
  }
  return previous;
}

inline struct node *Bnary::find_current(char *s)
{
  node *current;
  current=root;
  while(strcmp(s,(*current).s)!=0) //Οσο το string διαφέρει απο το string του τωρινού κόμβου.
  {
    if(strcmp(s,(*current).s)>0)
    {
      current=(*current).right;
    }
    else
    {
      current=(*current).left;
    }
  }
  return current;
}

Bnary::~Bnary()
{
  for(unsigned long int i=0;i<size;i++)
  {
    free((Ar[i])); // Αποδέσμευση του πίνακα απο structs.
  }
  free(Ar);
}

inline struct node *Bnary::left_most(struct node  *other)
{
  if(root==NULL) //Αν είναι κενό δέντρο.
  {
    return NULL;
  }
  static struct node *current=other;
  while((*current).left!=NULL) // Οσο υπάρχει αριστερός κόμβος.
  {
    current=(*current).left;
  }
  return current;
}

void Bnary::get_info(char *f)
{
  ofstream ofs;
  ofs.open(f,ios::out|ios::app); //Άνοιγμα αρχείου και γράψιμο στο τέλος του.
  if(!ofs.is_open())
  {
      exit(1);
  }
  unsigned long int *p;
  srand(time(NULL));// Παραγωγή 1000 ψευδό-τυχαίων αριθμών.
  p=(unsigned long int*)malloc(sizeof(unsigned long int)*1000);
  if(p==NULL)
  {
      exit(1);

  }
  for(short int i=0;i<1000;i++)
  {
      p[i]=rand()%size;
  }
  for(short int i=0;i<1000;i++)
  {
    ofs<<(*Ar[p[i]]).s<<" "<<"is in text "<<(*Ar[p[i]]).times_found<<" "<<"times."<<endl;
  }
  ofs.close();//Κλείσιμο αρχείου.
  free(p);//Αποδέσμευση του δείκτη.
}
