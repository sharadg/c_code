#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

int main() {
  unsigned char ibuf[128], obuf[128], pbuf[1024], *p;
  int i, ifd, ofd, pfd, ilen, olen, plen, sz_enc, sz_dec;
  struct timeval tim, *t;
  t = &tim;
  ilen = olen = 128;
  plen = 1024;
  p = pbuf;


  pfd = open("/home/sgupta/tmp/pr.der", O_RDONLY);

  if (pfd  == -1) {
    perror("life sucks!");
    exit(1);
  } else {
    printf("life looks good!\n");
  }

  memset(pbuf, 0, plen);
  if ((plen = read(pfd, pbuf, plen)) > 0) {
    printf("%d bytes read from key file\n", plen);
  }

  RSA *rsa, *rsa2;
  rsa = RSA_new();
  //rsa2 = RSA_new();

  for (i = 0; i < plen; i++) {
    printf("%x", pbuf[i]);
    if (i < plen - 1) printf(":");
  }
  printf("\n");

  gettimeofday(t, NULL);
  printf("time in millis: %ld\n", t->tv_usec);
  rsa = d2i_RSAPrivateKey(NULL, (const unsigned char **)&p, 1024);
  gettimeofday(t, NULL);
  printf("time in millis: %ld\n", t->tv_usec);
  if (rsa == NULL) {
    ERR_print_errors_fp(stderr);
  }

  if (RSA_check_key(rsa)) {
    printf("key size: %d\n", RSA_size(rsa));
    printf("life is sweet!\n");
  }

  if ((ifd = open("/home/sgupta/tmp/cc.enc", O_RDONLY)) > 0) {
    printf("opened encrypted file!\n");
    memset(ibuf, 0, ilen);
    if ((ilen = read(ifd, ibuf, ilen)) > 0) {
      printf("%d bytes read from input file\n", ilen);

      memset(obuf, 0, olen);
      gettimeofday(t, NULL);
      printf("time in millis: %ld\n", t->tv_usec);
      sz_dec = RSA_private_decrypt(ilen, ibuf, obuf, rsa, RSA_PKCS1_OAEP_PADDING);
      gettimeofday(t, NULL);
      printf("time in millis: %ld\n", t->tv_usec);
      if (sz_dec > -1) {
        printf("size of decrypted text: %d\n", sz_dec);
        printf("decrypted text -> ");
        for (i = 0; i < sz_dec; i++) {
          printf("%x", obuf[i]);
          if (i < sz_dec - 1) printf(":");
        }
        printf("\n");
      }
    }
  }

  /* if ((ifd = open("/home/sgupta/tmp/cc", O_RDONLY)) > 0) {
     printf("opened text file!\n");
     memset(ibuf, 0, ilen);
     if ((ilen = read(ifd, ibuf, ilen)) > 0) {
     printf("%d bytes read from input file\n", ilen);

     memset(obuf, 0, olen);
     if ((sz_enc = RSA_public_encrypt(ilen, ibuf, obuf, rsa, RSA_NO_PADDING)) > -1) {
     printf("size of encrypted text: %d\n", sz_enc);
     printf("encrypted text -> ");
     for (i = 0; i < sz_enc; i++) {
     printf("%02x", obuf[i]);
     if (i < sz_enc - 1) printf(":");
     }
     printf("\n");
     }
     }
     }*/

}
