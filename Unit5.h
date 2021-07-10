//---------------------------------------------------------------------------
#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
	TImage *Skin;
	TComboBox *Decks;
	TADOQuery *QDeck;
	TXMLDocument *Xuser;
	TListView *Deck;
	TEdit *Msg;
	TListBox *Chat;
	TIdTCPServer *Server;
	TIdTCPClient *Clients;
	TImage *Card1;
	TImage *Card2;
	TImage *Card3;
	TImage *Card4;
	TImage *Card5;
	TImage *Card6;
	TImage *MPlayed1;
	TImage *MPlayed2;
	TImage *MPlayed3;
	TImage *MPlayed4;
	TImage *MPlayed5;
	TImage *MPlayed6;
	TImage *OMPlayed1;
	TImage *OMPlayed2;
	TImage *OMPlayed3;
	TImage *OMPlayed4;
	TImage *OMPlayed5;
	TImage *OMPlayed6;
	TImage *OCard1;
	TImage *SPlayed1;
	TImage *OSPlayed3;
	TImage *ORPlayed3;
	TImage *Hover;
	TImage *RPlayed2;
	TImage *RPlayed3;
	TImage *RPlayed4;
	TImage *RPlayed5;
	TImage *RPlayed6;
	TImage *RPlayed1;
	TImage *SPlayed2;
	TImage *SPlayed3;
	TImage *SPlayed5;
	TImage *SPlayed4;
	TImage *SPlayed6;
	TImage *ORPlayed4;
	TImage *ORPlayed6;
	TImage *ORPlayed5;
	TImage *ORPlayed2;
	TImage *ORPlayed1;
	TImage *OSPlayed4;
	TImage *OSPlayed5;
	TImage *OSPlayed6;
	TImage *OSPlayed2;
	TImage *OSPlayed1;
	TImage *OCard2;
	TImage *OCard4;
	TImage *OCard5;
	TImage *OCard3;
	TImage *OCard6;
	TLabel *AS;
	TLabel *AR;
	TLabel *AM;
	TLabel *EM;
	TLabel *ER;
	TLabel *ES;
	TLabel *EScore;
	TLabel *AScore;
	TImage *ELeader;
	TImage *ALeader;
	TImage *Leader;
	TImage *ASkin;
	TImage *ESkin;
	TLabel *HoverPosition;
	TLabel *HoverName;
	TLabel *Turn;
	TImage *Background;
	TLabel *HoverFlavor;
	TImage *Exit;
	TLabel *ExitL;
	TImage *Coin;
	TImage *Send;
	TLabel *SendL;
	TImage *A;
	TImage *E;
	TADOConnection *DConnect;
	TImage *StReport;
	TImage *PReport;
	TLabel *StReportL;
	TLabel *PReportL;
	TImage *Server1;
	TLabel *Server1L;
	TImage *Local;
	TLabel *LocalL;
	TImage *Create;
	TLabel *CreateL;
	TImage *Server2;
	TLabel *Server2L;
	void __fastcall DecksChange(TObject *Sender);
	void __fastcall SendClick(TObject *Sender);
	void __fastcall Card1Click(TObject *Sender);
	void __fastcall ServerExecute(TIdContext *AContext);
	void __fastcall Card2Click(TObject *Sender);
	void __fastcall Card3Click(TObject *Sender);
	void __fastcall Card4Click(TObject *Sender);
	void __fastcall Card5Click(TObject *Sender);
	void __fastcall Card6Click(TObject *Sender);
	void __fastcall Card1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Card1MouseLeave(TObject *Sender);
	void __fastcall Card2MouseLeave(TObject *Sender);
	void __fastcall Card2MouseEnter(TObject *Sender);
	void __fastcall Card3MouseEnter(TObject *Sender);
	void __fastcall Card3MouseLeave(TObject *Sender);
	void __fastcall Card4MouseEnter(TObject *Sender);
	void __fastcall Card4MouseLeave(TObject *Sender);
	void __fastcall Card5MouseLeave(TObject *Sender);
	void __fastcall Card5MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Card6MouseLeave(TObject *Sender);
	void __fastcall Card6MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall EndTurnClick(TObject *Sender);
	void __fastcall ALeaderClick(TObject *Sender);
	void __fastcall MPlayed1MouseLeave(TObject *Sender);
	void __fastcall MPlayed2MouseLeave(TObject *Sender);
	void __fastcall MPlayed2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MPlayed3MouseLeave(TObject *Sender);
	void __fastcall MPlayed3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MPlayed4MouseLeave(TObject *Sender);
	void __fastcall MPlayed4MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MPlayed5MouseLeave(TObject *Sender);
	void __fastcall MPlayed5MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MPlayed6MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MPlayed6MouseLeave(TObject *Sender);
	void __fastcall RPlayed1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall RPlayed1MouseLeave(TObject *Sender);
	void __fastcall RPlayed2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall RPlayed2MouseLeave(TObject *Sender);
	void __fastcall RPlayed3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall RPlayed3MouseLeave(TObject *Sender);
	void __fastcall RPlayed4MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall RPlayed4MouseLeave(TObject *Sender);
	void __fastcall RPlayed5MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall RPlayed5MouseLeave(TObject *Sender);
	void __fastcall RPlayed6MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall RPlayed6MouseLeave(TObject *Sender);
	void __fastcall SPlayed1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SPlayed1MouseLeave(TObject *Sender);
	void __fastcall SPlayed2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SPlayed2MouseLeave(TObject *Sender);
	void __fastcall SPlayed3MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SPlayed3MouseLeave(TObject *Sender);
	void __fastcall SPlayed4MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SPlayed4MouseLeave(TObject *Sender);
	void __fastcall SPlayed5MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SPlayed5MouseLeave(TObject *Sender);
	void __fastcall SPlayed6MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SPlayed6MouseLeave(TObject *Sender);
	void __fastcall MPlayed1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ALeaderMouseEnter(TObject *Sender);
	void __fastcall ALeaderMouseLeave(TObject *Sender);
	void __fastcall ELeaderMouseEnter(TObject *Sender);
	void __fastcall ELeaderMouseLeave(TObject *Sender);
	void __fastcall ExitClick(TObject *Sender);
	void __fastcall CoinClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall StReportClick(TObject *Sender);
	void __fastcall PReportClick(TObject *Sender);
	void __fastcall Server1Click(TObject *Sender);
	void __fastcall LocalClick(TObject *Sender);
	void __fastcall CreateClick(TObject *Sender);
	void __fastcall Server2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif






















































