#include <stdio.h>

int main(int argc,char** argv) { 
int status;  
FILE* fto;  
char buf[512];
if(argc!=2){  
fprintf(stderr,"USAGE:filenameoption.n"); 
return -1; }
status=mkdir("pilot",0755); 
(!status)?printf("Directorycreated..n"): printf("Unabletocreatedirectory..n");
status=mkdir("./pilot/a",0755); 
(!status)?printf("Directorycreated..n"): printf("Unabletocreatedirectory..n");
sprintf(buf,"ls-al"); 
system(buf);
status=rmdir("pilot"); 
(!status)?printf("Directorydeleted.\n"): printf("Unabletodeletethedirectory.\n"); 
status=chdir("./pilot/a"); 
(!status)?printf("CurrentWorkingDirectoryischanged.\n"): printf("Unabletochangetothedirectory.\n"); 
fto=fopen(argv[1],"w+"); 
strcpy(buf,"\n\tKorea politechnic University \n\tComputer Sciencen\tHong Gil Dong ");
fwrite(buf,strlen(buf),1,fto); 
fprintf(fto,"\n\n\tClass of Advanced Programming\n"); 
fclose(fto); 
sprintf(buf,"more%s",argv[1]); system(buf); 
status=chdir("../.."); (!status)?printf("CurrentWorkingDirectoryischanged.\n"): 
printf("Unabletochangetothedirectory.\n"); 
sprintf(buf,"rm-rf%s","test");
//unlink().... system(buf); 
return 0; }



