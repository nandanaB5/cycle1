#include<stdio.h>
#include<string.h>
char result[20][20],copy[3],states[20][20];

void add_state(char a[3],int i)
{ 
  strcpy(result[i],a);
}

void display(int n)
{
  printf("Epsilon closure of %s = {",copy);
  int k=0;
  while(k<n)
  {
    printf(" %s",result[k]);
    k++;
  }
  printf(" }\n");
}
int main()
{
 int end,k=0,i,n;
 printf("Enter the no of states");
 scanf("%d",&n);

 printf("Enter the %d states:",n);
 for(int i=0;i<n;i++)
 	scanf("%s",states[i]);
 FILE *f1;
 f1=fopen("automata.txt","r");
 char state[3];
 char state1[3],input[3],state2[3];
 for(k=0;k<n;k++)
 {
 	i=0;
 	strcpy(state,states[k]);
 	strcpy(copy,state);
 	add_state(state,i++);
 	while(1)
 	{
 		end=fscanf(f1,"%s%s%s",state1,input,state2);
 		if(end==EOF)
 		   break;
 	
 	 if(strcmp(state,state1)==0)
 	  {
 	   if(strcmp(input,"e")==0)
 	   {
 	   	add_state(state2,i++);
 	   	strcpy(state,state2);
 	   }
 	  }
 	 }
 	  display(i);
 	  rewind(f1);
}
return 0;
}

