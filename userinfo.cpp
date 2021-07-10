
// ********************************************************************************** //
//                                                                                  
//                                 XML Data Binding                                 
//                                                                                  
//         Generated on: 16/05/2020 14:13:19                                        
//       Generated from: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\userinfo.xml   
//   Settings stored in: C:\Users\Bruno\Desktop\Gwent Guide PROGRESS\userinfo.xdb   
//                                                                                  
// ********************************************************************************** //

#include <System.hpp>
#pragma hdrstop

#include "userinfo.h"


// Global Functions 

_di_IXMLcollectedType __fastcall Getcollected(Xml::Xmlintf::_di_IXMLDocument Doc)
{
  return (_di_IXMLcollectedType) Doc->GetDocBinding("collected", __classid(TXMLcollectedType), TargetNamespace);
};

_di_IXMLcollectedType __fastcall Getcollected(Xml::Xmldoc::TXMLDocument *Doc)
{
  Xml::Xmlintf::_di_IXMLDocument DocIntf;
  Doc->GetInterface(DocIntf);
  return Getcollected(DocIntf);
};

_di_IXMLcollectedType __fastcall Loadcollected(const System::UnicodeString& FileName)
{
  return (_di_IXMLcollectedType) Xml::Xmldoc::LoadXMLDocument(FileName)->GetDocBinding("collected", __classid(TXMLcollectedType), TargetNamespace);
};

_di_IXMLcollectedType __fastcall  Newcollected()
{
  return (_di_IXMLcollectedType) Xml::Xmldoc::NewXMLDocument()->GetDocBinding("collected", __classid(TXMLcollectedType), TargetNamespace);
};

// TXMLcollectedType 

void __fastcall TXMLcollectedType::AfterConstruction(void)
{
  RegisterChildNode(System::UnicodeString("card"), __classid(TXMLcardType));
  ItemTag = "card";
  ItemInterface = __uuidof(IXMLcardType);
  Xml::Xmldoc::TXMLNodeCollection::AfterConstruction();
};

_di_IXMLcardType __fastcall TXMLcollectedType::Get_card(int Index)
{
  return (_di_IXMLcardType) List->Nodes[Index];
};

_di_IXMLcardType __fastcall TXMLcollectedType::Add()
{
  return (_di_IXMLcardType) AddItem(-1);
};

_di_IXMLcardType __fastcall TXMLcollectedType::Insert(const int Index)
{
  return (_di_IXMLcardType) AddItem(Index);
};

// TXMLcardType 

System::UnicodeString __fastcall TXMLcardType::Get_name()
{
  return GetChildNodes()->Nodes[System::UnicodeString("name")]->Text;
};

void __fastcall TXMLcardType::Set_name(System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("name")]->NodeValue = Value;
};

System::UnicodeString __fastcall TXMLcardType::Get_comment()
{
  return GetChildNodes()->Nodes[System::UnicodeString("comment")]->Text;
};

void __fastcall TXMLcardType::Set_comment(System::UnicodeString Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("comment")]->NodeValue = Value;
};

int __fastcall TXMLcardType::Get_id()
{
  return GetChildNodes()->Nodes[System::UnicodeString("id")]->NodeValue.operator int();
};

void __fastcall TXMLcardType::Set_id(int Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("id")]->NodeValue = Value;
};
