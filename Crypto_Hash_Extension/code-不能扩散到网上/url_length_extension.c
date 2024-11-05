#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

unsigned char *additionalMsg = "&download=secret.txt";

// The MAC for the valid URL
int a[8] = {  0x6d2356d1, 0xdd281171, 0x311d063e, 0xd9f782f3,
              0x7a46d2b2, 0xafa5aa69, 0x47830d9b, 0xfb21a6da };

// 6d2356d1,dd281171,311d063e,d9f782f3,7a46d2b2,afa5aa69,47830d9b,fb21a6da


int main(int argc, const char *argv[])
{
  int i;
  unsigned char buffer[SHA256_DIGEST_LENGTH];
  SHA256_CTX c;

  SHA256_Init(&c);

  /* We assume that the padded original message has 64 bytes (i.e., 1 block).
   * If that is not true, modify 64 accordingly, e.g. use 128 for 2 blocks. 
   * This step is important, because that is how we tell the hash function
   * the length of our message. */
  for (i=0; i<64; i++)  SHA256_Update(&c, "*", 1);

  for (i=0; i<8; i++)   c.h[i] = htole32(a[i]);

  // Append the additional message
  SHA256_Update(&c, additionalMsg, strlen(additionalMsg));
  SHA256_Final(buffer, &c);
  for (i = 0; i < 32; i++) {
      printf("%02x", buffer[i]);
  }
  printf("\n");

  return 0;
}
