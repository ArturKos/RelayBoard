//---------------------------------------------------------------------------
 #include <time.h>
#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------



__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TForm3::CheckBox8Click(TObject *Sender)
{
CheckBox1->Enabled = !CheckBox8->Checked;
CheckBox2->Enabled = !CheckBox8->Checked;
CheckBox3->Enabled = !CheckBox8->Checked;
CheckBox4->Enabled = !CheckBox8->Checked;
CheckBox5->Enabled = !CheckBox8->Checked;
CheckBox6->Enabled = !CheckBox8->Checked;
CheckBox7->Enabled = !CheckBox8->Checked;
CSpinEdit1->Enabled =  !CheckBox8->Checked;
CSpinEdit2->Enabled =  !CheckBox8->Checked;
CSpinEdit3->Enabled =  !CheckBox8->Checked;

LabeledEdit1->Enabled = CheckBox8->Checked;
LabeledEdit2->Enabled = CheckBox8->Checked;
LabeledEdit3->Enabled = CheckBox8->Checked;
LabeledEdit4->Enabled = CheckBox8->Checked;
LabeledEdit5->Enabled = CheckBox8->Checked;
LabeledEdit6->Enabled = CheckBox8->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormActivate(TObject *Sender)
{
CheckBox1->Enabled = !CheckBox8->Checked;
CheckBox2->Enabled = !CheckBox8->Checked;
CheckBox3->Enabled = !CheckBox8->Checked;
CheckBox4->Enabled = !CheckBox8->Checked;
CheckBox5->Enabled = !CheckBox8->Checked;
CheckBox6->Enabled = !CheckBox8->Checked;
CheckBox7->Enabled = !CheckBox8->Checked;
CSpinEdit1->Enabled =  !CheckBox8->Checked;
CSpinEdit2->Enabled =  !CheckBox8->Checked;
CSpinEdit3->Enabled =  !CheckBox8->Checked;

LabeledEdit1->Enabled = CheckBox8->Checked;
LabeledEdit2->Enabled = CheckBox8->Checked;
LabeledEdit3->Enabled = CheckBox8->Checked;
LabeledEdit4->Enabled = CheckBox8->Checked;
LabeledEdit5->Enabled = CheckBox8->Checked;
LabeledEdit6->Enabled = CheckBox8->Checked;
    time_t timer;
   struct tm *tblock;

   /* gets time of day */
   timer = time(NULL);

   /* converts date/time to a structure */
   tblock = localtime(&timer);
   CSpinEdit1->Value = tblock->tm_hour;
   CSpinEdit2->Value = tblock->tm_min;
   CSpinEdit3->Value = tblock->tm_sec;
      LabeledEdit1->Text = tblock->tm_hour;
   LabeledEdit2->Text = tblock->tm_min;
   LabeledEdit3->Text = tblock->tm_sec;
   LabeledEdit4->Text = tblock->tm_mday;
   LabeledEdit5->Text = tblock->tm_mon+1;
   LabeledEdit6->Text = tblock->tm_year + 1900;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::SpeedButton2Click(TObject *Sender)
{
Form3->Close();
}
//---------------------------------------------------------------------------




void __fastcall TForm3::SpeedButton1Click(TObject *Sender)
{
if((!CheckBox1->Checked)&&(!CheckBox2->Checked)&&(!CheckBox3->Checked)&&
    (!CheckBox4->Checked)&&(!CheckBox5->Checked)&&(!CheckBox6->Checked)&&
    (!CheckBox7->Checked)&&(!CheckBox8->Checked)) return;
if(Form3->czynnosci[Form3->edit]<max_czynnosci)
 try
 {

  if(ComboBox1->Text=="Wlacz")
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].wlacz = true;else
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].wlacz = false;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].pon = CheckBox1->Checked;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].wt = CheckBox2->Checked;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].sr = CheckBox3->Checked;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].czw = CheckBox4->Checked;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].pia = CheckBox5->Checked;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].sob = CheckBox6->Checked;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].nie = CheckBox7->Checked;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].g = CSpinEdit1->Value;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].m = CSpinEdit2->Value;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].s = CSpinEdit3->Value;
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].tylkowtedy = CheckBox8->Checked;
  if(LabeledEdit1->Text!="")
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].tg = LabeledEdit1->Text.ToInt();
  if(LabeledEdit2->Text!="")
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].tm = LabeledEdit2->Text.ToInt();
  if(LabeledEdit3->Text!="")
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].ts = LabeledEdit3->Text.ToInt();
  if(LabeledEdit4->Text!="")
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].dzien = LabeledEdit4->Text.ToInt();
  if(LabeledEdit5->Text!="")
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].miesiac = LabeledEdit5->Text.ToInt();
  if(LabeledEdit6->Text!="")
  Form3->przekazniki[Form3->edit].czynnosc[Form3->czynnosci[Form3->edit]].rok = LabeledEdit6->Text.ToInt();
   Form3->czynnosci[Form3->edit]++;
 }
 catch(...){};
 Form3->Close();
}
//---------------------------------------------------------------------------



