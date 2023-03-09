#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void print_table(int n, char *s, int index)
{
  if (n == 0) {
    printf("%s\n", s);
    return;  
  }

  print_table(n-1, (strcpy(s+index, "0"), s), index + 1);

  print_table(n-1, (strcpy(s+index, "1"), s), index + 1);

  return;
}

void printTable(int n, string s = string()) {
    if(n == 0) {
      cout << s << endl;
      return;
    }
    printTable(n-1, s + "0");
    printTable(n-1, s + "1");
  }

char s[100];

int main(int argc, char *argv[])
{
  //print_table(3, s, 0);
    printTable(3);
  exit(0);
}