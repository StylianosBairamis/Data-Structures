#include <iostream>
#include "Array.h"
#include "Sorted_array.h"
#include "Bnary.h"
#include "Hashing_table.h"
#include "AVL.h"
using namespace std;
#include <cstdlib>
#include <fstream>
#include <ctime>

int main(int argc,char *argv[]) //Παράμετροι για την διαχείρηση αρχείων μέσω του cmd.
{
  if(argc!=3)// Αν δεν είναι 3 οι παράμετροι έγινε κάποιο λάθος.
  {
    cout<<"TOO LITTLE ARGUMENTS!"<<endl;
    cout<<"EXITING"<<endl;
    exit(1);
  }
  time_t start,end;
  Array a; //Αταξινόμητος πίνακας.
  time(&start);//Ξεκινάει η χρονομέτρηση.
  ifstream ifs;
  char *p;
  p=(char *)malloc(sizeof(char)*47);//Μήκος μεγαλύτερης αγγλικής λέξης
  if(p==NULL)
  {
    exit(1);
  }
  ifs.open(argv[1],ios::in);//άνοιγμα αρχείου.
  if(ifs.is_open())
  {
    cout<<"FILE OPENED NORMALLY!"<<endl;
    while(ifs>>p)
    {
      a.insert(p);
    }
  }
  else
  {
    cout<<"FILE ERROR!"<<endl;//Λάθος με το άνοιγμα του αρχείου.
    cout<<"EXITING!"<<endl;
    exit(1);
  }
  ifs.close();
  a.get_info(argv[2]);//Τα δεδομένα μεταφέρονται στο αρχείο με όνομα argv[2]*/
  time(&end);//Τελειώνει η χρονομέτρηση.
  double time_taken= double(end - start);//Διαφορά του αρχικού χρόνου με τον τελικό.
  cout<<" "<<endl;
  cout<<"Time taken by program is : "<<fixed<<time_taken;
  cout<<" sec"<<endl;
  cout<<"PRESS ANY KEY TO CONTINUE!"<<endl;
  getchar();
  Sorted_array b;//Ταξινομημένος πίνακας.
  time(&start);//Όμοια με παραπάνω.
  ifs.open(argv[1],ios::in);
  if(ifs.is_open())
  {
    cout<<"FILE OPENED NORMALLY!"<<endl;
    while(ifs>>p)
    {
      b.insert(p);
    }
  }
  else
  {
    cout<<"FILE ERROR!"<<endl;
    cout<<"EXITING!"<<endl;
    exit(1);
  }
  ifs.close();
  b.merge_sort(0,b.getCurrent()-1);//Ταξινόμηση του πίνακα.
  b.get_info(argv[2]);
  time(&end);
  time_taken = double(end - start);
  cout<<" "<<endl;
  cout<<"Time taken by program is : "<<fixed<<time_taken;
  cout<<" sec"<<endl;
  cout<<"PRESS ANY KEY TO CONTINUE!"<<endl;
  getchar();
  Bnary c;//Απλό δυαδικό δέντρο.
  time(&start);
  ifs.open(argv[1],ios::in);
  if(ifs.is_open())
  {
    cout<<"FILE OPENED NORMALLY!"<<endl;
    while(ifs>>p)
    {
      c.insert_node(p);
    }
  }
  else
  {
    cout<<"FILE ERROR!"<<endl;
    cout<<"EXITING!"<<endl;
    exit(1);
  }
  ifs.close();
  c.get_info(argv[2]);
  time(&end);
  time_taken = double(end - start);
  cout<<" "<<endl;
  cout<<"Time taken by program is : "<<fixed<<time_taken;
  cout<<" sec"<<endl;
  cout<<"PRESS ANY KEY TO CONTINUE"<<endl;
  getchar();
  AVL d;//Δέντρο AVL
  time(&start);
  ifs.open(argv[1],ios::in);
  if(ifs.is_open())
  {
    cout<<"FILE OPENED NORMALLY!"<<endl;
    while(ifs>>p)
    {
      d.insert_node(p);
    }
  }
  else
  {
    cout<<"FILE ERROR!"<<endl;
    cout<<"EXITING!"<<endl;
    exit(1);
  }
  d.get_info(argv[2]);
  time(&end);
  time_taken = double(end - start);
  cout<<" "<<endl;
  cout<<"Time taken by program is : "<<fixed<<time_taken;
  cout<<" sec"<<endl;
  ifs.close();
  cout<<"PRESS ANY KEY TO CONTINUE!"<<endl;
  getchar();
  Hashing_table e;//Πίνακας κατακερματισμόυ.
  time(&start);
  ifs.open(argv[1],ios::in);
  if(ifs.is_open())
  {
    cout<<"FILE OPENED NORMALLY!"<<endl;
    while(ifs>>p)
    {
      e.insert(p);
    }
  }
  else
  {
    cout<<"FILE ERROR!"<<endl;
    cout<<"EXITING!"<<endl;
    exit(1);
  }
  e.get_info(argv[2]);
  time(&end);
  time_taken = double(end - start);
  cout<<" "<<endl;
  cout<<"Time taken by program is : "<<fixed<<time_taken;
  cout<<" sec"<<endl;
  ifs.close();
  cout<<"PRESS ANY KEY TO CONTINUE!"<<endl;
  getchar();
  return 0;
}
