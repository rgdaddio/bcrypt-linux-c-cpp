/*
 * Tester to test c/c++ on ubuntu bcrypt
 * Calls python to do the encrypt
 * Then uses c/c++ implementation to validate
 * There is encrypt via c/c++ tested commented below
 * Right now the implementation relies on 1)ubuntu bsd pkg
 * 2)and suckless software's explicit_bzero
 * There are really only 2 calls that need these pieces
 * The rest of the code is pretty much openbsd's implementation
 * 
 */
//tested with gcc 4.6.3 ubuntu 12.04
//tested with g++ 4.6.3 ubuntu 12.04
//tested with gcc 5.2.1 ubuntu 15.10
//tested with g++ 5.2.1 ubuntu 15.10

//sudo apt-get install libbsd-dev
//gcc -lbsd test.c bcrypt.c blowfish.c timing_safe.c linux_util.c -lrt `pkg-config --libs libbsd`
//g++ -lbsd test.c bcrypt.c blowfish.c timing_safe.c linux_util.c -lrt `pkg-config --libs libbsd`

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *bcrypt_gensalt(uint8_t log_rounds);
char *bcrypt(const char *pass, const char *salt);
int bcrypt_checkpass(const char *pass, const char *goodhash);

int dumpit(char *s);

int main(int argc, char *argv[])
{
  FILE *in;
  int count = 0;
  char inbuf[100];
  char outbuf[61];
  size_t len;
  char * nbuf;
  
  if(argc < 2){
    printf("USE: ./a.out  <pw>\n");
    return 0;
  }

  /*python call setup*/
  char const *tester = argv[1];
  char const *pypass = "/password.py";
  char const *pyval  = " password=";
  char cwd[1024];

  /*simple python must be where ./a.out is executed*/
  if (getcwd(cwd, sizeof(cwd)) != NULL)
    printf("Current working dir: %s\n", cwd);
  else
    {
      printf("cant get dir\n");
    }

  /*build string with pw to send to python program*/
  sprintf(cwd + strlen(cwd),"%s", pypass);
  sprintf(cwd + strlen(cwd), "%s", pyval);
  sprintf(cwd + strlen(cwd),"\"");
  sprintf(cwd + strlen(cwd), "%s", tester);
  sprintf(cwd + strlen(cwd), "\"");

  printf("python string: %s\n", cwd);
  
  if(!(in = popen(cwd, "r"))){
    printf("Unable to call verify script");
      return -1;
  }
  while(fgets(outbuf, 100, in) != NULL && count <  100){
    //read out the fd which is VALID or INVALID
    count++;
    if(count > 99){
      printf("excess loops\n");
      pclose(in);
      return 0;
    }
  }
  pclose(in);
    
  /**** Encrypt ****/  
  /*encrpt it here with c/c++ if you don't want python test*/
  //uint8_t log_round = 12; same as python
  //char *salty = bcrypt_gensalt(log_round);
  //char *crypto = bcrypt("tester", salty);
  
  //check with c/c++ pw vs python return(outbuf)
  int val = bcrypt_checkpass(tester, outbuf);
  
  printf("hash from python:   %s\n", outbuf);
  printf("outbuflen: %d\n", (int)strlen(outbuf));
  
  if(val==0)
    printf("SUCCESS: %d\n", val);
  else
    printf("FAIL %d\n", val);
  
  return 0;
  
}

int dumpit(char *s)
{
  char* forward = s;
  int forward_length = 0;
  while (*(forward++)!='\0') {
    forward_length++;
    //printf("Character %d", forward_length);
  }
  printf("Character %d\n", forward_length);
}
