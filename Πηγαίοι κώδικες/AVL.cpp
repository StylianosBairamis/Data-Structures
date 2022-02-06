#include "AVL.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;


AVL::AVL()
{
  root=NULL; //Κενό δέντρο.
  Ar=NULL; //Κενός πίνακας.
  size=0;
}

int AVL::find_height(struct node2 *other)
{
  if(other==NULL)
  {
    return 0;
  }
  static int left,right;
  left=1+find_height((*other).left);  //Αναδρομική κλήση.
  right=1+find_height((*other).right); //Αναδρομική κλήση.
  return left>right?left:right; // Χρήση τελεστή ?
}

bool AVL::insert_node(char *s)
{
  static char *temp;
  temp=transform(s); //Τροποποίηση string
  if(temp==NULL)
  {
    return false;
  }
  if(found(temp)) //Aν υπάρχει ήδη το string.
  {
    return true;
  }
  static node2 *create; // Δέσμευση χώρου.
  create=(node2 *)malloc(sizeof(node2));
  if(create==NULL)
  {
    exit(1);// Ανεπαρκής χώρος.
  }
  (*create).left=(*create).right=NULL;
  (*create).times_found=1;
  (*create).s=temp;
  (*create).height=1;
  if(root==NULL)//Κενό δέντρο.
  {
    root=create;
    Ar=(node2 **)realloc(Ar,sizeof(node2 *)*(size+1));
    if(Ar==NULL)
    {
      exit(1);
    }
    Ar[size]=create;
    size++;
    return true;
  }
  static bool isleft;
  node2 *current=root,*next,*important=NULL;
  while(true) //Όμοια με το απλό δυαδικό
  {
    if(get_balance(current)==1 || get_balance(current)==-1)
    {
      important=current;
    }
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
    if(next==NULL)//Βρέθηκε καταλληλή θέση.
    {
      if(isleft)
      {
        (*current).left=create;
      }
      else
      {
        (*current).right=create;
      }
      Ar=(node2 **)realloc(Ar,sizeof(node2 *)*(size+1));//Όμοια με απλό δυαδικό δέντρο.
      if(Ar==NULL)
      {
        exit(1);
      }
      Ar[size]=create;
      size++;
      if(important==NULL)
      {
        current=root;
        while(true)
        {
          if(strcmp(temp,(*current).s)>0)
          {
            (*current).height=find_height(current);
            current=(*current).right;
          }
          else if(strcmp(temp,(*current).s)<0)
          {
            (*current).height=find_height(current);
            current=(*current).left;
          }
          else
          {
            return true;
          }
        }
      }
      int test=find_height((*important).left)-find_height((*important).right);
      if(test==0)
      {
        current=important;
        if(strcmp(temp,(*current).s)>0)
        {
          current=(*current).right;
        }
        else
        {
          current=(*current).left;
        }
        while(true)
        {
          if(strcmp(temp,(*current).s)>0)
          {
            (*current).height=find_height(current);
            current=(*current).right;
          }
          else if(strcmp(temp,(*current).s)<0)
          {
            (*current).height=find_height(current);
            current=(*current).left;
          }
          else
          {
            return true;
          }
        }
      }
      else
      {
        int test2;
        static node2 *child;
        if(test>1)//Εκτελείται η ανάλογη περιστροφή.
        {
          child=(*important).left;
          test2=find_height((*child).left)-find_height((*child).right);
          if(test2>0)
          {
            left_left_rotation(important);
          }
          else
          {
            right_right_rotation((*important).left);
            left_left_rotation(important);
            //left_right_rotation(important);
          }
        }
        else if(test<-1)
        {
          child=(*important).right;
          test2=find_height((*child).left)-find_height((*child).right);
          if(test2>0)
          {
            left_left_rotation((*important).right);
            right_right_rotation(important);
            //right_left_rotation(important);
          }
          else if(test2<0)
          {
            right_right_rotation(important);
          }
        }
      }
      return true;
    }
    current=next;
  }
  return true;
}

void AVL::left_left_rotation(struct node2 *parent)
{
  static struct node2 *child,*parents_parent,*temp,*temp2;
  static bool isleft;
  if(parent!=root)
  {
    parents_parent=find_parent((*parent).s,isleft);//Βρές τον πατέρα του μη ισορροπημένου κόμβου.
    child=(*parent).left;
    temp=(*child).right;
    (*child).right=parent;
    (*parent).left=temp;
    if(isleft)
    {
      (*parents_parent).left=child; //Ενημέρωση του πατέρα του πρώην μη ισορροπημένου δέντρου.
    }
    else
    {
      (*parents_parent).right=child;//Όμοια.
    }
    node2 *current=root;
    while(true)
    {
      if(strcmp((*child).s,(*current).s)>0)
      {
        (*current).height=find_height(current);
        current=(*current).right;
      }
      else if(strcmp((*child).s,(*current).s)<0)
      {
        (*current).height=find_height(current);
        current=(*current).left;
      }
      else
      {
        (*current).height=find_height(current);
        break;
      }
    }
    temp2=(*current).right;
    (*temp2).height=find_height(temp2);
  }
  else
  {
    child=(*root).left;
    temp=(*child).right;
    (*child).right=root;
    (*root).left=temp;
    root=child;
    (*root).height=find_height(root);
    temp2=(*root).right;
    (*temp2).height=find_height(temp2);
  }
}

void AVL::right_right_rotation(struct node2 *parent)
{
  static struct node2 *child,*parents_parent,*temp,*temp2;
  static bool isleft;
  if(parent!=root)
  {
    child=(*parent).right;
    parents_parent=find_parent((*parent).s,isleft);//Βρές τον πατέρα του μη ισορροπημένου κόμβου.
    temp=(*child).left;  //Κατάλληλες αλλαγές για την εξισορρόπηση των υψών
    (*child).left=parent;
    (*parent).right=temp;
    if(isleft)
    {
      (*parents_parent).left=child; //Ενημέρωση του πατέρα του πρώην μη ισορροπημένου δέντρου.
    }
    else
    {
      (*parents_parent).right=child;//Όμοια.
    }
    node2 *current=root;
    while(true)
    {
      if(strcmp((*child).s,(*current).s)>0)
      {
        (*current).height=find_height(current);
        current=(*current).right;
      }
      else if(strcmp((*child).s,(*current).s)<0)
      {
        (*current).height=find_height(current);
        current=(*current).left;
      }
      else
      {
        (*current).height=find_height(current);
        break;
      }
    }
    temp2=(*current).left;
    (*temp2).height=find_height(temp2);
    }
    else //Αν ο μη ισορροπιμένος κόμβος είναι η ρίζα.
    {
      child=(*root).right;
      temp=(*child).left;
      (*child).left=root;
      (*root).right=temp;
      root=child;
      (*root).height=find_height(root);
      temp2=(*root).left;
      (*temp2).height=find_height(temp2);
    }
}

struct node2 *AVL::find_parent(char *s,bool &isleft)//Βλέπε δυαδικό δέντρο.
{
  node2 *current,*previous;
  current=root;
  while(strcmp(s,(*current).s)!=0)
  {
    previous=current;
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

bool AVL::found(char *s)//Βλέπε δυαδικό δέντρο.
{
  node2 *current=root;
  if(root==NULL)
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
  (*current).times_found++;
  return true;
}

void AVL::inorder(struct node2 *other)//Βλέπε διαδυκό δέντρο.
{
  if(other==NULL)
  {
    return;
  }
  inorder((*other).left);
  puts(((*other).s));
  inorder( (*other).right);
}

void AVL::postorder(struct node2 *other)//Βλέπε διαδυκό δέντρο.
{
  if(other==NULL)
  {
    return;
  }
  postorder((*other).left);
  postorder( (*other).right);
  puts(((*other).s));
}

void AVL::preorder(struct node2 *other)//Βλέπε διαδυκό δέντρο.
{
  if(other==NULL)
  {
    return;
  }
  puts(((*other).s));
  preorder((*other).left);
  preorder( (*other).right);
}

bool AVL::search(char *s)//Βλέπε διαδυκό δέντρο.
{
  node2 *current=root;
  if(root==NULL)
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
  return true;
}

bool AVL::delete_node(char *s)
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
  static node2 *child;
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
        static node2 *parent;
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
    static node2* temp2;
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
        static node2 *parent;
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
    static node2* temp2;
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
        static node2 *parent;
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
        static node2 *temp3,*temp4;
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
        static node2 *temp5,*temp6,*temp7;
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

struct node2 *AVL::left_most(struct node2  *other)//Βλέπε δυαδικό δέντρο.
{
  if(root==NULL)
  {
    return NULL;
  }
  struct node2 *current=other;
  while((*current).left!=NULL)
  {
    current=(*current).left;
  }
  return current;
}

struct node2 *AVL::find_current(char *s)//Βλέπε δυαδικό δέντρο.
{
  node2 *current;
  current=root;
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
  }
  return current;
}

/*void AVL::find_unbalanced(struct node2 *unbalanced)
{
  if(unbalanced==NULL)//Αν δεν υπάρχει κόμβος επέστρεψε.
  {
    return ;
  }
  find_unbalanced((*unbalanced).left);//Πήγαινε στο αριστερό παίδι.
  if((*unbalanced).balance_factor>=2 || (*unbalanced).balance_factor<=-2)//Ισορροπήσε το δέντρο με την ανάλογη περιστροφή.
  {

    static node2 *child;
    if((*unbalanced).balance_factor>1)
    {
      child=(*unbalanced).left;
      if((*child).balance_factor>0)
      {
        left_left_rotation(unbalanced);
      }
      else
      {
        left_right_rotation(unbalanced);
      }
    }
    else if((*unbalanced).balance_factor<-1)
    {
      child=(*unbalanced).right;
      if((*child).balance_factor>0)
      {
        right_left_rotation(unbalanced);
      }
      else
      {
        right_right_rotation(unbalanced);
      }
    }
  }
  find_unbalanced((*unbalanced).right);//Πήγαινε στο δεξί παιδί.
}*/

AVL::~AVL()
{
  /*for(unsigned long int i=0;i<size;i++)//Δυναμική αποδέσμευση του πίνακα.
  {
    free(Ar[i]);
  }*/
  free(Ar);
}

void AVL::get_info(char *f)
{
    ofstream ofs;
    ofs.open(f,ios::out|ios::app);
    if(!ofs.is_open())
    {
        cout<<"FILE ERROR!"<<endl;
        cout<<"EXITING!"<<endl;
        exit(1);
    }
    srand(time(NULL));
    unsigned long int *p;
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
      ofs<<(*Ar[p[i]]).s<<" is in text " <<(*Ar[p[i]]).times_found<<endl;
    }
    ofs.close();
}

inline int AVL::get_height(struct node2 *other)
{
  if(other==NULL)
  {
    return 0;
  }
  return (*other).height;
}

inline int AVL::get_balance(struct node2 *other)
{
  if(other==NULL)
  {
    return 0;
  }
  return get_height((*other).left)-get_height((*other).right);
}
