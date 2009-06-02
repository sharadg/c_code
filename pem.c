#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
  unsigned char ibuf[128], obuf[128];
  int i, ifd, ofd, ilen, olen, sz_enc, sz_dec;
  ilen = olen = 128;

  
  FILE *prk;
  prk = fopen("/home/sgupta/tmp/pr.key", "r");

  if (prk == NULL) {
    printf("life sucks!\n");
    exit(1);
  } else {
    printf("life looks good!\n");
  }

  RSA *rsa, *rsa2;
  rsa = RSA_new();
  //rsa2 = RSA_new();
  
  if ((rsa2 = PEM_read_RSAPrivateKey(prk, &rsa, NULL, NULL)) != NULL) {
    printf("key size: %d\n", RSA_size(rsa));
  }

  if (RSA_check_key(rsa)) {
    printf("life is sweet!\n");
  }

  if ((ifd = open("/home/sgupta/tmp/encc", O_RDONLY)) > 0) {
    printf("opened encrypted file!\n");
    memset(ibuf, 0, ilen);
    if ((ilen = read(ifd, ibuf, ilen)) > 0) {
      printf("%d bytes read from input file\n", ilen);

      memset(obuf, 0, olen);
      if ((sz_dec = RSA_private_decrypt(ilen, ibuf, obuf, rsa, RSA_PKCS1_PADDING)) > -1) {
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

  /*  if ((ifd = open("/home/sgupta/tmp/cc", O_RDONLY)) > 0) {
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
