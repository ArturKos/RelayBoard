//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "trayicon.h"
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton6;
        TSpeedButton *SpeedButton7;
        TSpeedButton *SpeedButton8;
        TMainMenu *MainMenu1;
        TMenuItem *Ustawienia1;
        TMenuItem *Pomoc1;
        TMenuItem *Oprogramie1;
        TSpeedButton *SpeedButton9;
        TImage *Image1;
        TImage *Image2;
        TTrayIcon *TrayIcon1;
        TPopupMenu *PopupMenu1;
        TMenuItem *p1;
        TMenuItem *p2;
        TMenuItem *p3;
        TMenuItem *p4;
        TMenuItem *p5;
        TMenuItem *p6;
        TMenuItem *p7;
        TMenuItem *p8;
        TMenuItem *N1;
        TMenuItem *all;
        TMenuItem *N2;
        TMenuItem *Zamknij1;
        TServerSocket *server;
        TTimer *Timer1;
        TTimer *Timer2;
        TTimer *Timer3;
        TTimer *Timer4;
        TTimer *Timer5;
        TTimer *Timer6;
        TTimer *Timer7;
        TTimer *Timer8;
        TTimer *Timer9;
        void __fastcall Ustawienia1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton9Click(TObject *Sender);
        void __fastcall SpeedButton10Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall SpeedButton7Click(TObject *Sender);
        void __fastcall SpeedButton8Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Glowneokno1Click(TObject *Sender);
        void __fastcall Zamknij1Click(TObject *Sender);
        void __fastcall Zamknij2Click(TObject *Sender);
        void __fastcall TrayIcon1Restore(TObject *Sender);
        void __fastcall p1Click(TObject *Sender);
        void __fastcall p2Click(TObject *Sender);
        void __fastcall p3Click(TObject *Sender);
        void __fastcall p4Click(TObject *Sender);
        void __fastcall p5Click(TObject *Sender);
        void __fastcall p6Click(TObject *Sender);
        void __fastcall p7Click(TObject *Sender);
        void __fastcall p8Click(TObject *Sender);
        void __fastcall allClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Oprogramie1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall serverClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall serverClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
private:	// User declarations

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
