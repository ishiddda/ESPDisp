#pragma once

#include<arduino.h>
//#include<FS.h>
#include<String.h>
#include<LittleFS.h>

String inifileString( File fp, const char *header, char *detail, const char *defaultData);
int inifileInteger( File fp, char *header, char *detail, int defaultData );
int inifileInteger( File fp, char *header, char *detail, int defaultData );
bool inifileBool( File fp, char *header, char *detail, bool defaultData );
bool CheckHeadString(String str, String header);
bool CheckItemString(String str, String detail, String *Value);
void ReadIniFile( void );

