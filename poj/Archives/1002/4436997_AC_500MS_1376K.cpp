#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000
typedef struct {char elem[8];int time;} item;
item ph[MAX];
char hash(char ch)
{
 if(ch<'P') return (char)((ch-'A')/3+2+'0');
 else if(ch>'S'&&ch<'Z') return (char)((ch-'T')/3+8+'0');
 else return (char)(7+'0');  
}

void trans(char * str,int ii)
{
 int i = 0,j = 0;
 while(str[i]!='\0')
 {
  if(str[i]=='-') {i++; continue;}
  else if(str[i]>='A'&&str[i<'Z']) ph[ii].elem[j++]=hash(str[i++]);
  else ph[ii].elem[j++]=str[i++];
 }
 ph[ii].elem[j]='\0';
 ph[ii].time = 1;
}
int cmp(const void * a,const void * b)
{
 return strcmp(((item *)a)->elem,((item *)b)->elem);
}
int main()
{
 int i=0,j=0,n;
 int fg=1;
 char s[100];
 scanf("%d",&n);
 getchar();
 while(i<n)
 {
  scanf("%s",s);
  trans(s,i);
  i++;
 }
 qsort(ph,n,sizeof(item),cmp);
 i=0,j=0;
 while(i++<n)
 {
  if(strcmp(ph[i].elem,ph[j].elem)!=0)
  {
   if(ph[j].time >1) 
   {
    printf("%c%c%c-%c%c%c%c %d\n",ph[j].elem[0],ph[j].elem[1],ph[j].elem[2],
     ph[j].elem[3],ph[j].elem[4],ph[j].elem[5],ph[j].elem[6],ph[j].time);
    fg=0;
   }
   j=i;
  }
  else ph[j].time+=ph[i].time;
 }

 if(fg) printf("No duplicates.\n");
 return 0;
}