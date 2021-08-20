//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include "unit3.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TComboBox *ComboBox2;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox1;
        TLabeledEdit *LabeledEdit1;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
        TComboBox *ComboBox1;
        TListBox *ListBox1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Dodajczynno1;
        TMenuItem *Usunczynnosc1;
        TComboBox *ComboBox3;
        TEdit *Edit1;
        TSpeedButton *SpeedButton1;
        TGroupBox *GroupBox5;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TMenuItem *N1;
        TMenuItem *Usunwszystkie1;
        void __fastcall Dodajczynno1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Usunwszystkie1Click(TObject *Sender);
        void __fastcall Usunczynnosc1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
