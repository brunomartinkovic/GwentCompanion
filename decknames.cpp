
// ************************************************************************************************************************** //
//                                                                                                                          
//                                                     XML Data Binding                                                     
//                                                                                                                          
//         Generated on: 3/10/2021 10:27:19 AM                                                                              
//       Generated from: C:\Bruno\Fakultet\Završni\Gwent Guide-20210301T194706Z-001\Gwent Guide\Win32\Debug\decknames.xml   
//   Settings stored in: C:\Bruno\Fakultet\Završni\Gwent Guide-20210301T194706Z-001\Gwent Guide\Win32\Debug\decknames.xdb   
//                                                                                                                          
// ************************************************************************************************************************** //

#include <System.hpp>
#pragma hdrstop

#include "decknames.h"


// Global Functions 

_di_IXMLmadeType __fastcall Getmade(Xml::Xmlintf::_di_IXMLDocument Doc)
{
  return (_di_IXMLmadeType) Doc->GetDocBinding("made", __classid(TXMLmadeType), TargetNamespace);
};

_di_IXMLmadeType __fastcall Getmade(Xml::Xmldoc::TXMLDocument *Doc)
{
  Xml::Xmlintf::_di_IXMLDocument DocIntf;
  Doc->GetInterface(DocIntf);
  return Getmade(DocIntf);
};

_di_IXMLmadeType __fastcall Loadmade(const System::UnicodeString& FileName)
{
  return (_di_IXMLmadeType) Xml::Xmldoc::LoadXMLDocument(FileName)->GetDocBinding("made", __classid(TXMLmadeType), TargetNamespace);
};

_di_IXMLmadeType __fastcall  Newmade()
{
  return (_di_IXMLmadeType) Xml::Xmldoc::NewXMLDocument()->GetDocBinding("made", __classid(TXMLmadeType), TargetNamespace);
};

// TXMLmadeType 

void __fastcall TXMLmadeType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("deck"), __classid(TXMLdeckType));
  ItemTag = "deck";
  ItemInterface = __uuidof(IXMLdeckType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

_di_IXMLdeckType __fastcall TXMLmadeType::Get_deck(int Index)
{
  return (_di_IXMLdeckType) List->Nodes[Index];
};

_di_IXMLdeckType __fastcall TXMLmadeType::Add()
{
  return (_di_IXMLdeckType) AddItem(-1);
};

_di_IXMLdeckType __fastcall TXMLmadeType::Insert(const int Index)
{
  return (_di_IXMLdeckType) AddItem(Index);
};

// TXMLdeckType 

System::UnicodeString __fastcall TXMLdeckType::Get_name()
{
  return GetChildNodes()->Nodes[System::UnicodeString("name")]->Text;
};

void __fastcall TXMLdeckType::Set_name(System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("name")]->NodeValue = Value;
};

int __fastcall TXMLdeckType::Get_leader()
{
  return GetChildNodes()->Nodes[System::UnicodeString("leader")]->NodeValue.operator int();
};

void __fastcall TXMLdeckType::Set_leader(int Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("leader")]->NodeValue = Value;
};

int __fastcall TXMLdeckType::Get_skin()
{
  return GetChildNodes()->Nodes[System::UnicodeString("skin")]->NodeValue.operator int();
};

void __fastcall TXMLdeckType::Set_skin(int Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("skin")]->NodeValue = Value;
};
