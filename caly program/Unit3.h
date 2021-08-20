//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#define max_czynnosci 100
 struct akcja{
bool wlacz,pon,wt,sr,czw,pia,sob,nie,tylkowtedy;
unsigned char g,m,s,tg,tm,ts,dzien,miesiac;
unsigned int rok;
};

struct przekaznik{
struct akcja czynnosc[max_czynnosci];
bool timer;
unsigned int i_g,i_m,i_s;
unsigned int n_g,n_m,n_s;
};


//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TComboBox *ComboBox1;
        TGroupBox *GroupBox2;
        TCSpinEdit *CSpinEdit1;
        TCSpinEdit *CSpinEdit2;
        TCSpinEdit *CSpinEdit3;
        TGroupBox *GroupBox3;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TGroupBox *GroupBox4;
        TCheckBox *CheckBox8;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox6;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit4;
        TLabeledEdit *LabeledEdit5;
        TLabeledEdit *LabeledEdit6;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TGroupBox *GroupBox7;
        TCheckBox *CheckBox9;
        TGroupBox *GroupBox8;
        TGroupBox *GroupBox9;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TGroupBox *GroupBox10;
        TCheckBox *CheckBox10;
        TGroupBox *GroupBox11;
        TGroupBox *GroupBox12;
        TEdit *Edit7;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TEdit *Edit11;
        TEdit *Edit12;
        void __fastcall CheckBox8Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
        struct przekaznik przekazniki[8];
        unsigned char  edit;
        AnsiString port;
        AnsiString nazwy_przekaznikow[8];
        unsigned char czynnosci[8];

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
