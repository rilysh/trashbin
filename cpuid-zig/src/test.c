#include <stdio.h>
#include <string.h>
#include <cpuid.h>

int main()
{
    unsigned int eax, ebx, ecx, edx;
    char buf[13];

    __cpuid(1, eax, ebx, ecx, edx);
    printf("CPUID: %d\n", eax);

    __cpuid(0, eax, ebx, ecx, edx);
    printf("Largest basic function number implemented: %i\n", eax);

    memcpy(buf, &ebx, sizeof(ebx));
    memcpy(buf + 4, &edx, sizeof(edx));
    memcpy(buf + 8, &ecx, sizeof(ecx));

    printf("Vendor ID: %s\n", buf);
}
