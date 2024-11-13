#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void getpath()
{
  char buffer[64];
  unsigned int ret;

  printf("input path please: "); fflush(stdout);

  gets(buffer);

  // this function returns the return address of whatever level specified by the argument.
  // using 0 means 0 levels up or the current function
  ret = __builtin_return_address(0);

  // ANDing the return address and 0xbf00.. checks if the first two chars are bf
  // if you use gdb, youll see all stack addresses start with bf so this essentially
  // stops us from returning to an address on the stack
  if((ret & 0xbf000000) == 0xbf000000) {
    printf("bzzzt (%p)\n", ret);
    _exit(1); // exit if address is on the stack
  }

  printf("got path %s\n", buffer);
}

int main(int argc, char **argv)
{
  getpath();
}
