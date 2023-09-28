#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <plugins.h>
#include <stdbool.h>
#include <orbis/libkernel.h>
#define db 0x003FC000
struct proc_info procInfo;
struct proc_rw datawrite;
OrbisPthread engine;
char auth[16];
unsigned char verid1[1]={0};
unsigned char verid2[1]={0};
unsigned char verid3[1]={0};
void procrw(u64 cd,void *dw,u64 s,u64 flag){
datawrite.address=cd+db;
datawrite.data=dw;
datawrite.length=s;
datawrite.write_flags=flag;
sys_sdk_proc_rw(&datawrite);}
void *spectrengine(void *args){
procrw(0x0126B8A4,verid1,1,0);
procrw(0x0126B8A8,verid2,1,0);
procrw(0x0126B8AA,verid3,1,0);
if(verid1[0]=='1'&&verid2[0]=='0'&&verid3[0]=='0'){
procrw(0x0133F900,DR100A,169,1);
procrw(0x0018D7F9,DR100B,9,1);
procrw(0x007B421D,DR100C,7,1);
procrw(0x007B4224,DR100C,7,1);
procrw(0x007B5449,DR100C,7,1);
}else{
procrw(0x0127B028,verid1,1,0);
procrw(0x0127B02C,verid2,1,0);
procrw(0x0127B02E,verid3,1,0);
if(verid1[0]=='1'&&verid2[0]=='0'&&verid3[0]=='3'){
procrw(0x01351F40,DR103A,169,1);
procrw(0x001A2A79,DR103B,9,1);
procrw(0x007D419D,DR103C,7,1);
procrw(0x007D41A4,DR103C,7,1);
procrw(0x007D53C9,DR103C,7,1);}}
scePthreadExit(NULL);
return NULL;}
int32_t attr_module_hidden module_start(size_t argc,const void *args){
if(sys_sdk_proc_info(&procInfo)){return 0;}
memcpy(auth, procInfo.titleid, sizeof(auth));
if(auth[4]=='0'&&auth[5]=='8'&&auth[6]=='4'&&auth[7]=='3'&&auth[8]=='2'){
scePthreadCreate(&engine, NULL, spectrengine, NULL, "spectrengine");}
else{if(auth[4]=='0'&&auth[5]=='8'&&auth[6]=='4'&&auth[7]=='9'&&auth[8]=='5'){
scePthreadCreate(&engine, NULL, spectrengine, NULL, "spectrengine");}
else{if(auth[4]=='0'&&auth[5]=='8'&&auth[6]=='5'&&auth[7]=='2'&&auth[8]=='6'){
scePthreadCreate(&engine, NULL, spectrengine, NULL, "spectrengine");}
else{if(auth[4]=='0'&&auth[5]=='8'&&auth[6]=='6'&&auth[7]=='9'&&auth[8]=='2'){
scePthreadCreate(&engine, NULL, spectrengine, NULL, "spectrengine");}}}}
return 0;}
int32_t attr_module_hidden module_stop(size_t argc,const void *args){
return 0;}