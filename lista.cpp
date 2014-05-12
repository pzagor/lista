
#include <iostream>
using namespace std;


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
		obj* pushFront (obj * p);
		obj* popFront();
		obj* popBack();
		obj* erase( obj * p);
		void showValues();
	
};

Lista::Lista()
{
	front = NULL;
	back = NULL;
	counter = 0;
}
	
obj * Lista::pushFront (obj * p)
{
	p->next = front;
	front = p;
	if (!back) back = front;
	counter++;
	return front;
	
}
    
obj * Lista::popFront()
{
	obj * p;
	if (front)
	{
		p = front;	
		front = front->next;
		if(!front) back = NULL;
		counter--;
		return p; 	
	}
	else return NULL;
}

obj * Lista::popBack()
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
		return p;
	}
	else  return NULL;
	

}


    obj * Lista::erase(obj * p)
    {
    	obj * p1;

    	if(p == front) return popFront();
    	else
    	{
        p1 = front;
        while(p1->next != p) 
		{
			p1 = p1->next;
		}
        p1->next = p->next;
        
        counter--;
        return p;
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
    
    
  main()
{
	Lista sl;
	obj * p;
	int   i;
  
	cout << "(A) : "; sl.showValues();  
  
	for(i = 1; i <= 1000; i++)
	{
	    p = new obj;
	    p->value = i;
	    sl.pushFront(p);
	}

	cout << "(B) : ";   sl.showValues();
  
	sl.popFront();
  
	cout << "(C) : ";   sl.showValues(); 
}

