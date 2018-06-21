#include <stdio.h>
#include <stdlib.h>
#include "printer.h"
#include "standart.h"
#include "udev.h"
#include "extended.h"

/***
SAMPLE OUTPUT

Name:        Intel Core i7-4790K
Arch:        64 Bits
Frequency:   4.0 GHz
NºCores:     4 cores(8 threads)
AXV:         AVX,AVX2
SSE:         SSE,SSE2,SSE4.1,SSE4.2
FMA:         FMA3
AES:         Yes
SHA:         No
L1 Size:     32KB(Data)32KB(Instructions)
L2 Size:     512KB
L3 Size:     8MB
Peak FLOPS:  512 GFLOP/s(in simple precision)

***/

int main() {
  struct cpuInfo* cpu = getCPUInfo();
  if(cpu == NULL)
    return EXIT_FAILURE;

  struct cache* cach = new_cache();
  struct frequency* freq = new_frequency();
  struct ascii* art = set_ascii(getCPUVendorInternal(cpu));

  char* cpuName = getString_CPUName();
  char* maxFrequency = getString_MaxFrequency(freq);
  char* nCores = getString_NumberCores(cpu);
  char* avx = getString_AVX(cpu);
  char* sse = getString_SSE(cpu);
  char* fma = getString_FMA(cpu);
  char* aes = getString_AES(cpu);
  char* sha = getString_SHA(cpu);
  char* l1 = getString_L1(cach);
  char* l2 = getString_L2(cach);
  char* l3 = getString_L3(cach);
  char* pp = getPeakPerformance(cpu,getFrequency(freq));

  setAttribute(art,ATTRIBUTE_NAME,cpuName);
  setAttribute(art,ATTRIBUTE_ARCH,"x86_64");
  setAttribute(art,ATTRIBUTE_FREQUENCY,maxFrequency);
  setAttribute(art,ATTRIBUTE_NCORES,nCores);
  setAttribute(art,ATTRIBUTE_AVX,avx);
  setAttribute(art,ATTRIBUTE_SSE,sse);
  setAttribute(art,ATTRIBUTE_FMA,fma);
  setAttribute(art,ATTRIBUTE_AES,aes);
  setAttribute(art,ATTRIBUTE_SHA,sha);
  setAttribute(art,ATTRIBUTE_L1,l1);
  setAttribute(art,ATTRIBUTE_L2,l2);
  setAttribute(art,ATTRIBUTE_L3,l3);
  setAttribute(art,ATTRIBUTE_PEAK,pp);

  print_ascii(art);

  free(cpuName);
  free(maxFrequency);
  free(nCores);
  free(avx);
  free(sse);
  free(fma);
  free(aes);
  free(sha);
  free(l1);
  free(l2);
  free(l3);
  free(pp);

  free(cpu);
  free(art);
  freeCache(cach);
  freeFrequency(freq);

  return EXIT_SUCCESS;
}
