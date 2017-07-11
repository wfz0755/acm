/** 
   语法：conversion(char s1[],char s2[],long d1,long d2); 
   参数：s[]：原进制数字，用字符串表示 
        s2[]：转换结果，用字符串表示 
          d1：原进制数 
          d2：需要转换到的进制数 
   返回值：null 
   注意：高于9的位数用大写'A'～'Z'表示，2～16位进制通过验证 
 
*/  
  
  
void conversion(char s[],char s2[],long d1,long d2)  
{  
    long i,j,t,num;  
    char c;  
    num=0;  
    for (i=0;s[i]!='\0';i++)  
        {  
        if (s[i]<='9'&&s[i]>='0') t=s[i]-'0'; else t=s[i]-'A'+10;  
        num=num*d1+t;  
        }  
    i=0;  
    while(1)  
        {  
        t=num%d2;  
        if (t<=9) s2[i]=t+'0'; else s2[i]=t+'A'-10;  
        num/=d2;  
        if (num==0) break;  
        i++;  
        }  
    for (j=0;j<i/2;j++)  
        {c=s2[j];s2[j]=s[i-j];s2[i-j]=c;}  
    s2[i+1]='\0';  
}  
