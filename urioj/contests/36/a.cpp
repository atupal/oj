#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char ans[100][100] ={"",
    "3",
    "13",
    "21",
    "34",
    "144",
    "233",
    "377",
    "987",
    "6765",
    "46368",
    "121393",
    "317811",
    "832040",
    "1346269",
    "2178309",
    "3524578",
    "14930352",
    "39088169",
    "63245986",
    "102334155",
    "433494437",
    "701408733",
    "1134903170",
    "1836311903",
    "2971215073",
    "4807526976",
    "20365011074",
    "32951280099",
    "53316291173",
    "139583862445",
    "225851433717",
    "365435296162",
    "1548008755920",
    "2504730781961",
    "4052739537881",
    "6557470319842",
    "10610209857723",
    "27777890035288",
    "44945570212853",
    "72723460248141",
    "117669030460994",
    "190392490709135",
    "308061521170129",
    "498454011879264",
    "806515533049393",
    "1304969544928657",
    "3416454622906707",
    "5527939700884757",
    "8944394323791464",
    "14472334024676221",
    "23416728348467685",
    "37889062373143906",
    "61305790721611591",
    "99194853094755497",
    "160500643816367088",
    "420196140727489673",
    "679891637638612258",
    "1100087778366101931",
    "2880067194370816120",
    "4660046610375530309",
};



int main() {
  int n;
  while(scanf("%d", &n)!= EOF)
    printf("%s\n", ans[n]);
  return 0;
}