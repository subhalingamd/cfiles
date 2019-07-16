#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<process.h>
#include<bios.h>
#include<dos.h>
#include<iomanip.h>
#include<time.h>

#include"NAVIGATE.hpp"
#include"PASSENC.hpp"


class MEMBER{
  char name[32],userid[32],password[32];
  double xp;
  int lvl;
  unsigned int tokens;

 public:
  MEMBER()
	{xp=0;	lvl=-1;	tokens=0;}
  MEMBER(char id[],char user_name[],char pass[]){
    strcpy(name,user_name);
    strcpy(userid,id);
    strcpy(password,pass);
    xp=0; lvl=-1; tokens=0;}
  MEMBER (MEMBER &m){
    strcpy(name,m.name);
    strcpy(userid,m.userid);
    strcpy(password,m.password);
    xp=m.xp; lvl=m.lvl; tokens=m.tokens;}

  char* ret_userid()	{return userid;}
  char* ret_name()	{return name;}
  char* ret_password()	{return password;}
  double ret_xp()	{return xp;}
  int ret_lvl()		{return lvl;}
  int ret_tokens() 	{return tokens;}

  void upd_tokens(int i){tokens+=i;}
  void upd_lvl(int i) 	{lvl=i;}
  void upd_xp(int i) 	{xp+=i;}

  int val_pass(char *inp_pass) {
    if(!strcmp(inp_pass,password))
      return 0;
    else return 1; }

  int CHANGE_PASS_val(char old[],char new1[],char new2[])  {
    if (strcmp(old,password))
      return 1;
    if (strcmp(new1,new2))
      return 2;
    strcpy(password,new1);
      return 0;  }

  void pass_enc()	{strcpy(password,ENC(password)); }

};

void main()	{
clrscr();

void GETPASS(char[]),LOAD(long);
void REGISTER(int),CHANGE_PASS(MEMBER); MEMBER LOGIN();
void ADMIN(),init();
MEMBER LOADER (MEMBER);

init();

int i;

clrscr();
int opt=1;

 while (opt)
 {
 cout<<"Welcome GUEST,\n";
 cout<<"\nJoin the group of Detectives of Itoville to solve a series of murder cases. ";
 cout<<"\n\nNOT YET A MEMBER? SIGN UP NOW!";
 cout<<"\n > Username: ";
 cout<<"\n > Name: ";
 cout<<"\n > Password: \n\n> Login\n\n  <Press Esc to EXIT>";
 ret:
 gotoxy(1,10);
 opt=bioskey(0);
 if (opt==7181)
 {
	MEMBER user=LOGIN(); i=1;
	if (strcmp(user.ret_userid(),"0"))
	{
	if (!strcmp(user.ret_userid(),"admin"))
	ADMIN();

	else{

	do {  i=1;
	clrscr();
	if (user.ret_lvl()>=0)
	{
	  cout<<user.ret_name();
	  gotoxy(40,1);
	  cout<<"XP: "<<user.ret_xp();
	  gotoxy(55,1);
	  cout<<"TOKENS: "<<user.ret_tokens();
	  gotoxy(70,1);
	  cout<<"LEVEL: "<<user.ret_lvl()<<endl;
	}
	else
	{
	  cout<<user.ret_name();
	  gotoxy(40,1);
	  cout<<"XP: "<<user.ret_xp();
	  gotoxy(55,1);
	  cout<<"TOKENS: "<<user.ret_tokens()<<endl;
	}
	cout<<"\nCHOOSE:\n> Play\n> Change Password\n   Logout";
	switch (UPDOWN(4,3)){
		case 1: clrscr(); user=LOADER(user); break;
		case 2: CHANGE_PASS(user); break;
		case 3: cout<<"\n\n   Are you sure you want to logout?\n     Press Enter to continue. Press Esc to cancel.";
			out:{
			int key=bioskey(0);
			if (key==7181)
			{
			i=0;
			clrscr();
			cout<<"\n Logging you out...";
			delay(1500);
			}
			else if (key==283)
			{;}
			else
			goto out;}

	}
	}while (i);
	}}
	clrscr();

 }
 else if ((char(opt)>='0'&&char(opt)<='9')||(char(opt)>='A'&&char(opt)<='Z')||(char(opt)>='a'&&char(opt)<='z'))
 {REGISTER(opt);}
 else if (opt==283)
 exit(0);
 else
 goto ret;

 }
}

   void  GETPASS(char inp[]) {
     char pass[32];
     for (int i=0;i<32;i++)
     {
	int key=0;
	key=bioskey(0);
	if (key==7181) {
	     if (i==0) {cout<<" This field cannot be empty."; i--; delay(1000); for (int j=0;j<28;j++) cout<<"\b \b"; continue;} else {pass[i]='\0';break;}}
	     if (key==3592) {if (i==0) {i--;} else {cout<<"\b \b";  i-=2;} continue;}
	     if (key==19200||key==19712||key==18432||key==20480){ i--; continue;}
	     pass[i]=char(key);
	     putch('*');
	   }

	   strcpy(inp,ENC(pass));
	   }

   void LOAD(long s){
	   cout<<"\n\n  LOADING...";
	   delay(s*1000);
	   cout<<"\b\b\b\b\b\b\b\b\b\b";
	   }

   void  CHANGE_PASS(MEMBER user){
	   clrscr();
	   char oldpass[32],newpass1[32],newpass2[32];
	   MEMBER mem;
	   fstream f ("USERS.DAT",ios::in|ios::out|ios::binary);
	   while (f.read((char*)&mem,sizeof(mem)))
	   if (!strcmp(user.ret_userid(),mem.ret_userid()))
	   break;
	   cout<<"\nChanging password.\nEnter current password:\t";
	   GETPASS(oldpass);
	   cout<<"\nEnter new password:\t";
	   GETPASS(newpass1);
	   cout<<"\nConfirm your password:\t";
	   GETPASS(newpass2);
	   switch(mem.CHANGE_PASS_val(oldpass,newpass1,newpass2)){
	   case 1: cout<<"\n  Current password you entered doesnot match"; break;
	   case 2:cout<<"\n  The new passwords you entered does not match!"; break;
	   case 0:      long p=f.tellg()-sizeof(mem);
			f.seekg(p);
			f.write((char*)&mem,sizeof(mem));
			cout<<"\n  Successfully changed!";}
			f.close();
			LOAD(2);
			clrscr();
		       }


  void REGISTER(int opt) {
	   int Val_UserID(char[]);
	   char id[32],user_name[32],pass[32];
	   do {
	   gotoxy(15,6);
   id[0]=char(opt);
   cout<<id[0];
   for (int i=1;i<32;i++)
   {
   int temp=bioskey(0);
   if (temp==3592)
   { if (i==1)
      {cout<<"\b \b";clrscr(); return;  }
    else
      {cout<<"\b \b"; i-=2;      }
   }
   else if (temp==283||temp==19200||temp==19712||temp==18432||temp==20480){ i--; continue;}
   else if (temp==7181) break;
   else
   {
   id[i]=char(temp);
   cout<<id[i];
   }
   }
   id[i]='\0';
   }while(Val_UserID(id));
   gotoxy(15,7);
   gets(user_name);
   gotoxy(15,8);
   GETPASS(pass);
   cout<<"\n\n       \n By signing up, you agree that you are more than 12 years old.\n  If not, press Esc. Press Enter to proceed.";
   int key,i=1;
       while (i)
       {
	  key=bioskey(0);
	  if (key==7181) break;
	  if (key==283) {clrscr(); return;}
       }
       MEMBER mem(id,user_name,pass);
       fstream f("USERS.DAT",ios::app|ios::binary);
       f.write((char*)&mem,sizeof(mem));
       LOAD(2);
       cout<<"Successfully Registered";
       delay(1000);
       clrscr();
    }

   int Val_UserID(char id[]){
      if (id[0]=='\0')
      { cout<<"  User name field cannot be empty.";delay(1000);for (int i=0;i<34;i++) cout<<"\b \b";clrscr(); return 1;}
	   MEMBER mem_val;
	   fstream f_reg("USERS.DAT",ios::in|ios::binary);
	   while (f_reg.read((char*)&mem_val,sizeof(mem_val)))
	   if (!strcmpi(mem_val.ret_userid(),id)) {
	   cout<<"  Name already exisits! Please choose another name";delay(1000);for (int i=0;i<strlen(id)+50;i++) cout<<"\b \b";return 1;}
	   return 0; }



  MEMBER LOGIN() {
  MEMBER mem,dummy("0","0","0");
	   char id[32],pass[32];
	   fstream f("USERS.DAT",ios::in|ios::in|ios::binary);
	   f.seekp(0,ios::beg);
	   start:{
	   clrscr();
  int opt=1;
 while (opt)
 {
 cout<<"Welcome GUEST,\n";
 cout<<"\nJoin the group of Detectives of Itoville to solve a series of murder cases. ";
 cout<<"\n\nLOGIN:";
 cout<<"\n > Username: ";
 cout<<"\n > Password: \n\n\n> Sign Up\n\n  <Press Esc to EXIT>";
 ret:
 gotoxy(1,10);
 opt=bioskey(0);
 if (opt==7181)
 {
   return dummy;
 }
 else if ((char(opt)>='0'&&char(opt)<='9')||(char(opt)>='A'&&char(opt)<='Z')||(char(opt)>='a'&&char(opt)<='z'))
{
   gotoxy(15,6);
   id[0]=char(opt);
   cout<<id[0];
   for (int i=1;i<32;i++)
   {
   int temp=bioskey(0);
   if (temp==3592)
   { if (i==1)
      {cout<<"\b \b";clrscr(); goto start;  }
    else
      {cout<<"\b \b"; i-=2;      }
   }
   else if (temp==283||temp==19200||temp==19712||temp==18432||temp==20480){ i--; continue;}
   else if (temp==7181) break;
   else
   {
   id[i]=char(temp);
   cout<<id[i];
   }
   }
   id[i]='\0';

     if (!(strcmp(id,"0")))  {
	   cout<<"\n  You don't have the permission to access this account! Try Again!";
	   delay(1750);
	   goto start;
	   }

     int ctr=1;
	   while (f.read((char*)&mem,sizeof(mem)))
	   if (!strcmpi(mem.ret_userid(),id)){ctr = 0; break;}



  gotoxy(15,7);
  GETPASS(pass);

   if (mem.val_pass(pass)||ctr)
	   {cout<<"\n The details you entered doesnot match with any of our records.Please try again!"; delay (2000);goto start; }
	   LOAD(2);
	   if (!(strcmp(mem.ret_userid(),"admin")))
	   return mem;
	   clrscr();
	   return mem;


 }
 else if (opt==283)
 exit(0);
 else
 goto ret;

 } }  }


  void ADMIN(){
	int i, opt;
	do {
	i=1;
	clrscr();
	cout<<"ADMIN PANEL\n\n";
	cout<<"  Change Password\n  Logout\n";
	MEMBER mem;        int n=0;
	fstream f("USERS.DAT",ios::in|ios::binary);
	long p=2*sizeof(mem);
	f.seekg(p);
	while (f.read((char*)&mem,sizeof(mem))) { n++;
	   cout<<"> "<<mem.ret_userid();
	  gotoxy(15,n+4);
	  cout<<mem.ret_name();
	  gotoxy(47,n+4);
	  cout<<mem.ret_tokens()<<'\n';

	  ;}

	if (n==0)
	cout<<setw(30)<<"<NO MEMBERS>";

	opt=UPDOWN(3,n+2);

	do {  i=1;
	if (opt==1)
	{
	   clrscr();
	   char newpass1[32],newpass2[32];
	   MEMBER mem;
	   fstream f ("USERS.DAT",ios::in|ios::out|ios::binary);
	   f.seekp(0);
	   long q=sizeof(mem);
	   f.seekp(q);
	   f.read((char*)&mem,sizeof(mem));
	   cout<<"\nEnter new password:\t";
	   GETPASS(newpass1);
	   cout<<"\nConfirm your password:\t";
	   GETPASS(newpass2);
	   switch(mem.CHANGE_PASS_val(mem.ret_password(),newpass1,newpass2)){
	   //case 1: cout<<"\n  Current password you entered doesnot match"; break;
	   case 2:cout<<"\n  The new passwords you entered does not match!"; break;
	   case 0:      long p=f.tellg()-sizeof(mem);
			 f.seekg(p);
			f.write((char*)&mem,sizeof(mem));
			cout<<"\n  Successfully changed!";    }
			f.close();
			LOAD(1);
			clrscr();
	   break;

	}

	if (opt==2) break;
	if (opt>=3)
	{
	clrscr();
	MEMBER user;
	fstream f1("USERS.DAT",ios::in|ios::out|ios::binary);
	long x=(opt-1)*sizeof(user);
	f1.seekg(x);
	f1.read((char*)&user,sizeof(user));
	cout<<"\n\nUSER ID: "<<user.ret_userid();
	cout<<"\nNAME: "<<user.ret_name();
	cout<<"\n\nXP: "<<user.ret_xp();
	cout<<"\nLEVEL: "<<user.ret_lvl();
	cout<<"\nTOKENS: "<<user.ret_tokens();
	cout<<"\n\n\nOPTION:\n 1.ADD/REMOVE tokens\n 2.REMOVE account\n 3.BACK";
	switch (UPDOWN(12,3)){
		case 1: clrscr();
			cout<<"\nUSER ID: "<<user.ret_userid()<<endl;
			cout<<"\n  Current number of tokens:\t"<<user.ret_tokens()<<endl;
			int a=0;
			cout<<"\n  Add  0    tokens\b\b\b\b\b\b\b\b\b\b\b";
			cin>>a;
			cout<<"\n\n Adding "<<a<<" tokens for "<<user.ret_userid()<<"\n  Press Enter to continue. Press Esc to cancel.";
			add:{
			int key=bioskey(0);
			if (key==7181)
			{
			user.upd_tokens(a);
			f1.seekp(0);
			long y=(opt-1)*sizeof(user);
			f1.seekp(y);
			f1.write((char*)&user,sizeof(user));
			cout<<"\n\n   Succesfully Added!";
			delay(1000);
			clrscr();
			}
		       else if (key==283)
		       break;
		       else
		       goto add;
		       }
		       break;
		case 2: clrscr();
			cout<<"\n Are you sure you want to remove "<<user.ret_userid()<<"\n   Press Enter to continue. Press Esc to cancel.";
			remove:{
			int key=bioskey(0);
			if (key==7181)
			{

			ifstream r1("USERS.dat",ios::binary);
			ofstream r2("temp.dat",ios::binary);
			MEMBER temp;
			while (r1.read((char*)&temp,sizeof(temp)))
			{
			  if (strcmp(temp.ret_userid(),user.ret_userid()))
			  r2.write((char*)&temp,sizeof(temp));
			}
			r1.close();
			r2.close();
			remove("USERS.dat");
			rename("temp.dat","USERS.dat");
			cout<<"\n\n   Succesfully Removed!";
			delay(1000);
			clrscr();
			}
		       else if (key==283)
		       break;
		       else
		       goto add;
		       }
		case 3: i=0;}
	f1.close();
	}} while (i);
	f.close();
	} while(opt!=2);}



MEMBER LOADER(MEMBER user) {
 void LVL1(MEMBER&), LVL2(MEMBER&);
 void GETCH();
int opt;
do {
clrscr();
opt=2;
if (user.ret_lvl()>=0)
{
	  cout<<user.ret_name();
	  gotoxy(40,1);
	  cout<<"XP: "<<user.ret_xp();
	  gotoxy(55,1);
	  cout<<"TOKENS: "<<user.ret_tokens();
	  gotoxy(70,1);
	  cout<<"LEVEL: "<<user.ret_lvl()<<endl;
 cout<<"\n  Save & Exit";
 switch(user.ret_lvl()) {
 case 0: cout<<"\n> Tutorial\n> Case 1: Who killed Mr. Enzo Mcswiggan"; break;
 case 1: cout<<"\n> Tutorial\n> Case 1: Who killed Mr. Enzo Mcswiggan\n> Case 2: Mystery behind Queen Rosalie Exeter Atkins\' crown"; break;
 case 2: cout<<"\n> Tutorial\n> Case 1: Who killed Mr. Enzo Mcswiggan\n> Case 2: Mystery behind Queen Rosalie Exeter Atkins\' crown\n   Case 3: (Coming Soon)"; break;
 default: cout<<"\n> Tutorial\n> Case 1: Who killed Mr. Enzo Mcswiggan\n> Case 2: Mystery behind Queen Rosalie Exeter Atkins\' crown\n   Case 3: (Coming Soon)"; break;
 }

 opt=UPDOWN(3,user.ret_lvl()+3);

}

switch(opt-2)
{
case -1: break;
case 0:
 clrscr();
 char str[207];
 ifstream f0("lvl0.txt");
 if (!f0)
  {
   cerr<<"Required file not detected!";
   GETCH();
   exit(1);
  }
 do {
 f0.getline(str,207);
 for (int i=0;i<strlen(str);i++)
 {
 if (str[i]=='<'&&str[i+1]=='n'&&str[i+5]=='>')
 { cout<<user.ret_name()<<',';  i+=6;}
 cout<<str[i];
 delay(15); }
 delay(500);
 if (str[1]=='<'&&str[strlen(str)-1]=='>')
 {
  getch();
  clrscr();
 }
 cout<<"\n";
 }while(!f0.eof());
 if (user.ret_lvl()<0)
 user.upd_lvl(0);
 clrscr();
 cout<<endl;
 LOAD(1);
 break;
 case 1:
	   LVL1(user);
	   break;
 case 2:   LVL2(user);
	   break;
 case 3: cout<<"\n\n\n  This level is coming soon! You will not be disappointed!\n\n"; delay(1500); break;
 case 4: ;
}
}while (opt!=1);
	   fstream f ("USERS.DAT",ios::in|ios::out|ios::binary);
	   MEMBER mem;
	   while (f.read((char*)&mem,sizeof(mem)))
	   if (!strcmp(user.ret_userid(),mem.ret_userid()))
	   break;
	   long p=f.tellg()-sizeof(user);
			f.seekg(p);
			f.write((char*)&user,sizeof(user));
			f.close();

	   clrscr();
	   cout<<"\n  Just a moment. Saving your progress..."<<endl;
	   delay(1250);
return user;
}


void LVL1(MEMBER &user)
{

class LVL1{
char name[32],blood[3],prof[32];
float age,height;
public:

void INPUT(char n[32],float a, float h, char b[3],char p[32]){
strcpy(name,n);
age=a;
height=h;
strcpy(blood,b);
strcpy(prof,p);
}
void DISPLAY(int i)
{
cout<<"  "<<name;
gotoxy(30,i+2);
cout<<age;
gotoxy(40,i+2);
cout<<height;
gotoxy(52,i+2);
cout<<blood;
gotoxy(60,i+2);
cout<<prof<<endl;
}
};

void GETCH(); void COUT(char*);
int VERIFY(int[],int,int,int);

clrscr();
char menu[9][125]={
  "> Investigate the dead body\t(1)",
  "> Investigate the wall on which strange words are written\t(1)",
  "> Check out the lawn\t(1)",
  "> Investigate the watchman\t(2)",
  "> Talk to a local\t(2)",
  "> Take blood test of the word\t(2)",
  "> Ask for postmortem report\t(3)",
  "> Enquire the nearby Truck driver who took the ride\t(3)",
  "> Check nearby CCTV cameras\t(3)",};
int us_opt[9]={0,0,0,0,0,0,0,0,0};

LVL1 crime[7];
crime[0].INPUT("Marvin Eckart",30,5.6,"A+","Butcher");
crime[5].INPUT("Zack Cox",23,5.8,"O+","Local");
crime[1].INPUT("Elza Ashton",24,5.8,"A+","Teacher");
crime[4].INPUT("Mymaker Desezanio",28,5.9,"A+","Watchman");
crime[2].INPUT("Ash Rache",22,5.1,"O+","Truck driver");
crime[3].INPUT("Mo Dixon",34,5.8,"O+","Truck driver");
crime[6].INPUT("Bruce Eckart",32,5.9,"O+","Watchman");

int succ=0;
clrscr();
 char str[207];
 ifstream f1("lvl1.txt");
 if (!f1)
  {
   cerr<<"Required file not detected!";
   GETCH();
   exit(1);
  }
 do {
 f1.getline(str,207);
 for (int i=0;i<strlen(str);i++)
 {
 if (str[i]=='<'&&str[i+1]=='n'&&str[i+5]=='>')
 { //cout<<user.ret_name()<<',';
  i+=6;}
 cout<<str[i];
 delay(15); }
 delay(500);
 if (str[1]=='<'&&str[strlen(str)-1]=='>')
 {
  getch();
  clrscr();
 }
 cout<<"\n";
 }while(!f1.eof());
clrscr();

clock_t beg,end;
beg=time(NULL);

int a=0,n=3,token=user.ret_tokens()+12,p=0;   //token carried forward
do {
gotoxy(60,1);
cout<<"TOKENS: "<<token<<"\n\n";
cout<<"-  FORCE EXIT (Your progress WON't be saved!)\n";
for (int a=0;a<n;a++)
puts(menu[a]);
int inp=UPDOWN_SUS(3,n+1);
switch(inp)
{
case 1: clrscr();
	cout<<"\n\n\tAre you sure you want to quit? Your progress WON't be saved!!\n\tPress Y to confirm exit.	\t";
	char ch;
	ch=getche();
	if (ch=='y'||ch=='Y')
	{
	succ=-1;
	break;
	}
	break;

case 2:clrscr();
       if (VERIFY(us_opt,inp,token,1)==1)  {
       token--; n=5; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,1)==0)
       break;
       COUT("\n Surprisingly there is no injury on the dead body....");
       GETCH();
       break;
case 3:clrscr();
if (VERIFY(us_opt,inp,token,1)==1)  {
       token--; n=5; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,1)==0)
       break;
       COUT("\n It's about 5.6 ft above the ground...\n  A strange word \"RACHE\" has been written with blood...");
       GETCH();
       break;
case 4:clrscr();
if (VERIFY(us_opt,inp,token,1)==1)  {
       token--; n=5; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,1)==0)
       break;
       COUT("\n There are lots of footprints -- most probably that of the cops...\n  The back window has been opened...");
	     GETCH();
       break;
case 5:clrscr();
if (VERIFY(us_opt,inp,token,2)==1)  {
       token-=2; n=7; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,2)==0)
       break;
       COUT("\n You arrive curiously to the watchman's house...\n\n Wait... he is not on DUTY?\n\nCan you tell us what happened last night? And why are you not on DUTY today?\n\n  -- Yesterday night when I saw a light in the house... which has been locked up for years... \n     I started to move towards the doorstep...\n      also I am new to this job and there...\n     there has been a rumour that a spirit roams over here...\n      so I went back to call my friend who was in the other street\n      when I came back I saw a drunken man outside the lawn who couldn\'t even make a stand...\n      It was dark and raining... \n      so we helped him to get to the nearby street where a small truck with label\n       \'All kinds of fish are tasty at FISH FAINTERS\'\n      We reached the door step... but I don't know where he went...\n      ...but the light was not over there, so I called the cops...\n     due to yesterday\'s Rain I got extreme cold...\n       That\'s it sir.");
       GETCH();
       break;
case 6:clrscr();
if (VERIFY(us_opt,inp,token,2)==1)  {
       token-=2; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,2)==0)
       break;
       COUT("\n Do you have any idea about the murder in your neighbourhood?\n  -- I know who did it.\n\n Then tell us! I will guarentee your protection with military support.\n  --  Okay... Okay... It's no one other than spirit which I have seen with my eyes...\n     It must have did this as he attempted to loot the spirits place...\n      you can see it's clear also there are no injuries...\n     By the way, when i will be getting the protection?\n\n You better shut the door hard as you can! -.-");
       GETCH();
       break;
case 7:clrscr();
if (VERIFY(us_opt,inp,token,2)==1)  {
       token-=2; n=9; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,2)==0)
       break;
       COUT("\n The one who comes for the blood test says\n   \"The word RACHE, in German, means \'revenge\'.\n    ...And the blood group is \'O+\'");
       GETCH();
       break;
case 8:clrscr();
if (VERIFY(us_opt,inp,token,3)==1)  {
       token-=3; n=9; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,3)==0)
       break;
       COUT("\n The postmortem report says\n   \"No external injuries...\n    Presence of tetrodoxin in blood -- a poison found in few marine organisms.");
       GETCH();
       break;
case 9:clrscr();
    if (VERIFY(us_opt,inp,token,3)==1)  {
       token-=3; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,3)==0)
       break;
       COUT("\n The Truck driver who took the drunk man said \n   \"He was not drunk at all...\n    ...and he got off in the  railway station... \" \n\n But chief, there is only one train at that time. It goes to the Teutoni... \n    So no use talking with him...");
       GETCH();
       break;
case 10:clrscr();
if (VERIFY(us_opt,inp,token,3)==1)  {
       token-=3; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,token,inp,3)==0)
       break;
       COUT("\n- East: No movement, other than watchman.\n- West: No movement, other than watchman.\nSouth: 2 men walking along the street and one falls down suddenly and other drags him towards the North.\nNorth: The CCTV camera not installed yet\n\n  Still unclear... :(");
       GETCH();
       break;
case -1:

clrscr();
cout<<"  Name";
gotoxy(30,1);
cout<<"Age(yrs)";
gotoxy(40,1);
cout<<"Height(ft)";
gotoxy(52,1);
cout<<"Blood";
gotoxy(60,1);
cout<<"Profession\n";


if (n==5)
{
for (int r=0;r<3;r++)
crime[r].DISPLAY(r);
cout<<"\n\n <PRESS Enter TWICE to CONFIRM>";
int temp_conf=UPDOWN_SUS(2,3);
if (temp_conf==-1)
{clrscr();
break;
}
int conf=UPDOWN_SUS(2,3);
if (conf!=temp_conf)
{
clrscr();break;
}
switch(conf)
{
case 4:clrscr();
end=time(NULL); succ=1; break;
case -1: clrscr(); break;
default: clrscr();
end=beg; succ=2; break;
}
}

else if (n==7)
{
for (int r=0;r<6;r++)
crime[r].DISPLAY(r);
cout<<"\n\n <PRESS Enter TWICE to CONFIRM>";
int temp_conf=UPDOWN_SUS(2,6);
if (temp_conf==-1)
{clrscr();
break;
}
int conf=UPDOWN_SUS(2,6);
if (conf!=temp_conf)
{
clrscr();break;
}
switch(conf)
{
case 4:clrscr();
end=time(NULL); succ=1; break;
case -1: clrscr(); break;
default: clrscr();
end=beg; succ=2; break;
}
}

else if (n==9)
{
for (int r=0;r<7;r++)
crime[r].DISPLAY(r);
cout<<"\n\n <PRESS Enter TWICE to CONFIRM>";
int temp_conf=UPDOWN_SUS(2,7);
if (temp_conf==-1)
{clrscr();
break;
}
int conf=UPDOWN_SUS(2,7);
if (conf!=temp_conf)
{
clrscr();break;
}
switch(conf)
{
case 4:clrscr();
end=time(NULL); succ=1; break;
case -1: clrscr(); break;
default: clrscr();
end=beg; succ=2; break;
}
}

else
{
cout<<"\t\t<NO RECORDS. PLAY MORE TO GET SOME SUSPECTS>";
GETCH();
clrscr();
}
}
}while(!succ);

if (succ==1)
{
clrscr();
cout<<"\n\nCASE 1:\t COMPLETED!!\n\n XP earned: ";
double xp=(850-(end-beg))*11;
if (xp<0)
xp=0;
cout<<xp;
GETCH();
if (user.ret_lvl()<1)
{
user.upd_xp(xp);
user.upd_tokens(token);
user.upd_lvl(1);
}
}

if (succ==2)
{
clrscr();
cout<<"\n\nCASE 1:\t FAILED!!\n\n XP earned: -300";
if (user.ret_lvl()<1)
user.upd_xp(-300);
GETCH();
}

}


void LVL2(MEMBER &user)
{

clrscr();

class LVL2{
char name[32],prof[32];
float age, height;
public:

void INPUT(char n[32],float a,float h,char p[32]){
strcpy(name,n);
age=a;
height=h;
strcpy(prof,p);
}
void DISPLAY(int i)
{
cout<<"  "<<name;
gotoxy(35,i+2);
cout<<age;
gotoxy(45,i+2);
cout<<height;
gotoxy(60,i+2);
cout<<prof<<endl;
}
};

void GETCH(); void COUT(char*);
int VERIFY(int[],int,int,int);

char menu[4][2][250]={
	"> Check the CCTVs on top of the crown\t(1)",
	"> Look through the wide window on the right side of the stage\t(1)",
	"> Check the first floor CCTV (near the stairs)\t(2)",
	"> Meet Mr. Nixon\t(3)",
        "> Check another CCTV in 2nd floor\t(3)",
	"> Raid a Security Guard\'s house\t(3)",
	"> Go to the Harbour in search of a suspect\t(3)",
	"> Go to a suspect's house\t(4)",

};


 char str[207];
 ifstream f2("lvl2.txt");
 if (!f2)
  {
   cerr<<"Required file not detected!\n";
   GETCH();
   exit(1);
  }
 do {
 f2.getline(str,207);
 for (int i=0;i<strlen(str);i++)
 {
 if (str[i]=='<'&&str[i+1]=='n'&&str[i+5]=='>')
 { //cout<<user.ret_name()<<',';
  i+=6;}
 cout<<str[i];
 delay(15); }
 delay(500);
 if (str[1]=='<'&&str[strlen(str)-1]=='>')
 {
  getch();
  clrscr();
 }
 cout<<"\n";
 }while(!f2.eof());
clrscr();

int us_opt[8]={0,0,0,0,0,0,0,0};

LVL2 crime[6];
crime[4].INPUT("Nikki Woolf",34,5.5,"-- (UNKNOWN) --");
crime[5].INPUT("Mymaker Desezanio",28,5.7,"Director");
crime[2].INPUT("Sid Nixon",24,5.6,"Detective");
crime[3].INPUT("Mymaker Nixon",28,5.8,"-- (UNKNOWN) --");
crime[1].INPUT("Oz Adams",21,5.5,"Housekeeper");
crime[0].INPUT("Nezel Reagan",34,5.6,"Security Guard");

int succ=0;

clock_t beg,end;
beg=time(NULL);

int a=0,n=1,token=user.ret_tokens()+14,p=0;
do {
gotoxy(60,1);
cout<<"TOKENS: "<<token<<"\n\n";
cout<<"-  FORCE EXIT (Your progress WON't be saved!)\n";
for (int a=0;a<n;a++)
{puts(menu[a][0]); puts(menu[a][1]);}
int inp=UPDOWN_SUS(3,2*n+1);
switch(inp)
{
case 1: clrscr();
	cout<<"\n\n\tAre you sure you want to quit? Your progress WON't be saved!!\n\tPress Y to confirm exit.	\t";
	char ch;
	ch=getche();
	if (ch=='y'||ch=='Y')
	{
	succ=-1;
	break;
	}
	break;

case 2:clrscr();
       if (VERIFY(us_opt,inp,token,1)==1)  {
       token--; n=2; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,1)==0)
       break;
       COUT(" Let me check the CCTVs\n  -- It has already been checked by the police and detectives\n      ...but as its for you its worth seeing again\n\n You check the CCTV which is near the stairs (It also has an sound recorder :) )\n");
       COUT("\n\t16:00: Everything is fine\n\t16:30: Everything is fine\n\t17:00: The crown starts to disappear and the crowd starts agitating. \n\t       The guards come to control the crowd. Everyone is taken to 1st floor. \n\t       Someone moving into the heads room.\n");
       COUT("\t17:05: Nobody can be seen in the entire floor in any CCTVs.\n\t17:10: Nixon comes near the stage and checks it.\n\t       He also checks the ground the walls the window \n       You hear long whistle from the speaker\n\n\n  What is that sound, Nicholson?\n\t-- \"Must be due to a Cargo ship in the nearby river which is going past this building to the dock\"\n\n\t17:15: Room is without any movements");
       GETCH();
       break;
case 3:clrscr();
if (VERIFY(us_opt,inp,token,1)==1)  {
       token--; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,1)==0)
       break;
	COUT("\n You check out of the window\n\n There is a tree, a calm river, police just below you, and a traffic jam in the nearby road.\n Your partner suggests you to check the CCTV");
       GETCH();
       break;
case 4:clrscr();
if (VERIFY(us_opt,inp,token,2)==1)  {
       token-=2; n=3; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,2)==0)
       break;
	COUT("\n\t17:10: No movement\n\t17:13: Nixon comes down the stairs...");
GETCH();
       break;
case 5:clrscr();
if (VERIFY(us_opt,inp,token,3)==1)  {
       token-=3; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,3)==0)
       break;
	COUT("\n You arrive at Mr Nixon's house\n\n  Knock knock..................knock knock\n  No response\n\n You again come back to the museum\n");
	GETCH();
       break;
case 6:clrscr();
if (VERIFY(us_opt,inp,token,3)==1)  {
       token-=3; n=4; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,3)==0)
       break;
       COUT("\n\t17:15: You see a shadow near the stage - 5.7 ft high...\n\n\t -- \"Who's that? It was different in the other camera?\" says Nicholson.\n \"There is some device over there, hanging at the back of the stage....\" \n\n\t -- \"Chief, it says \'Graphical Simulator\'...\n\"Give me a list of all Graphical Engineers in Itoville!\"\n\n\n\t-- \"Sid Nixon, Mymaker Nixon... Nikki Woolf too... I think that\'s it, Chief\" ");
       GETCH();
       break;
case 7:clrscr();
if (VERIFY(us_opt,inp,token,3)==1)  {
       token-=3; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,3)==0)
       break;
COUT("\n The police officer says\n   \"Don\'t you know that you can't raid without any valid evidence? \n    ...And I don't find anything wrong with him ...\n    Sorry, you can't raid his house. That's it!\"");
				   GETCH();
       break;
case 8:clrscr();
if (VERIFY(us_opt,inp,token,3)==1)  {
       token-=3; us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,inp,token,3)==0)
       break;
COUT("\n You arrive at Harbour.\n You check in the boarding area and you can't find her\n  You check in the waiting lounge you see her with a briefcase... \n\n  Can you give me your briefcase? \n  -- But why, sir?\n (The guards catch her and you try to open briefcase)\n\n ...\n Aww... something shiny...");
					     GETCH();
       break;
case 9:clrscr();
if (VERIFY(us_opt,inp,token,4)==1)  {
       token-=4; succ=2;us_opt[p]=inp; p++;}
       else if (VERIFY(us_opt,token,inp,4)==0)
       break;
COUT("\n You arrive at the house\n\n Knock knock......... Knock knock\n   No response\n\n  I doubt him now...\n Lets break in\n  (The guards break the door)\n ...\n The entire house is empty & he is not here... \n\n\n You receive a call from the harbour\n  Hullo, Mr, you were close but I'm just gonna sail off...\n\n      ....Ship starts off \n\n\n\t\t***THE END....***");
GETCH();
       break;
case -1:

clrscr();
cout<<"  Name";
gotoxy(35,1);
cout<<"Age(yrs)";
gotoxy(45,1);
cout<<"Height(ft)";
gotoxy(60,1);
cout<<"Profession\n";
if (n==2)
{
for (int r=0;r<1;r++)
crime[r].DISPLAY(r);
cout<<"\n\n <PRESS Enter TWICE to CONFIRM>";
int temp_conf=UPDOWN_SUS(2,1);
if (temp_conf==-1)
{clrscr();
break;
}
int conf=UPDOWN_SUS(2,1);
if (conf!=temp_conf)
{
clrscr();break;
}
switch(conf)
{
case 5:clrscr();
end=time(NULL); succ=1; break;
case -1: clrscr(); break;
default: clrscr();
end=beg; succ=2; break;
}
}
else if (n==3)
{
for (int r=0;r<3;r++)
crime[r].DISPLAY(r);
cout<<"\n\n <PRESS Enter TWICE to CONFIRM>";
int temp_conf=UPDOWN_SUS(2,3);
if (temp_conf==-1)
{clrscr();
break;
}
int conf=UPDOWN_SUS(2,3);
if (conf!=temp_conf)
{
clrscr();break;
}
switch(conf)
{
case 5:clrscr();
end=time(NULL); succ=1; break;
case -1: clrscr(); break;
default: clrscr();
end=beg; succ=2; break;
}
}

else if (n==4)
{
for (int r=0;r<6;r++)
crime[r].DISPLAY(r);
cout<<"\n\n <PRESS Enter TWICE to CONFIRM>";
int temp_conf=UPDOWN_SUS(2,6);
if (temp_conf==-1)
{clrscr();
break;
}
int conf=UPDOWN_SUS(2,6);
if (conf!=temp_conf)
{clrscr(); break;}
switch(conf)
{
case 5:clrscr();
end=time(NULL); succ=1;break;
case -1: clrscr(); break;
default: clrscr();
end=beg; succ=2;   break;
}
}
else
{
cout<<"\t\t<NO RECORDS. PLAY MORE TO GET SOME SUSPECTS>";
GETCH();
clrscr();
}
}
}while(!succ);

if (succ==1)
{
clrscr();
cout<<"\n\nCASE 2:\t COMPLETED!!\n\n XP earned: ";
double xp=(900-(end-beg))*11;
if (xp<0)
xp=0;
cout<<xp;
GETCH();
if (user.ret_lvl()<2)
{
user.upd_xp(xp);
user.upd_tokens(token);
user.upd_lvl(2);
}
}

if (succ==2)
{
clrscr();
cout<<"\n\nCASE 2:\t FAILED!!\n\n XP earned: -500";
GETCH();
if (user.ret_lvl()<2)
user.upd_xp(-500);
}
}


void GETCH()
{
cout<<"\n\n\t<PRESS ANY KEY TO CONTINUE>";
getch();
clrscr();
}

int VERIFY(int user[],int opt,int tokens,int t_check){
for (int i=0;i<9;i++)
if (opt==user[i])
return -1;
if (tokens-t_check>=0)
return 1;
else
{cout<<"\n\nNo Enough Tokens...";
GETCH();
return 0;}

}

void COUT(char* ch)
{
while (*ch++!='\0')
{
cout<<*(ch-1); delay(50);}
}


  void init() {
	clrscr();
	gotoxy(2,20);
	cout<<"(C) All Rights Reserved";
	gotoxy(25,8);
	cout<<"Looking for a Database...";
	delay(999);
	MEMBER test;
	fstream f("USERS.DAT",ios::in|ios::binary);
	f.read((char*)&test,sizeof(test));
	if (strcmp(test.ret_userid(),"0"))
	{
	gotoxy(25,8);
	cout<<"Setting up a Database for the first time...";
	MEMBER m("0","0","0");
	MEMBER adm("admin","ADMIN","admin");
	m.pass_enc(); adm.pass_enc();
	   fstream f1("USERS.DAT",ios::out|ios::binary);
	   f1.write((char*)&m,sizeof(m));
	   f1.write((char*)&adm,sizeof(adm));
	   f1.close();
	delay(1999);
	}
	clrscr();
	gotoxy(2,20);
	cout<<"(C) All Rights Reserved";
	gotoxy(25,8);
	cout<<"Looking for files...";
	delay(1299);
	int succ=0;
	ifstream s;
	s.open("LVL0.TXT");
	if (!s)
	succ++;
	s.close();
	s.open("LVL1.TXT");
	if (!s)
	succ++;
	s.close();
	s.open("LVL2.TXT");
	if (!s)
	succ++;
	s.close();
	if (succ!=0)
	{
	gotoxy(25,8);
	cerr<<"Oops... Some Files are missing...";
	gotoxy(26,9);
	cout<<"Contact the administrator immediately.";
	gotoxy(25,11);
	cout<<"\t<PRESS ANY KEY TO EXIT>";
	getch();
	exit(1);
	}
	clrscr();
	gotoxy(2,20);
	cout<<"(C) All Rights Reserved";
	gotoxy(25,8);
	cout<<"Taking you to Itoville...";
	gotoxy(25,9);
	cout<<"    Just a moment...";
	delay(5000);
	clrscr();
	gotoxy(2,20);
	cout<<"(C) All Rights Reserved";
	gotoxy(25,8);
	cout<<"Landed safely at Itoville";
	gotoxy(20,10);
	cout<<"<PRESS ANY KEY TO VERIFY YOUR IDENTITY>";
	 getch();

	}










/*v21.1*/