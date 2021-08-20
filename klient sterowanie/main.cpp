//---------------------------------------------------------------------------

#include <vcl.h>
#include "soc.cpp"
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool polaczony;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void allcheck()
{
 if((Form1->SpeedButton1->Down)&&
    (Form1->SpeedButton9->Down)&&
    (Form1->SpeedButton3->Down)&&
    (Form1->SpeedButton4->Down)&&
    (Form1->SpeedButton5->Down)&&
    (Form1->SpeedButton6->Down)&&
    (Form1->SpeedButton7->Down)&&
    (Form1->SpeedButton8->Down)){ Form1->SpeedButton10->Down = true;
                                  } else
    { Form1->SpeedButton10->Down = false;
                              }
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
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
 if(client->Active)
  {
    client->Active = false;
    SpeedButton2->Caption = "Polacz";
  }else
   {
    client->Host = LabeledEdit1->Text;
    client->Active = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::clientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    ErrorCode = 0;
    client->Active = false;
    SpeedButton2->Caption = "Polacz";     
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton1->Down)
client->Socket->SendText("on&1");else
client->Socket->SendText("off&1"); allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::clientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
polaczony = true;
    SpeedButton2->Caption = "Rozlacz";
    AnsiString t = "./password&";
    t+=LabeledEdit2->Text;
    client->Socket->SendText(t);      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::clientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
polaczony = false;
    client->Active = false;
    SpeedButton2->Caption = "Polacz";  
}
//---------------------------------------------------------------------------


void __fastcall TForm1::clientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
 AnsiString komenda = Socket->ReceiveText();
  if(komenda=="") return;
 AnsiString kom = eparametr(komenda,0);
 if(kom=="") return;

  if ((kom=="./nazwy")&&(parametr_count(komenda)==17))
  {
   SpeedButton1->Caption = eparametr(komenda,1);
   SpeedButton3->Caption = eparametr(komenda,2);
   SpeedButton4->Caption = eparametr(komenda,3);
   SpeedButton5->Caption = eparametr(komenda,4);
   SpeedButton6->Caption = eparametr(komenda,5);
   SpeedButton7->Caption = eparametr(komenda,6);
   SpeedButton8->Caption = eparametr(komenda,7);
   SpeedButton9->Caption = eparametr(komenda,8);
   if(eparametr(komenda,9)=="1")
    SpeedButton1->Down = true; else SpeedButton1->Down = false;
   if(eparametr(komenda,10)=="1")
    SpeedButton3->Down = true; else SpeedButton3->Down = false;
   if(eparametr(komenda,11)=="1")
    SpeedButton4->Down = true; else SpeedButton4->Down = false;
   if(eparametr(komenda,12)=="1")
    SpeedButton5->Down = true; else SpeedButton5->Down = false;
    if(eparametr(komenda,13)=="1")
    SpeedButton6->Down = true; else SpeedButton6->Down = false;
   if(eparametr(komenda,14)=="1")
    SpeedButton7->Down = true; else SpeedButton7->Down = false;
   if(eparametr(komenda,15)=="1")
    SpeedButton8->Down = true; else SpeedButton8->Down = false;
   if(eparametr(komenda,16)=="1")
    SpeedButton9->Down = true; else SpeedButton9->Down = false;  allcheck();
   return;
  }
 if ((kom=="on")&&(parametr_count(komenda)==2))
  {
   if(eparametr(komenda,1)=="1")
    SpeedButton1->Down = true; else
   if(eparametr(komenda,1)=="2")
    SpeedButton3->Down = true; else
   if(eparametr(komenda,1)=="3")
    SpeedButton4->Down = true; else
   if(eparametr(komenda,1)=="4")
    SpeedButton5->Down = true; else
   if(eparametr(komenda,1)=="5")
    SpeedButton6->Down = true; else
   if(eparametr(komenda,1)=="6")
    SpeedButton7->Down = true; else
   if(eparametr(komenda,1)=="7")
    SpeedButton8->Down = true; else
   if(eparametr(komenda,1)=="7")
    SpeedButton9->Down = true; allcheck();
    return;
  }
 if ((kom=="off")&&(parametr_count(komenda)==2))
  {
   if(eparametr(komenda,1)=="1")
    SpeedButton1->Down = false; else
   if(eparametr(komenda,1)=="2")
    SpeedButton3->Down = false; else
   if(eparametr(komenda,1)=="3")
    SpeedButton4->Down = false; else
   if(eparametr(komenda,1)=="4")
    SpeedButton5->Down = false; else
   if(eparametr(komenda,1)=="5")
    SpeedButton6->Down = false; else
   if(eparametr(komenda,1)=="6")
    SpeedButton7->Down = false; else
   if(eparametr(komenda,1)=="7")
    SpeedButton8->Down = false; else
   if(eparametr(komenda,1)=="8")
    SpeedButton9->Down = false;  allcheck();
    return;
  }
 if (kom=="alloff")
  {
   SpeedButton1->Down = false;
   SpeedButton3->Down = false;
   SpeedButton4->Down = false;
   SpeedButton5->Down = false;
   SpeedButton6->Down = false;
   SpeedButton7->Down = false;
   SpeedButton8->Down = false;
   SpeedButton9->Down = false;
   SpeedButton10->Down = false;
   allcheck();
   return;
  }
 if (kom=="allon")
  {
   SpeedButton1->Down = true;
   SpeedButton3->Down = true;
   SpeedButton4->Down = true;
   SpeedButton5->Down = true;
   SpeedButton6->Down = true;
   SpeedButton7->Down = true;
   SpeedButton8->Down = true;
   SpeedButton9->Down = true;
   SpeedButton10->Down = true;
    allcheck();
   return;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton3->Down)
client->Socket->SendText("on&2");else
client->Socket->SendText("off&2");  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton4->Down)
client->Socket->SendText("on&3");else
client->Socket->SendText("off&3");  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton5->Down)
client->Socket->SendText("on&4");else
client->Socket->SendText("off&4");  allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton6->Down)
client->Socket->SendText("on&5");else
client->Socket->SendText("off&5"); allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton7->Down)
client->Socket->SendText("on&6");else
client->Socket->SendText("off&6"); allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton8->Down)
client->Socket->SendText("on&7");else
client->Socket->SendText("off&7"); allcheck();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton10Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton10->Down)
{
client->Socket->SendText("allon");
SpeedButton1->Down = true;
SpeedButton3->Down = true;
SpeedButton4->Down = true;
SpeedButton5->Down = true;
SpeedButton6->Down = true;
SpeedButton7->Down = true;
SpeedButton8->Down = true;
SpeedButton9->Down = true;
 }else
 {
  client->Socket->SendText("alloff");
  SpeedButton1->Down = false;
SpeedButton3->Down = false;
SpeedButton4->Down = false;
SpeedButton5->Down = false;
SpeedButton6->Down = false;
SpeedButton7->Down = false;
SpeedButton8->Down = false;
SpeedButton9->Down = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{
if(!polaczony) return;
if(SpeedButton9->Down)
client->Socket->SendText("on&8");else
client->Socket->SendText("off&8"); allcheck();
}
//---------------------------------------------------------------------------


