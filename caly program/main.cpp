//---------------------------------------------------------------------------

#include <vcl.h>
#include "unit2.h"
#include "about.h"
#pragma hdrstop
#include<sysmac.h>
#include "main.h"
#include <stdio.h>
#include <inifiles.hpp>
#include <registry.hpp>
#include <time.h>
#include "soc.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"



TForm1 *Form1;

#define cbOutQueue 5//rozmiar bufora danych wyjœciowych
#define cbInQueue 5 //rozmiar bufora danych wejœciowych
#define uint8_t unsigned char

HANDLE hCommDev; // identyfikator portu szeregowego
DCB dcb; // struktura kontroli portu
LPCTSTR lpFileName = "COM3"; // wskaŸnik do nazwy portu
COMMPROP CommProp;
  DWORD fdwEvtMask = (EV_TXEMPTY | EV_CTS);
char Buffer_O[cbOutQueue]; // bufor danych wyjœciowych
char Buffer_I[cbInQueue]; // bufor danych wejœciowych
   COMSTAT Stat;
DWORD Errors;

void allcheck()
{
 if((Form1->SpeedButton1->Down)&&
    (Form1->SpeedButton2->Down)&&
    (Form1->SpeedButton3->Down)&&
    (Form1->SpeedButton4->Down)&&
    (Form1->SpeedButton5->Down)&&
    (Form1->SpeedButton6->Down)&&
    (Form1->SpeedButton7->Down)&&
    (Form1->SpeedButton8->Down)){ Form1->SpeedButton9->Down = true;
                                  Form1->all->Checked = true; } else
    { Form1->SpeedButton9->Down = false;
                                    Form1->all->Checked = false; }
/* if((!Form1->SpeedButton1->Down)&&
    (!Form1->SpeedButton2->Down)&&
    (!Form1->SpeedButton3->Down)&&
    (!Form1->SpeedButton4->Down)&&
    (!Form1->SpeedButton5->Down)&&
    (!Form1->SpeedButton6->Down)&&
    (!Form1->SpeedButton7->Down)&&
    (!Form1->SpeedButton8->Down)) { Form1->SpeedButton9->Down = false;
                                    Form1->all->Checked = false; }  */
}
const uint8_t crclockup[] = {0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
							157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
							35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
							190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
							70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
							219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
							101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
							248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
							140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
							17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
							175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
							50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
							202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
							87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
							233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
							116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53};

uint8_t CountCRC(uint8_t* c)  // Policz CRC dla danych znajduj¹cych siê
															// pod wskaŸnikim c o rozmiarze size bajtów
{
	uint8_t i,initVal=0;
	for(i = 1; i <= 3; i++)
	{
		initVal = crclockup[c[i] ^ initVal];
	}
	return initVal;
}
 void autostart()
{
   String name = "SterowanieListwa";
  String date  = Application->ExeName;
 if(Form2->CheckBox2->Checked)
  {
  TRegistry& Rejestr = *new TRegistry();
  Rejestr.RootKey = HKEY_LOCAL_MACHINE;
  Rejestr.OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", false);
  Rejestr.WriteString(name,date);
  delete &Rejestr;

  }else
  {
  TRegistry& Rejestr = *new TRegistry();
  Rejestr.RootKey = HKEY_LOCAL_MACHINE;
  Rejestr.OpenKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", false);
  if(Rejestr.ValueExists(name)) Rejestr.DeleteValue(name);

  delete &Rejestr;
  }
}
void zapisz_ustawienia()
{
   TIniFile *ini;
   ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
   ini->WriteString("ustawienia","port",Form3->port);
   ini->WriteBool("ustawienia","dostep_z_internetu",Form2->CheckBox1->Checked);
   ini->WriteString("ustawienia","haslo",Form2->LabeledEdit1->Text);
   ini->WriteBool("ustawienia","start_z_windows",Form2->CheckBox2->Checked);
   ini->WriteBool("ustawienia","start_zminimalizowany",Form2->CheckBox3->Checked);
   ini->WriteString("nazwy_przekaznikow","1",Form3->nazwy_przekaznikow[0]);
   ini->WriteString("nazwy_przekaznikow","2",Form3->nazwy_przekaznikow[1]);
   ini->WriteString("nazwy_przekaznikow","3",Form3->nazwy_przekaznikow[2]);
   ini->WriteString("nazwy_przekaznikow","4",Form3->nazwy_przekaznikow[3]);
   ini->WriteString("nazwy_przekaznikow","5",Form3->nazwy_przekaznikow[4]);
   ini->WriteString("nazwy_przekaznikow","6",Form3->nazwy_przekaznikow[5]);
   ini->WriteString("nazwy_przekaznikow","7",Form3->nazwy_przekaznikow[6]);
   ini->WriteString("nazwy_przekaznikow","8",Form3->nazwy_przekaznikow[7]);
   delete ini;

}
void ustaw_nazwy_przyciskow()
{
Form1->SpeedButton1->Caption = Form3->nazwy_przekaznikow[0];
Form1->SpeedButton2->Caption = Form3->nazwy_przekaznikow[1];
Form1->SpeedButton3->Caption = Form3->nazwy_przekaznikow[2];
Form1->SpeedButton4->Caption = Form3->nazwy_przekaznikow[3];
Form1->SpeedButton5->Caption = Form3->nazwy_przekaznikow[4];
Form1->SpeedButton6->Caption = Form3->nazwy_przekaznikow[5];
Form1->SpeedButton7->Caption = Form3->nazwy_przekaznikow[6];
Form1->SpeedButton8->Caption = Form3->nazwy_przekaznikow[7];


Form1->p1->Caption  = Form3->nazwy_przekaznikow[0];
Form1->p2->Caption  = Form3->nazwy_przekaznikow[1];
Form1->p3->Caption  = Form3->nazwy_przekaznikow[2];
Form1->p4->Caption  = Form3->nazwy_przekaznikow[3];
Form1->p5->Caption  = Form3->nazwy_przekaznikow[4];
Form1->p6->Caption  = Form3->nazwy_przekaznikow[5];
Form1->p7->Caption  = Form3->nazwy_przekaznikow[6];
Form1->p8->Caption  = Form3->nazwy_przekaznikow[7];
}
void odczytaj_ustawienia()
{
   TIniFile *ini;
   ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );
   Form3->port = ini->ReadString("ustawienia","port"," ");
   Form2->CheckBox1->Checked = ini->ReadBool("ustawienia","dostep_z_internetu",false);
   Form2->LabeledEdit1->Text = ini->ReadString("ustawienia","haslo"," ");
   Form2->CheckBox2->Checked = ini->ReadBool("ustawienia","start_z_windows",false);
   Form2->CheckBox3->Checked = ini->ReadBool("ustawienia","start_zminimalizowany",false);
   Form3->nazwy_przekaznikow[0] = ini->ReadString("nazwy_przekaznikow","1","Przekaznik 1");
   Form3->nazwy_przekaznikow[1] = ini->ReadString("nazwy_przekaznikow","2","Przekaznik 2");
   Form3->nazwy_przekaznikow[2] = ini->ReadString("nazwy_przekaznikow","3","Przekaznik 3");
   Form3->nazwy_przekaznikow[3] = ini->ReadString("nazwy_przekaznikow","4","Przekaznik 4");
   Form3->nazwy_przekaznikow[4] = ini->ReadString("nazwy_przekaznikow","5","Przekaznik 5");
   Form3->nazwy_przekaznikow[5] = ini->ReadString("nazwy_przekaznikow","6","Przekaznik 6");
   Form3->nazwy_przekaznikow[6] = ini->ReadString("nazwy_przekaznikow","7","Przekaznik 7");
   Form3->nazwy_przekaznikow[7] = ini->ReadString("nazwy_przekaznikow","8","Przekaznik 8");

   delete ini;
}
void zapiszczynnosciautomatyczne()
{
    FILE *stream;

   if ((stream = fopen(ChangeFileExt( Application->ExeName, ".prz" ).c_str() , "wb")) == NULL) /* open file TEST.$$$ */
      return;
   fwrite(&Form3->przekazniki, sizeof(Form3->przekazniki), 1, stream); /* write struct s to file */
   fclose(stream); /* close file */
      if ((stream = fopen(ChangeFileExt( Application->ExeName, ".pzr" ).c_str() , "wb")) == NULL) /* open file TEST.$$$ */
      return;
   fwrite(&Form3->czynnosci, sizeof(Form3->czynnosci), 1, stream); /* write struct s to file */
   fclose(stream); /* close file */
}
void odczytajczynnosciautomatyczne()
{
     FILE *stream;

   if ((stream = fopen(ChangeFileExt( Application->ExeName, ".prz" ).c_str(), "rb")) == NULL)
      return;

   fread(&Form3->przekazniki, sizeof(Form3->przekazniki), 1, stream); /* write struct s to file */
   fclose(stream); /* close file */
      if ((stream = fopen(ChangeFileExt( Application->ExeName, ".pzr" ).c_str(), "rb")) == NULL)
      return;

   fread(&Form3->czynnosci, sizeof(Form3->czynnosci), 1, stream); /* write struct s to file */
   fclose(stream);
}

//---------------------------------------------------------------------------

 int __fastcall Read_Comm(HANDLE hCommDev,
LPDWORD lpNumberOfBytesRead, DWORD Buf_Size)
{
DWORD nNumberOfBytesToRead;
ClearCommError(hCommDev, &Errors ,&Stat);
if (Stat.cbInQue > 0)
{
if (Stat.cbInQue > Buf_Size)
nNumberOfBytesToRead = Buf_Size;
else
nNumberOfBytesToRead = Stat.cbInQue;
ReadFile(hCommDev, &Buffer_I[0], nNumberOfBytesToRead,
lpNumberOfBytesRead, NULL);
}
else
*lpNumberOfBytesRead = 0;
return TRUE;
}
//--------------------------------------------------------------------
int __fastcall Write_Comm(HANDLE hCommDev, LPCVOID lpBuffer,
DWORD nNumberOfBytesToWrite)
{
DWORD NumberOfBytesWritten;
if (WriteFile(hCommDev, lpBuffer, nNumberOfBytesToWrite,
&NumberOfBytesWritten, NULL) > 0)
{
WaitCommEvent(hCommDev, &fdwEvtMask, NULL);
return TRUE;
}
else
return FALSE;
}
//---------------------------------------------------------------------------
int __fastcall Close_Comm(HANDLE hCommDev)
{
if ((hCommDev == 0) || (hCommDev == INVALID_HANDLE_VALUE))
{
return FALSE;
}
else
{
CloseHandle(hCommDev);
return TRUE;
}
}
 void __fastcall on(unsigned char ch)
 {
   unsigned char buf[] = {0x55,0x01,'O',ch,0x28};
   buf[4] = CountCRC(buf);
  Write_Comm(hCommDev,&buf,5);
 }
  void __fastcall off(unsigned char ch)
 {
   unsigned char buf[] = {0x55,0x01,'F',ch,0x28};
  buf[4] = CountCRC(buf);
  Write_Comm(hCommDev,&buf,5);
 }
 void __fastcall allon()
 {
  unsigned char buf[] = {0x55,0x01,'S',0xff,0x28};
  buf[4] = CountCRC(buf);
  Write_Comm(hCommDev,&buf,5);
 }
 void __fastcall alloff()
 {
  unsigned char buf[] = {0x55,0x01,'S',0x00,0x28};
  buf[4] = CountCRC(buf);
  Write_Comm(hCommDev,&buf,5);
 }
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void graph()
{
    if(Form1->SpeedButton1->Down)
   Form1->SpeedButton1->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton1->Glyph->Assign(Form1->Image1->Picture->Bitmap);
    if(Form1->SpeedButton2->Down)
   Form1->SpeedButton2->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton2->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton3->Down)
   Form1->SpeedButton3->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton3->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton4->Down)
   Form1->SpeedButton4->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton4->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton5->Down)
   Form1->SpeedButton5->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton5->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton6->Down)
   Form1->SpeedButton6->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton6->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton7->Down)
   Form1->SpeedButton7->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton7->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton7->Down)
   Form1->SpeedButton7->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton7->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton8->Down)
   Form1->SpeedButton8->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton8->Glyph->Assign(Form1->Image1->Picture->Bitmap);
       if(Form1->SpeedButton9->Down)
   Form1->SpeedButton9->Glyph->Assign(Form1->Image2->Picture->Bitmap); else
   Form1->SpeedButton9->Glyph->Assign(Form1->Image1->Picture->Bitmap);

}
 void common()
{

hCommDev = CreateFile(Form3->port.c_str(), GENERIC_READ | GENERIC_WRITE,
0, NULL, OPEN_EXISTING, 0, NULL);
if (hCommDev != INVALID_HANDLE_VALUE) // sprawdza, czy port jest
// otwarty prawid³owo
{     /*
CommProp.dwProvSpec1 = COMMPROP_INITIALIZED;// inicjalizuje
// format danych
// us³ugi. Port
// szeregowy jest
// zawsze dostêpny
GetCommProperties(hCommDev, &CommProp);
GetCommMask(hCommDev, &fdwEvtMask);
SetCommMask(hCommDev, EV_TXEMPTY | EV_CTS);   */
dcb.DCBlength=sizeof(dcb);
GetCommState(hCommDev,&dcb);
dcb.BaudRate=CBR_57600;
dcb.EvtChar=1;
dcb.fParity=FALSE;
dcb.Parity=NOPARITY;
dcb.StopBits=ONESTOPBIT;
dcb.ByteSize=8;
dcb.fOutxCtsFlow=False;
dcb.fOutxDsrFlow=False;
dcb.fDtrControl=0;
dcb.fDsrSensitivity=0;
dcb.fRtsControl=0;
dcb.fDtrControl = DTR_CONTROL_ENABLE;
dcb.fRtsControl = RTS_CONTROL_DISABLE;
dcb.fOutxCtsFlow = FALSE;
dcb.fOutxDsrFlow = FALSE;
dcb.fDsrSensitivity = FALSE;
dcb.fAbortOnError = FALSE;
dcb.fOutX = FALSE;
dcb.fInX = FALSE;
SetCommState(hCommDev,&dcb);

   unsigned char buf[] = {0x55,0x01,'G',0xff,0x28};
  buf[4] = CountCRC(buf);

  unsigned long l = 0, i=0;
  do{
  Write_Comm(hCommDev,&buf,5);
  Read_Comm(hCommDev,&l,5);
  if((i++)==20)
   {
    Application->MessageBoxA("Wybrany port nie odpowiada. Zmieñ konfiguracje lub podl¹cz sterownik","Komunikacja nie nawiazana",MB_OK);
    break;
   }
  }while(l!=5);
  Form1->SpeedButton1->Down = Buffer_I[3] & 1;
  Form1->SpeedButton2->Down = Buffer_I[3] & 2;
  Form1->SpeedButton3->Down = Buffer_I[3] & 4;
  Form1->SpeedButton4->Down = Buffer_I[3] & 8;
  Form1->SpeedButton5->Down = Buffer_I[3] & 16;
  Form1->SpeedButton6->Down = Buffer_I[3] & 32;
  Form1->SpeedButton7->Down = Buffer_I[3] & 64;
  Form1->SpeedButton8->Down = Buffer_I[3] & 128;

  Form1->p1->Checked = Buffer_I[3] & 1;
  Form1->p2->Checked = Buffer_I[3] & 2;
  Form1->p3->Checked = Buffer_I[3] & 4;
  Form1->p4->Checked = Buffer_I[3] & 8;
  Form1->p5->Checked = Buffer_I[3] & 16;
  Form1->p6->Checked = Buffer_I[3] & 32;
  Form1->p7->Checked = Buffer_I[3] & 64;
  Form1->p8->Checked = Buffer_I[3] & 128;

graph();


}
else
{
switch ((int)hCommDev)
{
case IE_BADID:
ShowMessage("Niew³aœciwa nazwa portu lub port jest"
" aktywny.");
break;
};
 }
}

void ion(char przekaznik)
{
if(!passcheck) return;
if(przekaznik==0)
 {
  Form1->SpeedButton1->Down = true;
  Form1->p1->Checked = true;
  Form1->SpeedButton1->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 }else
if(przekaznik==1)
 {
  Form1->SpeedButton2->Down = true;
   Form1->p2->Checked = true;
   Form1->SpeedButton2->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 }else
if(przekaznik==2)
 {
  Form1->SpeedButton3->Down = true;
   Form1->p3->Checked = true;
   Form1->SpeedButton3->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 }else
if(przekaznik==3)
 {
  Form1->SpeedButton4->Down = true;
   Form1->p4->Checked = true;
   Form1->SpeedButton4->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 }else
if(przekaznik==4)
 {
  Form1->SpeedButton5->Down = true;
   Form1->p5->Checked = true;
   Form1->SpeedButton5->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 }else
if(przekaznik==5)
 {
  Form1->SpeedButton6->Down = true;
   Form1->p6->Checked = true;
   Form1->SpeedButton6->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 }else
if(przekaznik==6)
 {
  Form1->SpeedButton7->Down = true;
   Form1->p7->Checked = true;
   Form1->SpeedButton7->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 }else
if(przekaznik==7)
 {
  Form1->SpeedButton8->Down = true;
   Form1->p8->Checked = true;
   Form1->SpeedButton8->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  on(przekaznik);
 } allcheck();
}
void ioff(char przekaznik)
{
if(!passcheck) return;
if(przekaznik==0)
 {
  Form1->SpeedButton1->Down = false;
  Form1->p1->Checked = false;
  Form1->SpeedButton1->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }else
if(przekaznik==1)
 {
  Form1->SpeedButton2->Down = false;
  Form1->p2->Checked = false;
  Form1->SpeedButton2->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }else
if(przekaznik==2)
 {
  Form1->SpeedButton3->Down = false;
  Form1->p3->Checked = false;
  Form1->SpeedButton3->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }else
if(przekaznik==3)
 {
  Form1->SpeedButton4->Down = false;
  Form1->p4->Checked = false;
  Form1->SpeedButton4->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }else
if(przekaznik==4)
 {
  Form1->SpeedButton5->Down = false;
  Form1->p5->Checked = false;
  Form1->SpeedButton5->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }else
if(przekaznik==5)
 {
  Form1->SpeedButton6->Down = false;
  Form1->p6->Checked = false;
  Form1->SpeedButton6->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }else
if(przekaznik==6)
 {
  Form1->SpeedButton7->Down = false;
  Form1->p7->Checked = false;
  Form1->SpeedButton7->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }
if(przekaznik==7)
 {
  Form1->SpeedButton8->Down = false;
  Form1->p8->Checked = false;
  Form1->SpeedButton8->Glyph->Assign(Form1->Image1->Picture->Bitmap);
  off(przekaznik);
 }   allcheck();
}

void __fastcall TForm1::Ustawienia1Click(TObject *Sender)
{
Form2->ShowModal();
ustaw_nazwy_przyciskow();
//autostart();
if(Form2->CheckBox1->Checked)
 server->Active = true; else
 server->Active = false;
if(Form2->ComboBox2->Text!="")
 if(Form3->port!=Form2->ComboBox2->Text)
  {
    Form3->port = Form2->ComboBox2->Text;
    Close_Comm(hCommDev);
    common();
  }
}
//---------------------------------------------------------------------------
 void __fastcall SetMinimizeWindow(TMessage &Msg)
 {
   //TForm::Dispatch(Msg);
 }


void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 Close_Comm(hCommDev);
 zapiszczynnosciautomatyczne();
 zapisz_ustawienia();
 autostart();
 Application->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
 if(SpeedButton1->Down)
  {
   on(0x00);
   p1->Checked =true;
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&1");
   SpeedButton1->Glyph->Assign(Form1->Image2->Picture->Bitmap);
  } else
   {
    off(0x00);
    p1->Checked = false;
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&1");
     SpeedButton1->Glyph->Assign(Image1->Picture->Bitmap);
   } allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{
 if(SpeedButton9->Down)
  {
   allon();
   SpeedButton9->Glyph->Assign(Image2->Picture->Bitmap);
   all->Checked =true;
   SpeedButton1->Down = true;
   SpeedButton2->Down = true;
   SpeedButton3->Down = true;
   SpeedButton4->Down = true;
   SpeedButton5->Down = true;
   SpeedButton6->Down = true;
   SpeedButton7->Down = true;
   SpeedButton8->Down = true;
   p1->Checked = true;
   p2->Checked = true;
   p3->Checked = true;
   p4->Checked = true;
   p5->Checked = true;
   p6->Checked = true;
   p7->Checked = true;
   p8->Checked = true;
      if(dpolaczony)
    server->Socket->Connections[0]->SendText("allon");
  } else
   {
    alloff();
    SpeedButton9->Glyph->Assign(Image1->Picture->Bitmap);
    all->Checked = false;
       SpeedButton1->Down = false;
   SpeedButton2->Down = false;
   SpeedButton3->Down = false;
   SpeedButton4->Down = false;
   SpeedButton5->Down = false;
   SpeedButton6->Down = false;
   SpeedButton7->Down = false;
   SpeedButton8->Down = false;
   p1->Checked = false;
   p2->Checked = false;
   p3->Checked = false;
   p4->Checked = false;
   p5->Checked = false;
   p6->Checked = false;
   p7->Checked = false;
   p8->Checked = false;
       if(dpolaczony)
    server->Socket->Connections[0]->SendText("alloff");
   }  graph();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton10Click(TObject *Sender)
{
alloff();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
 if(SpeedButton2->Down)
  {
   on(0x01);
   p2->Checked =true;

   SpeedButton2->Glyph->Assign(Image2->Picture->Bitmap);
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&2");
  } else
   {
    off(0x01);
    p2->Checked = false;
    SpeedButton2->Glyph->Assign(Image1->Picture->Bitmap);
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&2");
   } allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
 if(SpeedButton3->Down)
  {
   on(0x02);
   p3->Checked =true;
   SpeedButton3->Glyph->Assign(Image2->Picture->Bitmap);
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&3");
  } else
   {
    off(0x02);
    p3->Checked = false;
    SpeedButton3->Glyph->Assign(Image1->Picture->Bitmap);
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&3");
   } allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
 if(SpeedButton4->Down)
  {
   on(0x03);
   p4->Checked =true;
   SpeedButton4->Glyph->Assign(Image2->Picture->Bitmap);
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&4");
  } else
   {
    off(0x03);
    p4->Checked = false;
    SpeedButton4->Glyph->Assign(Image1->Picture->Bitmap);
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&4");
   }  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
 if(SpeedButton5->Down)
  {
   on(0x04);
   p5->Checked =true;
   SpeedButton5->Glyph->Assign(Image2->Picture->Bitmap);
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&5");
  } else
   {
    off(0x04);
    p5->Checked = false;
    SpeedButton5->Glyph->Assign(Image1->Picture->Bitmap);
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&5");
   }  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
 if(SpeedButton6->Down)
  {
   on(0x05);
   p6->Checked =true;
   SpeedButton6->Glyph->Assign(Image2->Picture->Bitmap);
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&6");
  } else
   {
    off(0x05);
    p6->Checked = false;
    SpeedButton6->Glyph->Assign(Image1->Picture->Bitmap);
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&6");
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
 if(SpeedButton7->Down)
  {
   on(0x06);
   p7->Checked =true;
   SpeedButton7->Glyph->Assign(Image2->Picture->Bitmap);
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&7");
  } else
   {
    off(0x06);
    p7->Checked = false;
    SpeedButton7->Glyph->Assign(Image1->Picture->Bitmap);
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&7");
   }   allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
 if(SpeedButton8->Down)
  {
   on(0x07);
   p8->Checked =true;
   SpeedButton8->Glyph->Assign(Image2->Picture->Bitmap);
   if(dpolaczony)
   server->Socket->Connections[0]->SendText("on&8");
  } else
   {
    off(0x07);
    p8->Checked = false;
    SpeedButton8->Glyph->Assign(Image1->Picture->Bitmap);
    if(dpolaczony)
    server->Socket->Connections[0]->SendText("off&8");
   }  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
odczytajczynnosciautomatyczne();
odczytaj_ustawienia();

if(Form2->CheckBox1->Checked)
 server->Active = true; else
 server->Active = false;
if(Form2->CheckBox3->Checked)
 {
  ShowWindow(Application->Handle,  SW_MINIMIZE);
  ShowWindow(Application->Handle,  SW_HIDE);
  }
ustaw_nazwy_przyciskow();
common();  allcheck();
graph();

}
//---------------------------------------------------------------------------






void __fastcall TForm1::Glowneokno1Click(TObject *Sender)
{
  TrayIcon1->Visible=false;
 ShowWindow(Application->Handle, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zamknij1Click(TObject *Sender)
{
 Application->Terminate();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zamknij2Click(TObject *Sender)
{
 Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1Restore(TObject *Sender)
{
//  TrayIcon1->Visible=false;       
}
//---------------------------------------------------------------------------







void __fastcall TForm1::p1Click(TObject *Sender)
{
  if(p1->Checked)
   {
    p1->Checked = false;
    off(0x00);
    SpeedButton1->Down = false;
   }else
    {
     p1->Checked = true;
     on(0x00);
     SpeedButton1->Down = true;
    }

 graph(); allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::p2Click(TObject *Sender)
{
  if(p2->Checked)
   {
    p2->Checked = false;
    off(0x01);
    SpeedButton2->Down = false;
   }else
    {
     p2->Checked = true;
     on(0x01);
     SpeedButton2->Down = true;
    }
     graph();  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::p3Click(TObject *Sender)
{
  if(p3->Checked)
   {
    p3->Checked = false;
    off(0x02);
    SpeedButton3->Down = false;
   }else
    {
     p3->Checked = true;
     on(0x02);
     SpeedButton3->Down = true;
    }   graph();   allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::p4Click(TObject *Sender)
{
  if(p4->Checked)
   {
    p4->Checked = false;
    off(0x03);
    SpeedButton4->Down = false;
   }else
    {
     p4->Checked = true;
     on(0x03);
     SpeedButton4->Down = true;
    }   graph();  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::p5Click(TObject *Sender)
{
  if(p5->Checked)
   {
    p5->Checked = false;
    off(0x04);
    SpeedButton5->Down = false;
   }else
    {
     p5->Checked = true;
     on(0x04);
     SpeedButton5->Down = true;
    }   graph(); allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::p6Click(TObject *Sender)
{
  if(p6->Checked)
   {
    p6->Checked = false;
    off(0x05);
    SpeedButton6->Down = false;
   }else
    {
     p1->Checked = true;
     on(0x05);
     SpeedButton6->Down = true;
    }   graph();   allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::p7Click(TObject *Sender)
{
  if(p7->Checked)
   {
    p7->Checked = false;
    off(0x06);
    SpeedButton7->Down = false;
   }else
    {
     p7->Checked = true;
     on(0x06);
     SpeedButton7->Down = true;
    }   graph();   allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::p8Click(TObject *Sender)
{
  if(p8->Checked)
   {
    p8->Checked = false;
    off(0x07);
    SpeedButton8->Down = false;
   }else
    {
     p8->Checked = true;
     on(0x07);
     SpeedButton8->Down = true;
    }    graph();  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::allClick(TObject *Sender)
{
  if(all->Checked)
   {
    all->Checked = false;
    alloff();
    SpeedButton9->Down = false;
   SpeedButton1->Down = false;
   SpeedButton2->Down = false;
   SpeedButton3->Down = false;
   SpeedButton4->Down = false;
   SpeedButton5->Down = false;
   SpeedButton6->Down = false;
   SpeedButton7->Down = false;
   SpeedButton8->Down = false;
   p1->Checked = false;
   p2->Checked = false;
   p3->Checked = false;
   p4->Checked = false;
   p5->Checked = false;
   p6->Checked = false;
   p7->Checked = false;
   p8->Checked = false;
   }else
    {
     all->Checked = true;
     allon();
     SpeedButton9->Down = true;
        SpeedButton1->Down = true;
   SpeedButton2->Down = true;
   SpeedButton3->Down = true;
   SpeedButton4->Down = true;
   SpeedButton5->Down = true;
   SpeedButton6->Down = true;
   SpeedButton7->Down = true;
   SpeedButton8->Down = true;
   p1->Checked = true;
   p2->Checked = true;
   p3->Checked = true;
   p4->Checked = true;
   p5->Checked = true;
   p6->Checked = true;
   p7->Checked = true;
   p8->Checked = true;
    }  graph();
}
//---------------------------------------------------------------------------

void autooff(char i)
{
 switch(i){
  case 0:
         Form1->SpeedButton1->Down = false;
         Form1->p1->Checked = false;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&1");
         off(i);
         break;
  case 1:
         Form1->SpeedButton2->Down = false;
         Form1->p2->Checked = false;
          if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&2");
         off(i);
         break;
  case 2:
         Form1->SpeedButton3->Down = false;
         Form1->p3->Checked = false;
          if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&3");
         off(i);
         break;
  case 3:
         Form1->SpeedButton4->Down = false;
         Form1->p4->Checked = false;
          if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&4");
         off(i);
         break;
  case 4:
         Form1->SpeedButton5->Down = false;
         Form1->p5->Checked = false;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&5");
         off(i);
         break;
  case 5:
         Form1->SpeedButton6->Down = false;
         Form1->p6->Checked = false;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&6");
         off(i);
         break;
  case 6:
         Form1->SpeedButton7->Down = false;
         Form1->p7->Checked = false;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&7");
         off(i);
         break;
  case 7:
         Form1->SpeedButton8->Down = false;
         Form1->p8->Checked = false;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("off&8");
         off(i);
         break;
  } allcheck();
}
void autoon(char i)
{
 switch(i){
  case 0:
         Form1->SpeedButton1->Down = true;
         Form1->p1->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&1");
         on(i);
         break;
  case 1:
         Form1->SpeedButton2->Down = true;
         Form1->p2->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&2");
         on(i);
         break;
  case 2:
         Form1->SpeedButton3->Down = true;
         Form1->p3->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&3");
         on(i);
         break;
  case 3:
         Form1->SpeedButton4->Down = true;
         Form1->p4->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&4");
         on(i);
         break;
  case 4:
         Form1->SpeedButton5->Down = true;
         Form1->p5->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&5");
         on(i);
         break;
  case 5:
         Form1->SpeedButton6->Down = true;
         Form1->p6->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&6");
         on(i);
         break;
  case 6:
         Form1->SpeedButton7->Down = true;
         Form1->p7->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&7");
         on(i);
         break;
  case 7:
         Form1->SpeedButton8->Down = true;
         Form1->p8->Checked = true;
         if(dpolaczony)
           Form1->server->Socket->Connections[0]->SendText("on&8");
         on(i);
         break;
  }  allcheck();
}
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    time_t timer;
   struct tm *tblock;

   /* gets time of day */
   timer = time(NULL);

   /* converts date/time to a structure */
   tblock = localtime(&timer);
 //  AnsiString date = tblock->tm_wday;
   for(int x = 0;x<8;x++)
    for(int y = 0;y<max_czynnosci;y++)
     if(Form3->czynnosci[x]>0)
         if(Form3->przekazniki[x].czynnosc[y].tylkowtedy)
          {
           if((Form3->przekazniki[x].czynnosc[y].tg==tblock->tm_hour)&&
               (Form3->przekazniki[x].czynnosc[y].tm==tblock->tm_min)&&
               (Form3->przekazniki[x].czynnosc[y].ts==tblock->tm_sec)&&
               (Form3->przekazniki[x].czynnosc[y].dzien==tblock->tm_mday)&&
               (Form3->przekazniki[x].czynnosc[y].miesiac==tblock->tm_mon+1)&&
               (Form3->przekazniki[x].czynnosc[y].rok==tblock->tm_year+1900))
                   if(Form3->przekazniki[x].czynnosc[y].wlacz)
                    {
                     autoon(x);
                    }else
                     {
                      autooff(x);
                     }
          }else
           if((Form3->przekazniki[x].czynnosc[y].g==tblock->tm_hour)&&
              (Form3->przekazniki[x].czynnosc[y].m==tblock->tm_min)&&
              (Form3->przekazniki[x].czynnosc[y].s==tblock->tm_sec))
               if(((Form3->przekazniki[x].czynnosc[y].pon)&&(tblock->tm_wday==1))||
                  ((Form3->przekazniki[x].czynnosc[y].wt)&&(tblock->tm_wday==2))||
                  ((Form3->przekazniki[x].czynnosc[y].sr)&&(tblock->tm_wday==3))||
                  ((Form3->przekazniki[x].czynnosc[y].czw)&&(tblock->tm_wday==4))||
                  ((Form3->przekazniki[x].czynnosc[y].pia)&&(tblock->tm_wday==5))||
                  ((Form3->przekazniki[x].czynnosc[y].sob)&&(tblock->tm_wday==6))||
                  ((Form3->przekazniki[x].czynnosc[y].nie)&&(tblock->tm_wday==0)))
                   if(Form3->przekazniki[x].czynnosc[y].wlacz)
                   {
                    autoon(x);
                   }else
                    {
                     autooff(x);
                    }



}
//---------------------------------------------------------------------------








void __fastcall TForm1::Oprogramie1Click(TObject *Sender)
{
 Form4->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
Image1->Picture->Bitmap->Transparent = true;
Image1->Picture->Bitmap->TransparentMode=tmFixed;
Image2->Picture->Bitmap->TransparentColor = clWhite;
Image2->Transparent = true;
Image2->Picture->Bitmap->TransparentMode=tmFixed;
passcheck = false;
dpolaczony = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::serverClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
AnsiString komenda = Socket->ReceiveText();
  if(komenda=="") return;
 AnsiString kom = eparametr(komenda,0);
 if(kom=="") return;
  if (kom=="./password")
  {
    if(parametr_count(komenda)!=2)
     {
      Socket->Close();
      return;
     }
    if(eparametr(komenda,1)!=Form2->LabeledEdit1->Text)
      {
       passcheck = false;
       Socket->Close();
  //     server->Socket->SendText("password incorrect");
      }else
      {
       passcheck = true;
       AnsiString nazwy = "./nazwy&"; nazwy += SpeedButton1->Caption; nazwy+='&';
       nazwy += SpeedButton2->Caption; nazwy+='&';
       nazwy += SpeedButton3->Caption; nazwy+='&';
       nazwy += SpeedButton4->Caption; nazwy+='&';
       nazwy += SpeedButton5->Caption; nazwy+='&';
       nazwy += SpeedButton6->Caption; nazwy+='&';
       nazwy += SpeedButton7->Caption; nazwy+='&';
       nazwy += SpeedButton8->Caption; nazwy+='&';

   if(SpeedButton1->Down)
    nazwy += "1&";else
    nazwy += "0&";
   if(SpeedButton2->Down)
    nazwy += "1&";else
    nazwy += "0&";
   if(SpeedButton3->Down)
    nazwy += "1&";else
    nazwy += "0&";
   if(SpeedButton4->Down)
    nazwy += "1&";else
    nazwy += "0&";
   if(SpeedButton5->Down)
    nazwy += "1&";else
    nazwy += "0&";
   if(SpeedButton6->Down)
    nazwy += "1&";else
    nazwy += "0&";
   if(SpeedButton7->Down)
    nazwy += "1&";else
    nazwy += "0&";
   if(SpeedButton8->Down)
    nazwy += "1";else
    nazwy += "0";
       Socket->SendText(nazwy);
      }
   return;
  }
  if ((kom=="on")&&(parametr_count(komenda)==2))
  {
     if(eparametr(komenda,1)=="1")
      ion(0x00);else
     if(eparametr(komenda,1)=="2")
      ion(0x01);else
     if(eparametr(komenda,1)=="3")
      ion(0x02);else
     if(eparametr(komenda,1)=="4")
      ion(0x03);else
     if(eparametr(komenda,1)=="5")
      ion(0x04);else
     if(eparametr(komenda,1)=="6")
      ion(0x05);else
     if(eparametr(komenda,1)=="7")
      ion(0x06);else
     if(eparametr(komenda,1)=="8")
      ion(0x07);
  return;
  }
  if ((kom=="off")&&(parametr_count(komenda)==2))
  {
     if(eparametr(komenda,1)=="1")
      ioff(0x00);else
     if(eparametr(komenda,1)=="2")
      ioff(0x01);else
     if(eparametr(komenda,1)=="3")
      ioff(0x02);else
     if(eparametr(komenda,1)=="4")
      ioff(0x03);else
     if(eparametr(komenda,1)=="5")
      ioff(0x04);else
     if(eparametr(komenda,1)=="6")
      ioff(0x05);else
     if(eparametr(komenda,1)=="7")
      ioff(0x06);else
     if(eparametr(komenda,1)=="8")
      ioff(0x07);
  return;
  }
  if (kom=="allon")
  {
   if(!passcheck) return;
   ion(0x00);
   ion(0x01);
   ion(0x02);
   ion(0x03);
   ion(0x04);
   ion(0x05);
   ion(0x06);
   ion(0x07);
   Form1->SpeedButton9->Glyph->Assign(Image2->Picture->Bitmap);
   Form1->SpeedButton9->Down = true;
   return;
  }
  if (kom=="alloff")
  {
   if(!passcheck) return;
   ioff(0x00);
   ioff(0x01);
   ioff(0x02);
   ioff(0x03);
   ioff(0x04);
   ioff(0x05);
   ioff(0x06);
   ioff(0x07);
   Form1->SpeedButton9->Glyph->Assign(Image1->Picture->Bitmap);
   Form1->SpeedButton9->Down = false;
   return;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::serverClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   dpolaczony=true;       
}
//---------------------------------------------------------------------------

void __fastcall TForm1::serverClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
 dpolaczony = false;
 passcheck = false;       
}
//---------------------------------------------------------------------------

void __fastcall TForm1::serverClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
 ErrorCode = 0;
}
//---------------------------------------------------------------------------



