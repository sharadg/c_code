#include <stdio.h>
#include <string.h>

unsigned char convert_to_dec(unsigned char in) {
  if (in > 'A' - 1)
    return (in - '0' - 7);
  else
    return (in - '0');
}

int main() {

  char b[10] = {'1', 'A', '2', 'B'};
  int i = 0;

  unsigned char a[5];
  unsigned char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  unsigned char buf1, buf2;
  unsigned char tmp;

  for(i = 0; i < strlen(b); i+=2) {
    buf1 = convert_to_dec(b[i]);
    buf2 = convert_to_dec(b[i+1]);
    tmp = (buf1 << 4 | buf2) & 0xff;
    a[i/2] = tmp;
  }

  printf("hex: %s\n", b);
  printf("decoded: %x:%x\n", a[0], a[1]);

  return 0;
}

