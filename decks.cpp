
// ******************************************************************************************* //
//                                                                                           
//                                     XML Data Binding                                      
//                                                                                           
//         Generated on: 17/05/2020 21:49:51                                                 
//       Generated from: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\Win32\Debug\decks.xml   
//   Settings stored in: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\Win32\Debug\decks.xdb   
//                                                                                           
// ******************************************************************************************* //

#include <System.hpp>
#pragma hdrstop

#include "decks.h"


// Global Functions 

_di_IXMLdecksType __fastcall Getdecks(Xml::Xmlintf::_di_IXMLDocument Doc)
{
  return (_di_IXMLdecksType) Doc->GetDocBinding("decks", __classid(TXMLdecksType), TargetNamespace);
};

_di_IXMLdecksType __fastcall Getdecks(Xml::Xmldoc::TXMLDocument *Doc)
{
  Xml::Xmlintf::_di_IXMLDocument DocIntf;
  Doc->GetInterface(DocIntf);
  return Getdecks(DocIntf);
};

_di_IXMLdecksType __fastcall Loaddecks(const System::UnicodeString& FileName)
{
  return (_di_IXMLdecksType) Xml::Xmldoc::LoadXMLDocument(FileName)->GetDocBinding("decks", __classid(TXMLdecksType), TargetNamespace);
};

_di_IXMLdecksType __fastcall  Newdecks()
{
  return (_di_IXMLdecksType) Xml::Xmldoc::NewXMLDocument()->GetDocBinding("decks", __classid(TXMLdecksType), TargetNamespace);
};

// TXMLdecksType 

void __fastcall TXMLdecksType::AfterConstruction(void)
{
  ItemTag = "name";
  ItemInterface = __uuidof(Xml::Xmlintf::IXMLNode);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

System::UnicodeString __fastcall TXMLdecksType::Get_name(int Index)
{
  return List->Nodes[Index]->Text;
};

Xml::Xmlintf::_di_IXMLNode __fastcall TXMLdecksType::Add(const System::UnicodeString name)
{
  Xml::Xmlintf::_di_IXMLNode item = AddItem(-1);
  item->NodeValue = name;
  return item;
};

Xml::Xmlintf::_di_IXMLNode __fastcall TXMLdecksType::Insert(const int Index, const System::UnicodeString name)
{
  Xml::Xmlintf::_di_IXMLNode item = AddItem(Index);
  item->NodeValue = name;
  return item;
};
