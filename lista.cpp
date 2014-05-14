
#include <iostream>
using namespace std;

#include "test.h"

struct obj
{
	obj * next;
	int value;	
};

class  Lista
{
	private:
		obj * front, * back;
	 	unsigned counter;
	
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
}

    
   //pushBack
    
    
int Lista::popFront()
{
	obj * p; 
	if (front)
	{
		p = front;	
		front = front->next;
		if(!front) back = NULL;
		counter--;
		 	
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
		} 
		counter--;
	
	}
	//else ; //return NULL;
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
    
    
    if( error_count != 0 ) {
        return 1;
    } else {
        return 0;
    }
    //system("PAUSE");
}
