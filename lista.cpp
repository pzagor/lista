#include "gmock/gmock.h" 
#include <iostream>
#include <list>
using namespace std;

//#include "test.h"

struct obj
{
	obj * next;
	int value;	
	static int objcounter;
	obj();
	~obj();
	
};
    int obj::objcounter = 0;
    obj::obj()
    {
        objcounter++;
    }	
    
    obj::~obj()
    {
        objcounter--;
    }


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

        ~Lista()
        {
            while (first())
            {
                popBack();
            }
        }

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
		delete p;
		if(!front) back = NULL;
		counter--;
		notifyremove(val);
		
		return  val;	
	}
	return 0;
}

int Lista::popBack()   // obtestowac
{
	
	if (back)
	{
        obj * p = back;
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
        int pvalue = p->value;
        delete p;
        return pvalue;
        
	
	}
    return 0;
}


/// - jak elementu ?
/// - jak sa dwa lub wiecej takie lementy ?

void Lista::erase(int val)
{
	obj * current;
	obj * prev = 0;

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
    delete current;
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


TEST(test_zbyszka, test_zbyszka)
{
    ASSERT_EQ(obj::objcounter, 0);
    Lista sl;
    
    ASSERT_EQ(sl.size(), 0 );
    
    for(int i = 1; i <= 10; i++)
    {
        sl.pushFront(i);
        ASSERT_EQ(sl.size(), i );
    }
    ASSERT_EQ(sl.size(), 10 );
    sl.popFront();
    ASSERT_EQ(sl.size(), 9 );
    sl.erase(5);
    ASSERT_EQ(sl.size(), 8 );
}

TEST(test_na_usuwanie, test_na_usuwanie)
{
    ASSERT_EQ(obj::objcounter, 0);
    Lista sl;
    ASSERT_EQ(sl.size(), 0 );
    for(int i = 1; i <= 3; i++)
    {
        sl.pushFront(i);
    }
    
    ASSERT_EQ(sl.first()->value, 3);
    ASSERT_EQ(sl.first()->next->value, 2);
    ASSERT_EQ(sl.first()->next->next->value, 1);
    
    sl.erase(1);
    
    ASSERT_EQ(sl.first()->value, 3);
    ASSERT_EQ(sl.first()->next->value, 2);
    //ASSERT_EQ(sl.first()->next->next, 0);
    ASSERT_EQ(sl.size(), 2);
    ASSERT_EQ(sl.first()->next, sl.last());
    
    sl.erase(3);
    
    ASSERT_EQ(sl.first()->value, 2);
    ASSERT_EQ(sl.size(), 1);
    sl.erase(3);

}
TEST(test_na_usuwanie, test_na_usuwanie_pusta)
{
    ASSERT_EQ(obj::objcounter, 0);
    Lista sl;
    ASSERT_EQ(sl.size(), 0 );
    sl.erase(1);
}

TEST(test_observ, test_observ)
{
    ASSERT_EQ(obj::objcounter, 0);
    Lista sl;
    ListaObserverEmail ob1;
    ListaObserverWypisanie ob2;
    sl.addObserver(&ob1);
    sl.addObserver(&ob2);
    
    sl.pushFront(2);
    
    ASSERT_EQ(ob1.event_count, 1);
    ASSERT_EQ(ob2.event_count, 1);
    
    sl.pushFront(1);
    
    ASSERT_EQ(ob1.event_count, 2);
    ASSERT_EQ(ob2.event_count, 2);
    
    sl.removeObserver(&ob2);
    
    sl.erase(1);
    
    ASSERT_EQ(ob1.event_count, 3);
    ASSERT_EQ(ob2.event_count, 2);
    
}
TEST(test_memory_leak, test_memory_leak)
{
    ASSERT_EQ(obj::objcounter, 0);

    Lista sl;
    
    ASSERT_EQ(obj::objcounter, 0);
    
    ASSERT_EQ(sl.size(), 0 );
    for(int i = 1; i <= 5; i++)
    {
        sl.pushFront(i);
    }
    
    ASSERT_EQ(obj::objcounter, 5);
   
    sl.popFront();

    ASSERT_EQ(obj::objcounter, 4);
   
    sl.popBack();
    
    ASSERT_EQ(obj::objcounter, 3);

    sl.erase(2);
    
    ASSERT_EQ(obj::objcounter, 2);
 
    sl.erase(5);
    
    ASSERT_EQ(obj::objcounter, 2);
    
}



TEST (stare_main, stare_main)
{
    ASSERT_EQ(obj::objcounter, 0);
    
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
    //ASSERT_EQ(obj::objcounter, 0);
    //RUN_TEST(stare_main);
    //ASSERT_EQ(obj::objcounter, 0);
    //RUN_TEST(test_zbyszka);
    //ASSERT_EQ(obj::objcounter, 0);
    //RUN_TEST(test_na_usuwanie_pusta);
    //ASSERT_EQ(obj::objcounter, 0);
    //ASSERT_EQ(obj::objcounter, 0);
    //RUN_TEST(test_na_usuwanie);
    //ASSERT_EQ(obj::objcounter, 0);
    //RUN_TEST(test_observers);
    //ASSERT_EQ(obj::objcounter, 0);
    //RUN_TEST(test_memory_leak);
    //ASSERT_EQ(obj::objcounter, 0);
    //cout << "Wykryto " << error_count << " bledow" << endl;
    
  

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

    /*if( error_count != 0 ) {

        return 1;
    } else {
        return 0;
    }*/
    system("PAUSE");
}


// TODO     // obtestowac

/// pop back czy wszedl w kazda galaz

