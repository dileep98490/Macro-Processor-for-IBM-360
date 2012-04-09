#include<stdio.h>
#include<conio.h>
#include<string.h>
struct MACRODEF
{char name[15];
char def[100];
};//For storing macro definetions
struct ARGLIAR
{char hash[4];
char arg[12];
};//Arguement list array table for storing arguements
struct ARGLIAR a,a1;

struct MACRODEF m;
char label[15];
char op[15];
char operand[15];//Three strings storing the strings while moving across the file
int s=0;//flag for determining the MEND so that until then starting from MACRO can be stored in MDT

  FILE *fpm,*fpa;
static int ct=0;
int macro()//Used in pass1 to store macro definetions in MDT
{int i,st,en;
//For hashing
int flag;//To check for arguements
char ad[2];//To store the string converted int
fpa=fopen("ALA.dil","rb+");

    fpm=fopen("MDT.dil","rb+");
    if(fpm==NULL)
      fpm=fopen("MDT.dil","wb+");//MDT table in binary format
      if(strcmp(op,"MEND")!=0)
      {
      if(s==0)
     {
               s=1;strcpy(m.name,op);

      strcat(label,"\t");
     strcat(op,"\t");
     strcat(operand,"\n");//Combining label,op and operands, so that they can be stored combinely addding to the contents of definetion
    strcpy(m.def,label);
    strcat(m.def,op);
    strcat(m.def,operand);


     }
     else
    {
         /*The below is the code to fill ALA and also changing the values in macro definetion and filling
         them with index markers*/ 
          //Code to fill ALA
              i=0;
               flag=0;
               while(label[i]!='\0')
               {
               if(label[i]=='&')
               {flag=1;break;}i++;
               }


               if(flag==1)
               {
               i=0;
         while(label[i]!='\0')
    {if(label[i]=='&')
    {st=i;
    while(label[i]!=',' && label[i]!='\0')
    i++;
         en=i;
         label[st]='#';
         itoa(ct,ad,10);

         strcpy(a.hash,"#");
   
         strcat(a.hash,ad);
         label[st+1]=ad[0];
         st=st+2;
         while(label[en]!='\0')
         label[st++]=label[en++];
         label[st]='\0';
         fseek(fpa,0,SEEK_END);
         fwrite(&a,sizeof(a),1,fpa);
         ct++;

         }
       if(label[i]==NULL)
break;
         i++;
         }

          }
//End of code to fill ALA
//Code to fill ALA


               i=0;
               flag=0;
               while(operand[i]!='\0')
               {
               if(operand[i]=='&')
               {flag=1;break;}
               i++;
               }
          // i=0;
//            while(operand[i]!='\0')
//            {printf("%c\n",operand[i]);
//            i++;}
               if(flag==1)
               {
               i=0;

         while(operand[i]!='\0')
    {
         if(operand[i]=='&')
    {st=i;


    while(operand[i]!=NULL && operand[i]!=',')
 {
                           i++;

 }
         en=i;

          operand[st]='#';
         itoa(ct,ad,10);
         strcpy(a.hash,"#");
         strcat(a.hash,ad);
       operand[st+1]=ad[0];

         st=st+2;
         while(operand[en]!='\0')
         operand[st++]=operand[en++];
         operand[st]='\0';
               fseek(fpa,0,SEEK_END);
         fwrite(&a,sizeof(a),1,fpa);
         ct++;
         }
if(operand[i]==NULL)
break;
         i++;
         }

         }
//End of code to fill ALA


      strcat(label,"\t");
     strcat(op,"\t");
     strcat(operand,"\n");
    strcat(m.def,label);
    strcat(m.def,op);
    strcat(m.def,operand);


         }
         }
     fclose(fpa);
     }
    int pass2()
    {char str[100],str1[100];
char stru[10];
    char ad2[3];
    FILE *fpo;
    int k,flag,i;
    flag=0;
    fpa=fopen("ALA2.dil","rb+");
        fpm=fopen("MDT.dil","r");
                   fpo=fopen("Output.txt","a");//Pass 2 output file


        while(fread(&m,sizeof(m),1,fpm)==1)
        if(strcmp(m.name,op)==0)
        {
                    //Code for adding arguements to ALA from macro call itself
                i=0;
                                 while(operand[i]!='\0'&&operand[i]!='_')
                                { k=0;
                                                                         while(operand[i]!=',' && operand[i]!='\0')
                                         stru[k++]=operand[i++];


                                         itoa(ct,ad2,10);
                                stru[k]='\0';

                              strcpy(a1.hash,"#\0");



                                 strcat(a1.hash,ad2);
                                 strcpy(a1.arg,stru);
                                 fseek(fpa,0,SEEK_END);
                         
                                 fwrite(&a1,sizeof(a1),1,fpa);

                                 if(operand[i]=='\0')
                                 break;
                                         i++; ct++;

                                         }
                                         //End of code
                               k=0;i=0;







                                while(m.def[i]!=10)//For checking the end of line so that the macro defining is not copied
        i++;
        i++;
        while(m.def[i]!='\0')
        str[k++]=m.def[i++];//Storing the remaining part of macro definetion

                              flag=1;
                              k=k-1;
                              str[k]='\0';//Ending it early so that some variety type characters are not printed
                              //Code for printing
                              i=0;
                              while(str[i]!='\0')
                              {k=0;
                                                 while(str[i]!='#' && str[i]!='\0')
                               {str1[k++]=str[i++];//Making another small string so that it is convenient for printing purposes
                               }
                               str1[k]='\0';
                               
                             
                               if(str[i]=='#')
                               {  fprintf(fpo,"%s",str1);
                                              ad2[0]='#';
                               ad2[1]=str[i+1];
                               ad2[2]='\0';
                          
                               rewind(fpa);
                               while(fread(&a1,sizeof(a1),1,fpa)==1)
                              {
                                                                    if(strcmp(a1.hash,ad2)==0)
                               {
                                                        fseek(fpo,0,SEEK_END);
                                                        fprintf(fpo,"%s",a1.arg);//Printing the arguement retrieved from ALA to file
                                                      
                                                        break;
                                                        }}
                                                        i=i+2;
                                                        }
                                                         else
                                                          fprintf(fpo,"%s\n",str1);//If # is not found, then there is no need to replace anything in the string
                                                        }
                                                       
                               //End of code
                               break;}


if(flag!=1)
   fprintf(fpo,"%s\t%s\t%s\n",label,op,operand);
  fclose(fpo);
  fclose(fpm);

fclose(fpa);

        }


int main()
{FILE *fp,*fpn,*fpo;
fpa=fopen("ALA.dil","wb+");
fclose(fpa);
fpa=fopen("ALA2.dil","wb+");
fclose(fpa);
char stu[15];//For storing the operand so that endl value is not passed along with it
int i;
  fpo=fopen("Output.txt","w+");
  fclose(fpo);
fpm=fopen("MDT.dil","wb+");
fclose(fpm);//For initialising the needed files
int flag=0;
fp=fopen("Input.txt","r");
while(!feof(fp))
{
            fscanf(fp,"%s",label);
fscanf(fp,"%s",op);
fscanf(fp,"%s",operand);

if(flag==1)
macro();//If a macro definetion is found pass-1 is called

if(strcmp(op,"MACRO")==0)
flag=1; //Macro definetion found, flag is set so that from next step on, it can be stored in MDT


  if(strcmp(op,"MEND")==0)
  {
                            flag=0;s=0;
                         fseek(fpm,0,SEEK_END);   //For appending in the last, can be prevented if "a" attribute is used during the opening of file
  fwrite(&m,sizeof(m),1,fpm);
  fclose(fpm);
            }
            }

            rewind(fp);
             fpn=fopen("Input2.txt","w+");//creating the macro definetions free input for pass-2
             flag=0;
             i=0;
        while(!feof(fp))
{
            fscanf(fp,"%s",label);
fscanf(fp,"%s",op);
fscanf(fp,"%s",operand);

if(flag==1)
{if(strcmp(op,"MACRO")!=0)//If after MEND, MACRO is not found, that is the end of macro definetions
flag=2;
else
flag=0;}

if(flag==2)//After all the definetions ended we can set the flag to 2, and copy the remaining contents into new file
{fprintf(fpn,"%s\t%s\t%s\n",label,op,operand);
i++;
}

if(strcmp(op,"MEND")==0)
flag=1;//Checking whether MEND occurs
}

fclose(fpn);
fclose(fp);

          printf("Pass-1 is over\nThe definetions stored in MDT are:\n");
            fpm=fopen("MDT.dil","r");
            while(fread(&m,sizeof(m),1,fpm)==1)
            printf("%s\t\t\t\t\t\t%s",m.name,m.def);
            fclose(fpm);
            fpn=fopen("Input2.txt","r");


            ct=0;
             while(!feof(fpn))
             {


                   fscanf(fpn,"%s",label);
fscanf(fpn,"%s",op);
fscanf(fpn,"%s",operand);

                             pass2();
                           i--;
                           if(i==0)//To prevent the extra space of endl
                           break;

                             }
                              printf("The arguements stored in ALA are:\n");
            fpm=fopen("ALA2.dil","r");
            while(fread(&a1,sizeof(a1),1,fpm)==1)
            printf("%s\t%s\n",a1.hash,a1.arg);
            fclose(fpm);
                             printf("Pass-2 is over\n");
            getche();//To wait, so that screen is not closed abruptly


            }
