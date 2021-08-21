#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


bool isEndSentence(int index, string text);
bool isLetter(int index, string text);
bool isSpace(int index, string text);


int main(void)
{
    string text = get_string("Text: ");

    int n = strlen(text);
    int sentences = 0, words = 1, letters = 0;

    //We need letters, sentences, and words.

    for(int i = 0; i < n; i++)
    {
        if (isLetter(i,text))
        {
            letters++;
        }
        else if(isEndSentence(i,text) && isLetter(i-1,text))
        {
            sentences++;
        }
        else if(isSpace(i,text))
        {
            words++;
        }
    }


    float L = (float) letters / words * 100.00;
    float S = (float) sentences / words * 100.00;
    int index = (int)round((0.0588 * L) - (0.296 * S) - 15.8);

    //printf("True grade is %f", index);
    if(index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
    printf("Grade %i\n", index);
    }
    //printf("Found %i words, %i sentences, %i letters.", words, sentences, letters);
}



bool isEndSentence(int index, string text)
{
    if(text[index] == '!' || text[index] == '.' || text[index] == '?')
    {
        return true;
    }
    else
    {
        return false;
    }
};

bool isLetter(int index, string text)
{
     if ((text[index] >= 'a' && text[index] <= 'z') || (text[index] >= 'A' && text[index] <= 'Z'))
     {
         return true;
     }
     else
     {
         return false;
     }
}

bool isSpace(int index, string text)
{
    if(text[index] == 32)
    {
        return true;
    }
    else
    {
        return false;
    }
}
