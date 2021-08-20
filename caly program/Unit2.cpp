//---------------------------------------------------------------------------

#include <vcl.h>


#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
void dodaj_czynnosc(unsigned char przek, unsigned char idx)
{
AnsiString czyn;

   if(Form3->przekazniki[przek].czynnosc[idx-1].tylkowtedy)
   {
    czyn = "# ";
     if(Form3->przekazniki[przek].czynnosc[idx-1].wlacz)
    czyn+="wl ";else czyn += "wyl  ";
    czyn+= (unsigned char)Form3->przekazniki[przek].czynnosc[idx-1].tg;
    czyn+=":";
    czyn+= (unsigned char)Form3->przekazniki[przek].czynnosc[idx-1].tm;
    czyn+=":";
    czyn+= (unsigned char)Form3->przekazniki[przek].czynnosc[idx-1].ts;
    czyn += "   ";
    czyn+= (unsigned char)Form3->przekazniki[przek].czynnosc[idx-1].dzien;
    czyn+= ".";
    czyn+= (unsigned char)Form3->przekazniki[przek].czynnosc[idx-1].miesiac;
    czyn += ".";
    czyn+= (unsigned int)Form3->przekazniki[przek].czynnosc[idx-1].rok;
    czyn+="r";
   }else
 {
 if(Form3->przekazniki[przek].czynnosc[idx-1].wlacz)
  czyn="wl ";else czyn="wyl ";
 if(Form3->przekazniki[przek].czynnosc[idx-1].pon)
  czyn += "pon ";
   if(Form3->przekazniki[przek].czynnosc[idx-1].wt)
  czyn += "wt ";
   if(Form3->przekazniki[przek].czynnosc[idx-1].sr)
  czyn += "sr ";
   if(Form3->przekazniki[przek].czynnosc[idx-1].czw)
  czyn += "czw ";
   if(Form3->przekazniki[przek].czynnosc[idx-1].pia)
  czyn += "pia ";
   if(Form3->przekazniki[przek].czynnosc[idx-1].sob)
  czyn += "sob ";
   if(Form3->przekazniki[przek].czynnosc[idx-1].nie)
  czyn += "nie ";

  czyn += (unsigned char)Form3->przekazniki[przek].czynnosc[idx-1].g;
  czyn+= ":";
  czyn += (unsigned char)Form3->przekazniki[przek].czynnosc[idx-1].m;
  czyn+= ":";
  czyn += (int)Form3->przekazniki[przek].czynnosc[idx-1].s;
  }
 Form2->ListBox1->Items->Add(czyn);
}
void get_nazwy()
{
if(Form2->ComboBox3->Text == "PrzekaŸnik 1")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[0]; else
if(Form2->ComboBox3->Text == "PrzekaŸnik 2")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[1]; else
if(Form2->ComboBox3->Text == "PrzekaŸnik 3")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[2]; else
if(Form2->ComboBox3->Text == "PrzekaŸnik 4")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[3]; else
if(Form2->ComboBox3->Text == "PrzekaŸnik 5")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[4]; else
if(Form2->ComboBox3->Text == "PrzekaŸnik 6")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[5]; else
if(Form2->ComboBox3->Text == "PrzekaŸnik 7")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[6]; else
if(Form2->ComboBox3->Text == "PrzekaŸnik 8")
 Form2->Edit1->Text = Form3->nazwy_przekaznikow[7];
}
void pokaz_czynnosci()
{
 Form2->ListBox1->Clear();
 
 if(Form2->ComboBox1->Text == "PrzekaŸnik 1")
  if(Form3->czynnosci[0]>0)
   for(int i=1;i<=Form3->czynnosci[0];i++)
    dodaj_czynnosc(0,i);

 if(Form2->ComboBox1->Text == "PrzekaŸnik 2")
  if(Form3->czynnosci[1]>0)
   for(int i=1;i<=Form3->czynnosci[1];i++)
    dodaj_czynnosc(1,i);

 if(Form2->ComboBox1->Text == "PrzekaŸnik 3")
  if(Form3->czynnosci[2]>0)
   for(int i=1;i<=Form3->czynnosci[2];i++)
    dodaj_czynnosc(2,i);

 if(Form2->ComboBox1->Text == "PrzekaŸnik 4")
  if(Form3->czynnosci[3]>0)
   for(int i=1;i<=Form3->czynnosci[3];i++)
    dodaj_czynnosc(3,i);

 if(Form2->ComboBox1->Text == "PrzekaŸnik 5")
  if(Form3->czynnosci[4]>0)
   for(int i=1;i<=Form3->czynnosci[4];i++)
    dodaj_czynnosc(4,i);

 if(Form2->ComboBox1->Text == "PrzekaŸnik 6")
  if(Form3->czynnosci[5]>0)
   for(int i=1;i<=Form3->czynnosci[5];i++)
    dodaj_czynnosc(5,i);

 if(Form2->ComboBox1->Text == "PrzekaŸnik 7")
  if(Form3->czynnosci[6]>0)
   for(int i=1;i<=Form3->czynnosci[6];i++)
    dodaj_czynnosc(6,i);

 if(Form2->ComboBox1->Text == "PrzekaŸnik 8")
  if(Form3->czynnosci[7]>0)
   for(int i=1;i<=Form3->czynnosci[7];i++)
    dodaj_czynnosc(7,i);
}
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Dodajczynno1Click(TObject *Sender)
{
Form3->ShowModal();
pokaz_czynnosci();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormActivate(TObject *Sender)
{
  ComboBox2->Items->Clear();
  get_nazwy();
  pokaz_czynnosci();
  for (UINT i=1; i<25; i++)
    {
   AnsiString TestS = "";
   TestS.sprintf("\\\\.\\COM%d",i);
  
      //Try to open the port
   bool bSuccess = false;
   HANDLE hPort = ::CreateFile(TestS.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
   if (hPort == INVALID_HANDLE_VALUE)
      {
        DWORD dwError = GetLastError();

        //Check to see if the error was because some other app had the port open
        if (dwError == ERROR_ACCESS_DENIED)
          bSuccess = TRUE;
      }
      else
      {
        //The port was opened successfully
        bSuccess = TRUE;

        //Don't forget to close the port, since we are going to do nothing with it anyway
        CloseHandle(hPort);
      }

      //Add the port number to the array which will be returned
   if (bSuccess)
   ComboBox2->Items->Add("COM" + IntToStr(i));
  }
}
//---------------------------------------------------------------------------




void __fastcall TForm2::ComboBox3Change(TObject *Sender)
{
 get_nazwy();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
  if(ComboBox3->Text == "PrzekaŸnik 1")
Form3->nazwy_przekaznikow[0] = Edit1->Text; else
  if(ComboBox3->Text == "PrzekaŸnik 2")
Form3->nazwy_przekaznikow[1] = Edit1->Text; else
  if(ComboBox3->Text == "PrzekaŸnik 3")
Form3->nazwy_przekaznikow[2] = Edit1->Text; else
  if(ComboBox3->Text == "PrzekaŸnik 4")
Form3->nazwy_przekaznikow[3] = Edit1->Text; else
  if(ComboBox3->Text == "PrzekaŸnik 5")
Form3->nazwy_przekaznikow[4] = Edit1->Text; else
  if(ComboBox3->Text == "PrzekaŸnik 6")
Form3->nazwy_przekaznikow[5] = Edit1->Text; else
  if(ComboBox3->Text == "PrzekaŸnik 7")
Form3->nazwy_przekaznikow[6] = Edit1->Text; else
  if(ComboBox3->Text == "PrzekaŸnik 8")
Form3->nazwy_przekaznikow[7] = Edit1->Text;

}
//---------------------------------------------------------------------------




void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
pokaz_czynnosci();
if(ComboBox1->Text=="PrzekaŸnik 1")
 Form3->edit = 0; else
if(ComboBox1->Text=="PrzekaŸnik 2")
 Form3->edit = 1; else
if(ComboBox1->Text=="PrzekaŸnik 3")
 Form3->edit = 2; else
if(ComboBox1->Text=="PrzekaŸnik 4")
 Form3->edit = 3; else
if(ComboBox1->Text=="PrzekaŸnik 5")
 Form3->edit = 4; else
if(ComboBox1->Text=="PrzekaŸnik 6")
 Form3->edit = 5; else
if(ComboBox1->Text=="PrzekaŸnik 7")
 Form3->edit = 6; else
if(ComboBox1->Text=="PrzekaŸnik 8")
 Form3->edit = 7;
}
//---------------------------------------------------------------------------



void __fastcall TForm2::Usunwszystkie1Click(TObject *Sender)
{
if(ComboBox1->Text=="PrzekaŸnik 1")
 {
   ZeroMemory(&Form3->czynnosci[0],sizeof(Form3->czynnosci[0]) );
   ZeroMemory(&Form3->przekazniki[0].czynnosc,sizeof(Form3->przekazniki[0].czynnosc) );
 }
if(ComboBox1->Text=="PrzekaŸnik 2")
 {
   ZeroMemory(&Form3->czynnosci[1],sizeof(Form3->czynnosci[1]) );
   ZeroMemory(&Form3->przekazniki[1].czynnosc,sizeof(Form3->przekazniki[1].czynnosc) );
 }
if(ComboBox1->Text=="PrzekaŸnik 3")
 {
   ZeroMemory(&Form3->czynnosci[2],sizeof(Form3->czynnosci[2]) );
   ZeroMemory(&Form3->przekazniki[2].czynnosc,sizeof(Form3->przekazniki[2].czynnosc) );
 }
if(ComboBox1->Text=="PrzekaŸnik 4")
 {
   ZeroMemory(&Form3->czynnosci[3],sizeof(Form3->czynnosci[3]) );
   ZeroMemory(&Form3->przekazniki[3].czynnosc,sizeof(Form3->przekazniki[3].czynnosc) );
 }
if(ComboBox1->Text=="PrzekaŸnik 5")
 {
   ZeroMemory(&Form3->czynnosci[4],sizeof(Form3->czynnosci[4]) );
   ZeroMemory(&Form3->przekazniki[4].czynnosc,sizeof(Form3->przekazniki[4].czynnosc) );
 }
if(ComboBox1->Text=="PrzekaŸnik 6")
 {
   ZeroMemory(&Form3->czynnosci[5],sizeof(Form3->czynnosci[5]) );
   ZeroMemory(&Form3->przekazniki[5].czynnosc,sizeof(Form3->przekazniki[5].czynnosc) );
 }
if(ComboBox1->Text=="PrzekaŸnik 7")
 {
   ZeroMemory(&Form3->czynnosci[6],sizeof(Form3->czynnosci[6]) );
   ZeroMemory(&Form3->przekazniki[6].czynnosc,sizeof(Form3->przekazniki[6].czynnosc) );
 }
if(ComboBox1->Text=="PrzekaŸnik 8")
 {
   ZeroMemory(&Form3->czynnosci[7],sizeof(Form3->czynnosci[7]) );
   ZeroMemory(&Form3->przekazniki[7].czynnosc,sizeof(Form3->przekazniki[7].czynnosc) );
 }


 pokaz_czynnosci();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Usunczynnosc1Click(TObject *Sender)
{
  if(ComboBox1->Text == "PrzekaŸnik 1")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[0]--;
         ZeroMemory(&Form3->przekazniki[0].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[0].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[0].czynnosc[x] = Form3->przekazniki[0].czynnosc[x+1];
           Form3->czynnosci[0]--;
          }
  if(ComboBox1->Text == "PrzekaŸnik 2")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[1]--;
         ZeroMemory(&Form3->przekazniki[1].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[1].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[1].czynnosc[x] = Form3->przekazniki[1].czynnosc[x+1];
           Form3->czynnosci[1]--;
          }
  if(ComboBox1->Text == "PrzekaŸnik 3")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[2]--;
         ZeroMemory(&Form3->przekazniki[2].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[2].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[2].czynnosc[x] = Form3->przekazniki[2].czynnosc[x+1];
           Form3->czynnosci[2]--;
          }
  if(ComboBox1->Text == "PrzekaŸnik 4")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[3]--;
         ZeroMemory(&Form3->przekazniki[3].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[3].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[3].czynnosc[x] = Form3->przekazniki[3].czynnosc[x+1];
           Form3->czynnosci[3]--;
          }
  if(ComboBox1->Text == "PrzekaŸnik 5")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[4]--;
         ZeroMemory(&Form3->przekazniki[4].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[4].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[4].czynnosc[x] = Form3->przekazniki[4].czynnosc[x+1];
           Form3->czynnosci[4]--;
          }
  if(ComboBox1->Text == "PrzekaŸnik 6")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[5]--;
         ZeroMemory(&Form3->przekazniki[5].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[5].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[5].czynnosc[x] = Form3->przekazniki[5].czynnosc[x+1];
           Form3->czynnosci[5]--;
          }
  if(ComboBox1->Text == "PrzekaŸnik 7")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[6]--;
         ZeroMemory(&Form3->przekazniki[6].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[6].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[6].czynnosc[x] = Form3->przekazniki[6].czynnosc[x+1];
           Form3->czynnosci[6]--;
          }
  if(ComboBox1->Text == "PrzekaŸnik 8")
     if(ListBox1->ItemIndex>=0)
      if(ListBox1->ItemIndex+1==ListBox1->Items->Count)
        {
         Form3->czynnosci[7]--;
         ZeroMemory(&Form3->przekazniki[7].czynnosc[ListBox1->ItemIndex],sizeof(Form3->przekazniki[7].czynnosc)[ListBox1->ItemIndex] );
        } else
         {
          for(int x = ListBox1->ItemIndex;x<max_czynnosci;x++)
           Form3->przekazniki[7].czynnosc[x] = Form3->przekazniki[7].czynnosc[x+1];
           Form3->czynnosci[7]--;
          }

  pokaz_czynnosci();
}
//---------------------------------------------------------------------------


