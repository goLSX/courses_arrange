#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include "structure.h"

void mainmenu();	//....

int Locate(char* ch);			//ok

void Read_file();	//ok

void Print_message(); //ok

void Adjust_message(); //ok

void File_Update();   //ok

void Arrange_Selete(int choice);		//ok

void Arrange(VexNode *result,int choice);

void Top_Sort(VexNode *result,int choice);	//ok

void Print_Top_Sort_Result();   //ok

#endif // FUNC_H_INCLUDED
