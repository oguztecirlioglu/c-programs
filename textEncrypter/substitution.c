#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool checkduplicate(string s);

int main(int argc, string argv[])
{

    string key = argv[1];

    if (argc != 2)
    {
        printf("Need only one command line input.\n");
        return 1;
    }

    if (strlen(key) != 26)
    {
        printf("Key needs to have 26 characters\n");
        return 1;
    }

    if (checkduplicate(key) == 1)
    {
        printf("Key has duplicates\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    int n = strlen(plaintext);

    char ciphertext[n];

    printf("ciphertext: ");
    for(int i = 0; i < n; i++)
    {
        if (!isalnum(plaintext[i]) && plaintext[i] != ' ')
        {
            return 1;
            break;
        }
        if (plaintext[i] == ' ')
        {
            ciphertext[i] = ' ';
        }
        else if (isdigit(plaintext[i]))
        {
            ciphertext[i] = plaintext[i];
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = tolower(key[(int)plaintext[i]-'a']);
        }
        else
        {
            ciphertext[i] = toupper(key[(int)plaintext[i]-'A']);
        }
        printf("%c",ciphertext[i]);
    }

    printf("\n");

}

bool checkduplicate(string s)
{
    int n = strlen(s);
    int duplicates[52] = {0};

    for (int i = 0; i < n; i++)
    {
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
        {
            ;
        }
        else
        {
            return 1;
        }

        if (islower(s[i]))
        {
            duplicates[s[i]-97]++;
            if(duplicates[s[i]-97] == 2)
            {
                return 1;
            }
        }
        else
        {
            duplicates[s[i]-39]++;
            if (duplicates[s[i]-39] == 2)
            {
                return 1;
            }
        }
    }
    return 0;
};
