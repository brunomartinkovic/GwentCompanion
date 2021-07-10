
// ********************************************************************************* //
//                                                                                 
//                                XML Data Binding                                 
//                                                                                 
//         Generated on: 19/05/2020 01:48:12                                       
//       Generated from: C:\Users\Bruno\Desktop\Gwent Guide\Win32\Debug\lang.xml   
//   Settings stored in: C:\Users\Bruno\Desktop\Gwent Guide\Win32\Debug\lang.xdb   
//                                                                                 
// ********************************************************************************* //

#include <System.hpp>
#pragma hdrstop

#include "lang.h"


// Global Functions 

_di_IXMLlanguageType __fastcall Getlanguage(Xml::Xmlintf::_di_IXMLDocument Doc)
{
  return (_di_IXMLlanguageType) Doc->GetDocBinding("language", __classid(TXMLlanguageType), TargetNamespace);
};

_di_IXMLlanguageType __fastcall Getlanguage(Xml::Xmldoc::TXMLDocument *Doc)
{
  Xml::Xmlintf::_di_IXMLDocument DocIntf;
  Doc->GetInterface(DocIntf);
  return Getlanguage(DocIntf);
};

_di_IXMLlanguageType __fastcall Loadlanguage(const System::UnicodeString& FileName)
{
  return (_di_IXMLlanguageType) Xml::Xmldoc::LoadXMLDocument(FileName)->GetDocBinding("language", __classid(TXMLlanguageType), TargetNamespace);
};

_di_IXMLlanguageType __fastcall  Newlanguage()
{
  return (_di_IXMLlanguageType) Xml::Xmldoc::NewXMLDocument()->GetDocBinding("language", __classid(TXMLlanguageType), TargetNamespace);
};

// TXMLlanguageType 

int __fastcall TXMLlanguageType::Get_jezik()
{
  return GetChildNodes()->Nodes[System::UnicodeString("jezik")]->NodeValue.operator int();
};

void __fastcall TXMLlanguageType::Set_jezik(int Value)
{
  GetChildNodes()->Nodes[System::UnicodeString("jezik")]->NodeValue = Value;
};
