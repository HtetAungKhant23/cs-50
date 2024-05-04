#include <stdio.h>
#include <string.h>

int countWords(char *text);
int countLetters(char *text);
int countSentences(char *text);
int computeIndex(int words, int letters, int sentences);

int main(){

    char* text = "It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him.";
    int words = countWords(text);
    int letters = countLetters(text);
    int sentences = countSentences(text);
    int index = computeIndex(words, letters, sentences);
    printf("%d and %d and %d and %d\n", index, words, letters, sentences);
    if(index < 1){
        printf("Before Grade 1");
    }else if (index >= 16){
        printf("Grade 16+");
    }else{
        printf("Grade %d\n", index);
    }

        return 0;
}

int countLetters(char *text){
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if(text[i] != ' ' && text[i] != '.' && text[i] != '?' && text[i] != '!'){
            letters++;
        }
    }
    return letters;
}

int countSentences(char *text){
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++){
        if(text[i] == '?' || text[i] == '.' || text[i] == '!'){
            sentences++;
        }
    }
    return sentences;
}

int countWords(char* text){
    int words = 0;
    for (int i = 0; i < strlen(text); i++){
        if(text[i] == ' '){
            words++;
        }
    }
    return words + 1;
}

int computeIndex(int words, int letters, int sentences){
    float L = (letters / (float)words) * 100;
    float S = (sentences / (float)words) * 100;
    return 0.0588 * L - 0.296 * S - 15.8;
}