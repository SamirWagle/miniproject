
/** @file g.c
 *  @brief Contact Management System Program    
 *  Mini Project
 *  It  will add,edit,delete,search and list contacts stored
 *	A silple program with structure,pointer,function,array used
 *  @author: Samir Wagle 
 * Roll Number 60
 *Group CE
 
 */

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

struct contact //Structure

{

  char name[50], add[20], email[30], ph[10]; //Contact Name,Address,Email and Phone Number
};



void add();    //Function To take input
void search(); //Function To Search Data
void disp();   //Function to Display Stored Data
void del();    //Function to Delete Stored Data

int main() //Main Function
{
  char editname[50];
  FILE *create, *temporary;         //File  Pointers
  struct contact newcontact;        //Structure
  create = fopen("all.dll", "rb+"); //Open file in Binary Read Mode
  int ch;
  long int recsize;

top:
  //Main Menu Parts
  printf("\n\n\n\n\t\t\t\t\t\t  Welcome to Contact Management System \n\n");
  printf("\n\t [1]------ \tAdd a contact   \n");
  printf("\n\t [2]------ \tDelete a contact\n");
  printf("\n\t [3]------ \tSearch a contact\n");
  printf("\n\t [4]------ \tEdit contact detials\n");
  printf("\n\t [5]------ \tDisplay all contacts\n");
  printf("\n\t [0]------ \tEXIT\n");
  printf("\tEnter the choice:");

  scanf("%d", &ch); //Input of User Choice

  switch (ch)

  {

  case 1:  //when user press 1
    add(); //add() function is called
    break;

  case 2:  //when user press 2
    del(); //del() function is called
    break;

  case 3:          //when user press 3
    system("cls"); //clear screen
    search();      //search() function is called
    break;

  case 4: //when user press 4 Data editing portal will open
    system("cls");
    recsize=sizeof(newcontact);
    printf("Enter the contact name to modify: ");
    scanf("%s", &editname);                                        //taking input from user what name user want to modify
    rewind(create);                                                //move record to starting of a file
    while (fread(&newcontact, sizeof(newcontact), 1, create) == 1) //fetch all record from file
    {

      if (stricmp(newcontact.name, editname) == 0) //if entered name matches with that in file
      {
        printf("\nPress Enter After entering one data: \t\t\n ");
        printf("\n\tEnter New Name:\t");
        scanf("%s", &newcontact.name);
        printf("\n\tEnter New Address:\t");
        scanf("%s", &newcontact.add);
        printf("\n\tEnter Email Address:\t");
        scanf("%s", &newcontact.email);
        printf("\n\tEnter Phone Number:\t");
        scanf("%s", &newcontact.ph);
        fseek(create, -recsize, SEEK_CUR);                  /// move the cursor 1 step back from current position
        fwrite(&newcontact, sizeof(newcontact), 1, create); //overwrite record

        break;
      }
      fflush(stdin); //flush the input buffer
    }

    fclose(create); //close the file

    break;

  case 5: //when user press 5

    disp(); //disp() function is called which displays all record

    break;

  case 0: //exit
    return 0;
    break;

  default: //when user presses any other choices
    printf("\t Invalid Choice\n");
    break;
  }
  goto top; //goes to top
}

void add()
//this function takes contact input from the user and stores them in binary format dll file.
//This function asks user to input Name,Address, Email and Phone Number and stores them in file
{

  system("cls");
  struct contact newcontact;       //Structure
  FILE *create;                    //file pointers
  create = fopen("all.dll", "ab"); //opens all.dll

  fflush(stdin);

  printf("\n\nEnter Name in format Firstname_Lastname\n\t"); //Input from user
  scanf("%s", &newcontact.name);

  printf("\n\nEnter Address\n\t"); //Input from user
  scanf("%s", &newcontact.add);

  printf("\n\nEnter Email Address\n\t"); //Input from user
  scanf("%s", &newcontact.email);

  printf("\n\nEnter Phone Number\n\t"); //Input from user
  scanf("%s", &newcontact.ph);

  fwrite(&newcontact, sizeof(newcontact), 1, create); //write the input data in file

  fclose(create); //close file
  printf("Data Recorded Successfully. ");
  return;
}

void search() //this is search function
//this takes input from user and compares whether user input name is there on file or not
//if  user input name is there on file then it prints all the other necessary data like name,address,email and phone number
//if user input name is not there, program terminates;vv
{

  system("cls"); //clear screen
  char srh[20];
  char name[20];
  int found = 0;
  int l;
  int temp;
  int k = 0;
  int i;
  FILE *create = fopen("all.dll", "r"); //file pointers and opening file

  struct contact newcontact;

  printf("\n\tEnter Name Of Contact to Search\n\t");
  fflush(stdin);
  scanf("%s", &srh); //input part
  l = strlen(srh);   //total length of user input string
  printf("\tsearch result for %s is \n\n", srh);

  while (fread(&newcontact, sizeof(newcontact), 1, create) == 1) //fetch all the record
  {

    for (i = 0; i <= l; i++) //it takes individual data and compares it to stored data

      name[i] = newcontact.name[i];
    name[l] = '\0';

    if (strcmp(name, srh) == 0) //i f data found then it will print it
    {
      printf("\n\n\n\t\t\tRecord Found");
      printf("\n\n\tName\t%s", &newcontact.name);
      printf("\n\n\tAddress\t :%s", &newcontact.add);
      printf("\n\n\tEmail : \t%s", &newcontact.email);
      printf("\n\n\tPhone Number :\t %s", &newcontact.ph);
      found++;
    }
  }
  if (found == 0) //if not found then it will print no match found
    printf("\n\tNo match found!");

  else

    printf("\n\t%d contact found!", found); //counting how many data was found

  fclose(create);
}
void disp()
//display function
//it displays all the data stored in a file
{
  int plus = 1;
  //(c) sAMIR wAGLE ALL RIGHTS RESERVED
  int ch;
  struct contact newcontact;

  FILE *create; //file pointer
  printf("The Stored Records Are:\n\n");
  create = fopen("all.dll", "rb"); //opens file
  while (fread(&newcontact, sizeof(newcontact), 1, create))
  { //reads file

    printf("%d\tName=%s\t\tAddress=%s\t\tEmail= %s\t\tPhone.No=%s\t", plus, newcontact.name, newcontact.add, newcontact.email, newcontact.ph); //displays file
    plus++;                                                                                                                                    //counts the data
    printf("\n\n");
  }
//(C) Samir Wagle all rights reserved

  fclose(create); //closes the file
  printf("End of The List");
}
void del()
//This function is used to delete the selected data
//it asks user to enter name you want to delete and compares that name to name stored in file
//if name matches then it will delete the file
//if it does not matches then it will skip
{

  struct contact newcontact;
  FILE *create, *temporary;
  create = fopen("all.dll", "rb");
  temporary = fopen("temp.dat", "wb"); //intermediate temporary file for temporary storing
  char editname[50];                   //character declaration
  system("cls");
  printf("Enter the contact name to delete: ");
  scanf("%s", editname);
  rewind(create); //move record to starting of point

  while (fread(&newcontact, sizeof(newcontact), 1, create) == 1) ///reads data from file
  {

    if (strcmp(newcontact.name, editname) != 0) //compares two strings and check whether the entered record match or not
//Command 
    {

      fwrite(&newcontact, sizeof(newcontact), 1, temporary);
      //moves all the record except that one we want to delete
    }
  }

  fclose(create);    // close the file with create pointer
  fclose(temporary); //close the temporary file

//(c) Samir Wagle All rights reserved
  create = fopen("all.dll", "wb");
  temporary = fopen("temp.dat", "rb");
  //this while loop is used to print the required data
  while (fread(&newcontact, sizeof(newcontact), 1, temporary) == 1)
  {
// for(i=1,i<=n,i++);
//fp=fopen"all.dll","rb"
//fp=fread"app.dll","rb"
//iif(i-1 i<=cheeckname i++ i--,c+c--100
 
    fwrite(&newcontact, sizeof(newcontact), 1, create);
    
  }

  fclose(create);
  fclose(temporary);

  printf("If Data Found Then It will be deleted successfully. If data is not found then it will discard");
}
