//---------------------------------------------------------------------------


#pragma hdrstop

#include "soc.h"
#include <vcl>
bool dpolaczony;
bool passcheck;
//---------------------------------------------------------------------------

#pragma package(smart_init)
unsigned int parametr_count(AnsiString kom)
{
 if(kom == "") return 0;
 unsigned int count = 1;
 for(int i = 1; i<kom.Length();i++)
  if(kom[i]=='&') count ++;
 return count;
}
AnsiString eparametr(AnsiString kom, unsigned int id)
{
 AnsiString ret;
 int k = kom.Length();
 unsigned int i = 1, z = 0;

 while((z!=id)&&(i<=kom.Length()))
    if(kom[i++]=='&') z++;
    
 while((kom[i]!='&')&&(i<=k))
  {
    ret+=kom[i++];
    if(i>k) break;
  }
 return ret;
} 