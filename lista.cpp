struct obj{
	obj * next;
	int value;	
};

class  Lista
{
	 
	private:
	 obj * front, *back;
	 unsigned counter;
	
	public: 
	Lista();
	pushFront (obj * p)
	popFront();
	popBack();
	popOne( obj * p);
	
};

Lista::Lista()
{
	front = NULL;
	back = NULL;
	counter = 0;
}
	
obj * pushFront (obj * p)
{
p->next = front;
front = p;
if (!back) back = front;
counter++;
return front;
	
}
    
obj * popFront()
{
	obj * p;
	if (front)
	{
		p= front;	
		front = front->next;
		if(!front) back = NULL;
		counter--;
		return p; 	
	}

}


