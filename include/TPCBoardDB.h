/*-----------------------------------------------------------
File: TPCBoardDB.h
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This file stores the association between servers, optical links,
 VA2795 digitizers and fragment ids in the ICARUS DAQ system.

-------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <cstring>

// constant parameters for CAEN A2795
#define N_CRATES 4

namespace TPCBoardDB {

// structure for crate-info
struct A2795Crate 
{
  int link1;
  int link2;
  char name[100];
  int fragmentID;
  int nboards1;
  int nboards2;
  int aX818;
  
  A2795Crate() : link1(0), link2(0), name(""), fragmentID(0), nboards1(0), nboards2(0), aX818(0) {}
  
  A2795Crate(int l1, int l2, const char* n, int f, int nb1, int nb2, int x) :
    link1(l1), link2(l2), fragmentID(f), nboards1(nb1), nboards2(nb2), aX818(x)
    {
      strncpy(name, n, sizeof(name)); 
      name[sizeof(name) - 1] = '\0';
    }
};

// board DB
const A2795Crate ee01b(2,3,"icarustpcee01b",4100,4,5,3);
const A2795Crate ee01m(4,5,"icarustpcee01m",4098,4,5,3);
const A2795Crate ee01t(6,7,"icarustpcee01t",4096,4,4,3);
const A2795Crate ee02(0,1,"icarustpcee02",4102,4,5,3);
const A2795Crate ee03(6,7,"icarustpcee03",4104,4,5,3);
const A2795Crate ee04(4,5,"icarustpcee04",4106,4,5,3);
const A2795Crate ee05(2,3,"icarustpcee05",4108,4,5,3);
const A2795Crate ee06(0,1,"icarustpcee06",4110,4,5,3);
const A2795Crate ee07(6,7,"icarustpcee07",4112,4,5,3);
const A2795Crate ee08(4,5,"icarustpcee08",4114,4,5,3);
const A2795Crate ee09(2,3,"icarustpcee09",4116,4,5,3);
const A2795Crate ee10(0,1,"icarustpcee10",4118,4,5,3);
const A2795Crate ee11(6,7,"icarustpcee11",4352,4,5,3);
const A2795Crate ee12(4,5,"icarustpcee12",4354,4,5,3);
const A2795Crate ee13(2,3,"icarustpcee13",4356,4,5,3);
const A2795Crate ee14(0,1,"icarustpcee14",4358,4,5,3);
const A2795Crate ee15(6,7,"icarustpcee15",4360,4,5,3);
const A2795Crate ee16(4,5,"icarustpcee16",4362,4,5,3);
const A2795Crate ee17(2,3,"icarustpcee17",4364,4,5,3);
const A2795Crate ee18(0,1,"icarustpcee16",4366,4,5,3);
const A2795Crate ee19(6,7,"icarustpcee19",4368,4,5,3);
const A2795Crate ee20b(4,5,"icarustpcee20b",4374,4,5,3);
const A2795Crate ee20m(2,3,"icarustpcee20m",4372,4,5,3);
const A2795Crate ee20t(0,1,"icarustpcee20t",4370,4,4,3);
const A2795Crate ew01b(2,3,"icarustpcew01b",4612,4,5,3);
const A2795Crate ew01m(4,5,"icarustpcew01m",4610,4,5,3);
const A2795Crate ew01t(6,7,"icarustpcew01t",4608,4,4,3);
const A2795Crate ew02(0,1,"icarustpcew02",4614,4,5,3);
const A2795Crate ew03(6,7,"icarustpcew03",4616,4,5,3);
const A2795Crate ew04(4,5,"icarustpcew04",4618,4,5,3);
const A2795Crate ew05(2,3,"icarustpcew05",4620,4,5,3);
const A2795Crate ew06(0,1,"icarustpcew06",4622,4,5,3);
const A2795Crate ew07(6,7,"icarustpcew07",4624,4,5,3);
const A2795Crate ew08(4,5,"icarustpcew08",4626,4,5,3);
const A2795Crate ew09(2,3,"icarustpcew09",4628,4,5,3);
const A2795Crate ew10(0,1,"icarustpcew10",4630,4,5,3);
const A2795Crate ew11(6,7,"icarustpcew11",4864,4,5,3);
const A2795Crate ew12(4,5,"icarustpcew12",4866,4,5,3);
const A2795Crate ew13(2,3,"icarustpcew13",4868,4,5,3);
const A2795Crate ew14(0,1,"icarustpcew14",4870,4,5,3);
const A2795Crate ew15(6,7,"icarustpcew15",4872,4,5,3);
const A2795Crate ew16(4,5,"icarustpcew16",4874,4,5,3);
const A2795Crate ew17(2,3,"icarustpcew17",4876,4,5,3);
const A2795Crate ew18(0,1,"icarustpcew16",4878,4,5,3);
const A2795Crate ew19(6,7,"icarustpcew19",4880,4,5,3);
const A2795Crate ew20b(4,5,"icarustpcew20b",4886,4,5,3);
const A2795Crate ew20m(2,3,"icarustpcew20m",4884,4,5,3);
const A2795Crate ew20t(0,1,"icarustpcew20t",4882,4,4,3);
const A2795Crate we01b(2,3,"icarustpcwe01b",5124,4,5,3);
const A2795Crate we01m(4,5,"icarustpcwe01m",5122,4,5,3);
const A2795Crate we01t(6,7,"icarustpcwe01t",5120,4,4,3);
const A2795Crate we02(0,1,"icarustpcwe02",5126,4,5,3);
const A2795Crate we03(6,7,"icarustpcwe03",5128,4,5,3);
const A2795Crate we04(4,5,"icarustpcwe04",5130,4,5,3);
const A2795Crate we05(2,3,"icarustpcwe05",5132,4,5,3);
const A2795Crate we06(0,1,"icarustpcwe06",5134,4,5,3);
const A2795Crate we07(6,7,"icarustpcwe07",5136,4,5,3);
const A2795Crate we08(4,5,"icarustpcwe08",5138,4,5,3);
const A2795Crate we09(2,3,"icarustpcwe09",5140,4,5,3);
const A2795Crate we10(0,1,"icarustpcwe10",5142,4,5,3);
const A2795Crate we11(6,7,"icarustpcwe11",5376,4,5,3);
const A2795Crate we12(4,5,"icarustpcwe12",5378,4,5,3);
const A2795Crate we13(2,3,"icarustpcwe13",5380,4,5,3);
const A2795Crate we14(0,1,"icarustpcwe14",5382,4,5,3);
const A2795Crate we15(6,7,"icarustpcwe15",5384,4,5,3);
const A2795Crate we16(4,5,"icarustpcwe16",5386,4,5,3);
const A2795Crate we17(2,3,"icarustpcwe17",5388,4,5,3);
const A2795Crate we18(0,1,"icarustpcwe16",5390,4,5,3);
const A2795Crate we19(6,7,"icarustpcwe19",5392,4,5,3);
const A2795Crate we20b(4,5,"icarustpcwe20b",5398,4,5,3);
const A2795Crate we20m(2,3,"icarustpcwe20m",5396,4,5,3);
const A2795Crate we20t(0,1,"icarustpcwe20t",5394,4,4,3);
const A2795Crate ww01b(2,3,"icarustpcww01b",5636,4,5,3);
const A2795Crate ww01m(4,5,"icarustpcww01m",5634,4,5,3);
const A2795Crate ww01t(6,7,"icarustpcww01t",5632,4,4,3);
const A2795Crate ww02(0,1,"icarustpcww02",5638,4,5,3);
const A2795Crate ww03(6,7,"icarustpcww03",5640,4,5,3);
const A2795Crate ww04(4,5,"icarustpcww04",5642,4,5,3);
const A2795Crate ww05(2,3,"icarustpcww05",5644,4,5,3);
const A2795Crate ww06(0,1,"icarustpcww06",5646,4,5,3);
const A2795Crate ww07(6,7,"icarustpcww07",5648,4,5,3);
const A2795Crate ww08(4,5,"icarustpcww08",5650,4,5,3);
const A2795Crate ww09(2,3,"icarustpcww09",5652,4,5,3);
const A2795Crate ww10(0,1,"icarustpcww10",5654,4,5,3);
const A2795Crate ww11(6,7,"icarustpcww11",5888,4,5,3);
const A2795Crate ww12(4,5,"icarustpcww12",5890,4,5,3);
const A2795Crate ww13(2,3,"icarustpcww13",5892,4,5,3);
const A2795Crate ww14(0,1,"icarustpcww14",5894,4,5,3);
const A2795Crate ww15(6,7,"icarustpcww15",5896,4,5,3);
const A2795Crate ww16(4,5,"icarustpcww16",5898,4,5,3);
const A2795Crate ww17(2,3,"icarustpcww17",5900,4,5,3);
const A2795Crate ww18(0,1,"icarustpcww16",5902,4,5,3);
const A2795Crate ww19(6,7,"icarustpcww19",5904,4,5,3);
const A2795Crate ww20b(4,5,"icarustpcww20b",5910,4,5,3);
const A2795Crate ww20m(2,3,"icarustpcww20m",5908,4,5,3);
const A2795Crate ww20t(0,1,"icarustpcww20t",5906,4,4,3);
const A2795Crate empty(0,0,"",-1,0,0,-1);

// server DB
A2795Crate server25[N_CRATES]{ ee02, ee01b, ee01m, ee01t };
A2795Crate server23[N_CRATES]{ ee06, ee05, ee04, ee03 };
A2795Crate server22[N_CRATES]{ ee10, ee09, ee08, ee07 };
A2795Crate server21[N_CRATES]{ ee14, ee13, ee12, ee11 };
A2795Crate server20[N_CRATES]{ ee18, ee17, ee16, ee15 };
A2795Crate server19[N_CRATES]{ ee20t, ee20m, ee20b, ee19 };
A2795Crate server18[N_CRATES]{ ew02, ew01b, ew01m, ew01t };
A2795Crate server17[N_CRATES]{ ew06, ew05, ew04, ew03 };
A2795Crate server16[N_CRATES]{ ew10, ew09, ew08, ew07 };
A2795Crate server15[N_CRATES]{ ew14, ew13, ew12, ew11 };
A2795Crate server14[N_CRATES]{ ew18, ew17, ew16, ew15 };
A2795Crate server13[N_CRATES]{ ew20t, ew20m, ew20b, ew19 };
A2795Crate server12[N_CRATES]{ we02, we01b, we01m, we01t };
A2795Crate server11[N_CRATES]{ we06, we05, we04, we03 };
A2795Crate server10[N_CRATES]{ we10, we09, we08, we07 };
A2795Crate server09[N_CRATES]{ we14, we13, we12, we11 };
A2795Crate server08[N_CRATES]{ we18, we17, we16, we15 };
A2795Crate server07[N_CRATES]{ we20t, we20m, we20b, we19 };
A2795Crate server06[N_CRATES]{ ww02, ww01b, ww01m, ww01t };
A2795Crate server05[N_CRATES]{ ww06, ww05, ww04, ww03 };
A2795Crate server04[N_CRATES]{ ww10, ww09, ww08, ww07 };
A2795Crate server03[N_CRATES]{ ww14, ww13, ww12, ww11 };
A2795Crate server02[N_CRATES]{ ww18, ww17, ww16, ww15 };
A2795Crate server01[N_CRATES]{ ww20t, ww20m, ww20b, ww19 };
A2795Crate noserver[N_CRATES]{ empty, empty, empty, empty };

// get list of A2795 crates connected to the current host
void GetListOfCrates(A2795Crate (&crates)[N_CRATES])
{
  char hostname[100];
  int ret = gethostname(hostname, sizeof(hostname));
  printf("You are currently on %s\n",hostname);

  if (strcmp(hostname,"icarus-tpc01.fnal.gov")==0)
      memcpy(crates, server01, sizeof(server01));
  else if (strcmp(hostname,"icarus-tpc02.fnal.gov")==0)
      memcpy(crates, server02, sizeof(server02));
  else if (strcmp(hostname,"icarus-tpc03.fnal.gov")==0)
      memcpy(crates, server03, sizeof(server03));
  else if (strcmp(hostname,"icarus-tpc04.fnal.gov")==0)
      memcpy(crates, server04, sizeof(server04));
  else if (strcmp(hostname,"icarus-tpc05.fnal.gov")==0)
      memcpy(crates, server05, sizeof(server05));
  else if (strcmp(hostname,"icarus-tpc06.fnal.gov")==0)
      memcpy(crates, server06, sizeof(server06));
  else if (strcmp(hostname,"icarus-tpc07.fnal.gov")==0)
      memcpy(crates, server07, sizeof(server07));
  else if (strcmp(hostname,"icarus-tpc08.fnal.gov")==0)
      memcpy(crates, server08, sizeof(server08));
  else if (strcmp(hostname,"icarus-tpc09.fnal.gov")==0)
      memcpy(crates, server09, sizeof(server09));
  else if (strcmp(hostname,"icarus-tpc10.fnal.gov")==0)
      memcpy(crates, server10, sizeof(server10));
  else if (strcmp(hostname,"icarus-tpc11.fnal.gov")==0)
      memcpy(crates, server11, sizeof(server11));
  else if (strcmp(hostname,"icarus-tpc12.fnal.gov")==0)
      memcpy(crates, server12, sizeof(server12));
  else if (strcmp(hostname,"icarus-tpc13.fnal.gov")==0)
      memcpy(crates, server13, sizeof(server13));
  else if (strcmp(hostname,"icarus-tpc14.fnal.gov")==0)
      memcpy(crates, server14, sizeof(server14));
  else if (strcmp(hostname,"icarus-tpc15.fnal.gov")==0)
      memcpy(crates, server15, sizeof(server15));
  else if (strcmp(hostname,"icarus-tpc16.fnal.gov")==0)
      memcpy(crates, server16, sizeof(server16));
  else if (strcmp(hostname,"icarus-tpc17.fnal.gov")==0)
      memcpy(crates, server17, sizeof(server17));
  else if (strcmp(hostname,"icarus-tpc18.fnal.gov")==0)
      memcpy(crates, server18, sizeof(server18));
  else if (strcmp(hostname,"icarus-tpc19.fnal.gov")==0)
      memcpy(crates, server19, sizeof(server19));
  else if (strcmp(hostname,"icarus-tpc20.fnal.gov")==0)
      memcpy(crates, server20, sizeof(server20));
  else if (strcmp(hostname,"icarus-tpc21.fnal.gov")==0)
      memcpy(crates, server21, sizeof(server21));
  else if (strcmp(hostname,"icarus-tpc22.fnal.gov")==0)
      memcpy(crates, server22, sizeof(server22));
  else if (strcmp(hostname,"icarus-tpc23.fnal.gov")==0)
      memcpy(crates, server23, sizeof(server23));
  else if (strcmp(hostname,"icarus-tpc25.fnal.gov")==0)
      memcpy(crates, server25, sizeof(server25));
  else 
  {
    memcpy(crates, noserver, sizeof(noserver));
    printf("****** no A2795digitizers in DB for this server (%s) ******\n",hostname);
    return;
  }
}

} // end of boardDB

