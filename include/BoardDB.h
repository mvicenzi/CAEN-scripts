/*-----------------------------------------------------------
File: BoardDB.h
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

namespace boardDB {

// structure for board-info
struct V1730 
{
  int link;
  char name[100];
  int boardID;
  int fragmentID;
  
  V1730() : link(0), name(""), boardID(0), fragmentID(0) {}
  
  V1730(int l, const char* n, int b, int f) :
    link(l), boardID(b), fragmentID(f)
    {
      strncpy(name, n, sizeof(name)); 
      name[sizeof(name) - 1] = '\0';
    }
};

// board DB
const V1730 eebot01(5,"icaruspmteebot01",21,8213);
const V1730 eebot02(6,"icaruspmteebot02",22,8214);
const V1730 eebot03(7,"icaruspmteebot03",23,8215);
const V1730 eetop01(2,"icaruspmteetop01",18,8210);
const V1730 eetop02(3,"icaruspmteetop02",19,8211);
const V1730 eetop03(4,"icaruspmteetop03",20,8212);
const V1730 ewbot01(7,"icaruspmtewbot01",15,8207);
const V1730 ewbot02(0,"icaruspmtewbot02",16,8208);
const V1730 ewbot03(1,"icaruspmtewbot03",17,8209);
const V1730 ewtop01(4,"icaruspmtewtop01",12,8204);
const V1730 ewtop02(5,"icaruspmtewtop02",13,8205);
const V1730 ewtop03(6,"icaruspmtewtop03",14,8206);
const V1730 webot01(1,"icaruspmtwebot01",9,8201);
const V1730 webot02(2,"icaruspmtwebot02",10,8202);
const V1730 webot03(3,"icaruspmtwebot03",11,8203);
const V1730 wetop01(6,"icaruspmtwetop01",6,8198);
const V1730 wetop02(7,"icaruspmtwetop02",7,8199);
const V1730 wetop03(0,"icaruspmtwetop03",8,8200);
const V1730 wwbot01(3,"icaruspmtwwbot01",3,8195);
const V1730 wwbot02(4,"icaruspmtwwbot02",4,8196);
const V1730 wwbot03(5,"icaruspmtwwbot03",5,8197);
const V1730 wwtop01(0,"icaruspmtwwtop01",0,8192);
const V1730 wwtop02(1,"icaruspmtwwtop02",1,8193);
const V1730 wwtop03(2,"icaruspmtwwtop03",2,8194);

// server DB
V1730 server01[N_LINKS]{ wwtop01, wwtop02, wwtop03, wwbot01, wwbot02, wwbot03, wetop01, wetop02 };
V1730 server02[N_LINKS]{ wetop03, webot01, webot02, webot03, ewtop01, ewtop02, ewtop03, ewbot01 };
V1730 server03[N_LINKS]{ ewbot02, ewbot03, eetop01, eetop02, eetop03, eebot01, eebot02, eebot03 };

// get list of V1730 boards connected to the current host
void GetListOfBoards(V1730 (&boards)[N_LINKS])
{
  char hostname[100];
  int ret = gethostname(hostname, sizeof(hostname));
  printf("You are currently on %s\n",hostname);

  if (strcmp(hostname,"icarus-pmt01")==0)
    memcpy(boards, server01, sizeof(server01));
  else if (strcmp(hostname,"icarus-pmt02")==0)
    memcpy(boards, server02, sizeof(server02));
  else if (strcmp(hostname,"icarus-pmt03.fnal.gov")==0)
    memcpy(boards, server03, sizeof(server03));
  else 
  {
    printf("****** no V1730 digitizers in DB for this server (%s) ******",hostname);
    return;
  }
}

} // end of boardDB

