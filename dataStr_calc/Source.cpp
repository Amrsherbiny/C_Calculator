#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float eval[100];
char stack[100];
int top=-1;
int topEv = -1;
float pushEv( float x)
{
	if ( topEv >=100)
	{
		return 0;
	}
	eval[++topEv]=x;
	return 1;
}
int push( char x)
{
	if ( top >=100)
	{
		return 0;
	}
	stack[++top]=x;
	return 1;
}
float popEv()
{ float x;
 x=eval[topEv];
 topEv--;
	return x;
}
char pop()
{ char x;
 x=stack[top];
 top--;
	return x;
}

int check(char x)
{
   if(x == '(')
 return(1);
   if(x == '+' || x == '-')
 return(2);
   if(x == '*' || x == '/')
 return(3);
   if (x== '^')
   return(4);
   else
	   return 0;
}
float evaluate(char *postfix)
{
	float x,y,z,res;
	for(int i = 0; i <strlen(postfix); i++)
	{  
		if (isdigit(postfix[i]))
			pushEv(postfix[i]-'0');
		else
		{
		x= check(postfix[i]);
		if(x == 2)
		{
			if (postfix[i]=='+')
				{
					y = popEv();
					z= popEv();
					res = y+z;
					pushEv(res);
			}
			if(postfix[i] == '-')
			{
				y = popEv();
					z= popEv();
					res = z-y;
					pushEv(res);
			}
		}
		else
			if(x == 3)
			{
				if (postfix[i]  == '*')
				{
					y = popEv();
					z= popEv();
					res = y*z;
					pushEv(res);
			}
			if(postfix[i]  == '/')
			{
				y = popEv();
				z= popEv();
				if (y!=0)
				{
				res = z/y;
				pushEv(res);
				}
				else printf("Error division by zero");

			}
			}
			else
				if(x==4)
			{
				y = popEv();
					z= popEv();
					res = pow(z,y)/*z^y*/;
					pushEv(res);
				
			}
		}
	}
res = popEv();
return res;
}
int main ()
{ 
	char infix[100]; char postfix[100];
	int i=0,j=0;
	gets(infix);
	while (infix[i] != NULL)
	{
		
		if (isdigit(infix[i]))
		{
			postfix[j]=infix[i];
			j++;
		}
		else if(infix[i] == '(')
		{
			push(infix[i]);
		}
        else if(infix[i] == ')')
        {
			char x = pop();
            while( x != '(')
				{
					postfix[j]=x;
					j++;
					x=pop();
			}
        }
        else
        {
			if ( top != -1)
			{
				if(check(stack[top]) < check(infix[i]) )
					push(infix[i]);
				else
				{
					int isPushed = 0;
				while(check(stack[top]) > check(infix[i]))
              {  
				  if (stack[top] == NULL)
				  {
					  push(infix[i]);
					  isPushed = 1;
					 break;	  
				  }
				  else
				  for (int a=top ; a<=top; a--)
					 {  if (a == -1 || stack[top] == '(')
						  break;
					 else
						 postfix[j++]=pop();
				  
					 
				  
				  }
				 /* if(infix[i+1]==NULL)
					  break;*/
			}
				if(isPushed == 0 )
					push(infix[i]);
				}
			}else
			push(infix[i]);
        }
		
			
	i++;
	}
				while (stack[top] != NULL && infix[i] == NULL)
				{
					postfix[j]=pop();
					j++;
					if (top == -1)
						break;
				}
			
	postfix[j] = '\0';
				puts(postfix);
				float res = evaluate(postfix);
					printf("%f",res);
getch();	

}