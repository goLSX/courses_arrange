#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include "structure.h"

void mainmenu();	

int Locate(char* ch);			

void Read_file();	

void Print_message(); 

void Adjust_message(); 

void File_Update();   

void Arrange_Selete(int choice);		

void Arrange(VexNode *result,int choice);

void Top_Sort(VexNode *result,int choice);	

void Print_Top_Sort_Result();  

#endif // FUNC_H_INCLUDED
