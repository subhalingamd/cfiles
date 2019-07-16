char* ENC(char* str)
{  int len=0;
   for (;*str!='\0';str++)
    {len++;
    if (*str<30)
    *str+=2;
    else if (*str<56)
    *str+=3;
    else if (*str<89)
    *str+=5;
    else if (*str<100)
    *str +=6;
    else if (*str<120)
    *str +=8;
    else
    *str +=9;}
   str-=len;
  return str;
}
