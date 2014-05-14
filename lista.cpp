
#include <iostream>
#include <list>
using namespace std;

#include "test.h"

struct obj
{
	obj * next;
	int value;	
};

class ListaObserver 
{
    public:
        virtual void itemAdded(int val) = 0;
        virtual void itemDeleted(int val) = 0;
}; 

class  Lista
{
	private:
		obj * front, * back;
	 	unsigned counter;
	
	   std::list<ListaObserver*> observers;
	public: 
	
		Lista();
		void pushFront(int val);
		int popFront();
		int popBack();
		void erase( int val);
		void showValues();
		unsigned  size() { return counter; } 
		
		obj* first() { return front; }
		obj* last()  { return back; }
		void addObserver(ListaObserver * p)
		{
		    observers.push_back(p);
		};
		void removeObserver(ListaObserver * p)
		{
		    observers.remove(p);
		};
		void notifyadd(int val)
		{
		    for (std::list<ListaObserver*>::const_iterator i = observers.begin(); i != observers.end(); ++i )
		    {
		        (*i)->itemAdded(val);
		    }
		};
		void notifyremove(int val)
		{
		    for (std::list<ListaObserver*>::const_iterator i = observers.begin(); i != observers.end(); ++i )
		    {
		        (*i)->itemDeleted(val);
		    }
		};
	
};



class ListaObserverWypisanie : public ListaObserver
{
    public:
        int event_count;
        ListaObserverWypisanie(): event_count(0) {}
    
        void itemAdded(int val)
        {
            cout << "Dodano do listy" << val << endl;
            event_count++;
        }
        void itemDeleted(int val)
        {
            cout << "Usuniêto z listy" << val << endl;
            event_count++;
        }
};

class ListaObserverEmail : public ListaObserver
{
    public:
        int event_count;
        ListaObserverEmail(): event_count(0) {}
        void itemAdded(int val)
        {
            cout << "Wysy³am mail z wartoscia" << val << endl;
            event_count++;
        }
        
        void itemDeleted(int val)
        {
            cout << "Wysy³am mail z wartoscia" << val << endl;
            event_count++;
        }
};

Lista::Lista()
{
	front = NULL;
	back = NULL;
	counter = 0;
}
	
void Lista::pushFront(int val)
{
	obj * p = new obj;
    p->next = front;
	p->value = val;
	front = p;
	if (!back) back = front;
	counter++;
	notifyadd(val);
}

    
   //pushBack
   
  
int Lista::popFront()
{
	obj * p; 
	if (front)
	{
		p = front;
        int val = front->value;	
		front = front->next;
		if(!front) back = NULL;
		counter--;
		notifyremove(val);
		return  val;	
	}
	else return p->value;
}

int Lista::popBack()
{
	obj * p;
	if (back)
	{
		p = back;
		if(p == front) 
		{
			notifyremove(front->value);
            front = back = NULL;
		}
		else
		{
			back = front;
			while (back->next != p )
			{
				back = back->next;		
			}
			back->next = NULL;
			notifyremove(p->value);
			
		} 
		counter--;
		return p->value;
	
	}
	
}


//obj * Lista::erase(obj * p)
//{
//

/// usuwa element o wartosc val z listy

/// - jak elementu ?
/// - jak sa dwa lub wiecej takie lementy ?

void Lista::erase(int val)
{
	obj * current;
	obj * prev;

	if (!front) 
    {
        return;
    }
    if (val == front->value)
    {
        popFront();
        return;
    }
    current = front;
    while(current->value != val) 
	{
	    prev = current;
        current = current->next;
        if (!current)
        {
            return;
        }
	}
	notifyremove(current->value);
    cout << current->value;
	prev->next = current->next; 
    counter--;
    if (!current->next)
    {
        back = prev;
    }      
} 


void Lista::showValues()
    {
      obj * p;
      
      if(!front) cout << "Lista jest pusta." << endl;
      else
      {
        p = front;
        while(p)
        {
          cout << p->value << " ";
          p = p->next;
        }
        cout << endl;
      }
    }


void test_zbyszka() 
{
    Lista sl;
    
    CHECK_EQUAL(sl.size(), 0 );
    
    for(int i = 1; i <= 10; i++)
    {
        sl.pushFront(i);
        CHECK_EQUAL(sl.size(), i );
    }
    CHECK_EQUAL(sl.size(), 10 );
    sl.popFront();
    CHECK_EQUAL(sl.size(), 9 );
    sl.erase(5);
    CHECK_EQUAL(sl.size(), 8 );
}

void test_na_usuwanie()
{
    Lista sl;
    CHECK_EQUAL(sl.size(), 0 );
    for(int i = 1; i <= 3; i++)
    {
        sl.pushFront(i);
    }
    
    CHECK_EQUAL(sl.first()->value, 3);
    CHECK_EQUAL(sl.first()->next->value, 2);
    CHECK_EQUAL(sl.first()->next->next->value, 1);
    
    sl.erase(1);
    
    CHECK_EQUAL(sl.first()->value, 3);
    CHECK_EQUAL(sl.first()->next->value, 2);
    //CHECK_EQUAL(sl.first()->next->next, 0);
    CHECK_EQUAL(sl.size(), 2);
    CHECK_EQUAL(sl.first()->next, sl.last());
    
    sl.erase(3);
    
    CHECK_EQUAL(sl.first()->value, 2);
    CHECK_EQUAL(sl.size(), 1);
    sl.erase(3);

}
void test_na_usuwanie_pusta()
{
    Lista sl;
    CHECK_EQUAL(sl.size(), 0 );
    sl.erase(1);
}

void test_observers()
{
    Lista sl;
    ListaObserverEmail ob1;
    ListaObserverWypisanie ob2;
    sl.addObserver(&ob1);
    sl.addObserver(&ob2);
    
    sl.pushFront(2);
    
    CHECK_EQUAL(ob1.event_count, 1);
    CHECK_EQUAL(ob2.event_count, 1);
    
    sl.pushFront(1);
    
    CHECK_EQUAL(ob1.event_count, 2);
    CHECK_EQUAL(ob2.event_count, 2);
    
    sl.removeObserver(&ob2);
    
    sl.erase(1);
    
    CHECK_EQUAL(ob1.event_count, 3);
    CHECK_EQUAL(ob2.event_count, 2);
    
}

void stare_main()
{

	Lista sl;
	
  
	cout << "(A) : "; sl.showValues();  
  
	for(int i = 1; i <= 10; i++)
	{
        sl.pushFront(i);
	}

	cout << "(B) : ";   sl.showValues();
  
	sl.popFront();

	cout << "(C) : ";   sl.showValues(); 
	
	sl.erase(5);
	
	cout << "(5) : ";   sl.showValues();
}

int main(int argc, char** argv)
{
    RUN_TEST(stare_main);
    RUN_TEST(test_zbyszka);
    RUN_TEST(test_na_usuwanie_pusta);
    RUN_TEST(test_na_usuwanie);
    RUN_TEST(test_observers);
    
    
    if( error_count != 0 ) {
        return 1;
    } else {
        return 0;
    }
    //system("PAUSE");
}
