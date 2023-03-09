#include <stdio.h>
#include <string.h>


void number_spell(int num, char** names) {
    if(num < 10) {
        printf("%s ",names[num]);
        return;
    }

    number_spell(num/ 10, names);

    printf("%s ",names[num%10]);
}

int main()
{
    char* names[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    number_spell(123, names);
}