/*-----------------------------------------------------------
File: PMTBoardDB.h
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This file stores the association between servers, optical links,
 V1730 digitizers and fragment ids in the ICARUS DAQ system.

-------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <cstring>

// constant parameters for CAEN V1730
#define N_LINKS 8
#define MAX_CHANNELS 16

namespace PMTBoardDB {

// structure for board-info
struct V1730 
{
  int link;
  char name[100];
  int boardID;
  int fragmentID;
  int aX818;
  
  V1730() : link(0), name(""), boardID(0), fragmentID(0), aX818(0) {}
  
  V1730(int l, const char* n, int b, int f, int x) :
    link(l), boardID(b), fragmentID(f), aX818(x)
    {
      strncpy(name, n, sizeof(name)); 
      name[sizeof(name) - 1] = '\0';
    }
};

// board DB
const V1730 eebot01(4,"icaruspmteebot01",21,8213,5);
const V1730 eebot02(5,"icaruspmteebot02",22,8214,5);
const V1730 eebot03(6,"icaruspmteebot03",23,8215,5);
const V1730 eetop01(0,"icaruspmteetop01",18,8210,5);
const V1730 eetop02(1,"icaruspmteetop02",19,8211,5);
const V1730 eetop03(2,"icaruspmteetop03",20,8212,5);
const V1730 ewbot01(4,"icaruspmtewbot01",15,8207,3);
const V1730 ewbot02(5,"icaruspmtewbot02",16,8208,3);
const V1730 ewbot03(6,"icaruspmtewbot03",17,8209,3);
const V1730 ewtop01(0,"icaruspmtewtop01",12,8204,3);
const V1730 ewtop02(1,"icaruspmtewtop02",13,8205,3);
const V1730 ewtop03(2,"icaruspmtewtop03",14,8206,3);
const V1730 webot01(4,"icaruspmtwebot01",9,8201,3);
const V1730 webot02(5,"icaruspmtwebot02",10,8202,3);
const V1730 webot03(6,"icaruspmtwebot03",11,8203,3);
const V1730 wetop01(0,"icaruspmtwetop01",6,8198,3);
const V1730 wetop02(1,"icaruspmtwetop02",7,8199,3);
const V1730 wetop03(2,"icaruspmtwetop03",8,8200,3);
const V1730 wwbot01(4,"icaruspmtwwbot01",3,8195,3);
const V1730 wwbot02(5,"icaruspmtwwbot02",4,8196,3);
const V1730 wwbot03(6,"icaruspmtwwbot03",5,8197,3);
const V1730 wwtop01(0,"icaruspmtwwtop01",0,8192,3);
const V1730 wwtop02(1,"icaruspmtwwtop02",1,8193,3);
const V1730 wwtop03(2,"icaruspmtwwtop03",2,8194,3);
const V1730 empty3(3,"EMPTY",-1,-1,-1);
const V1730 empty7(7,"EMPTY",-1,-1,-1);
const V1730 empty(0,"",-1,-1,-1);

// server DB
V1730 server01[N_LINKS]{ wwtop01, wwtop02, wwtop03, empty3, wwbot01, wwbot02, wwbot03, empty7 };
V1730 server02[N_LINKS]{ wetop01, wetop02, wetop03, empty3, webot01, webot02, webot03, empty7 };
V1730 server03[N_LINKS]{ ewtop01, ewtop02, ewtop03, empty3, ewbot01, ewbot02, ewbot03, empty7 };
V1730 server04[N_LINKS]{ eetop01, eetop02, eetop03, empty3, eebot01, eebot02, eebot03, empty7 };
V1730 noserver[N_LINKS]{ empty, empty, empty, empty, empty, empty, empty, empty};

// get list of V1730 boards connected to the current host
void GetListOfBoards(V1730 (&boards)[N_LINKS])
{
  char hostname[100];
  int ret = gethostname(hostname, sizeof(hostname));
  printf("You are currently on %s\n",hostname);

  if (strcmp(hostname,"icarus-pmt01.fnal.gov")==0)
    memcpy(boards, server01, sizeof(server01));
  else if (strcmp(hostname,"icarus-pmt02.fnal.gov")==0)
    memcpy(boards, server02, sizeof(server02));
  else if (strcmp(hostname,"icarus-pmt03.fnal.gov")==0)
    memcpy(boards, server03, sizeof(server03));
  else if (strcmp(hostname,"icarus-pmt04.fnal.gov")==0)
    memcpy(boards, server04, sizeof(server04));
  else if (strcmp(hostname,"icarus-tpc27.fnal.gov")==0)
    memcpy(boards, server02, sizeof(server02));
  else 
  {
    memcpy(boards, noserver, sizeof(noserver));
    printf("****** no V1730 digitizers in DB for this server (%s) ******\n",hostname);
    return;
  }
}

} // end of boardDB

