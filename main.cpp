#include <iostream>
#include <cstdlib>
#include <time.h> 
#include <vector>

void printWord(const std::string word);

std::string generateChallenge(const std::string word);

void guess(const std::string word, const std::string hiddenLetters);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Please provide a word as an argument" << std::endl;
        return 1;
    }

    guess(argv[1], generateChallenge(argv[1]));

    return 0;
}

void printWord(const std::string word)
{
    for (int i = 0, n = word.length(); i < n; i++)
    {
        std::cout << char(toupper(word[i]));
    }
}

std::string generateChallenge(const std::string word)
{
    const int length = word.length();

    std::cout << "===============Guess the word===============" << std::endl;
    std::cout << "Note: You only have 3 attempts" << std::endl;

    const int maxHiddenLetters = length * 2 / 5;
    std::vector<int> randomPositions {};
    srand(time(0));
    for (int i = 0; i < maxHiddenLetters; i++)
    {
        randomPositions.push_back(std::rand() % length);
    }

    std::string hiddenLetters{};
    for (int i = 0; i < length; i++)
    {
        bool isHiddenCharacter = false;
        for (const int j : randomPositions)
        {
            if (i == j)
            {
                isHiddenCharacter = true;
                hiddenLetters += word[i];
                break;
            }
        }

        if (isHiddenCharacter == true)
        {
            std::cout << "_";
        }
        else
        {
            std::cout << char(toupper(word[i]));
        }
    }
    std::cout << std::endl;
    return hiddenLetters;
}

void guess(const std::string word, const std::string hiddenLetters)
{
    const int chances = 3;
    const std::string hangman[] =
        {"======================|=====================",
         "                      |                     ",
         "                      |                     ",
         "                      O                     ",
         "                     /|\\                   ",
         "                     / \\                   "};

    bool isCorrect = true;
    std::string guessLetters {};
    for (int i = 0; i < chances; i++)
    {
        isCorrect = true;

        std::cout << "Guess: " << "[" << i + 1 << "] ";
        std::cin >> guessLetters;

        int mininumLength = guessLetters.length() > word.length() ? guessLetters.length() : word.length();

        for (int i = 0; i < mininumLength; i++)
        {
            if (toupper(guessLetters[i]) != toupper(word[i]))
            {
                isCorrect = false;
                break;
            }
        }

        if (isCorrect == true)
        {
            std::cout << "Congratulations!!! You Guessed ";
            printWord(word);
            std::cout << " Correctly!!!" << std::endl;
            std::cout << "============================================" << std::endl;
            break;
        }
        else
        {
            for (int j = 0; j < i + 1 && j < chances; j++)
            {
                std::cout << hangman[j] << std::endl;
            }
        }
    }

    if (isCorrect == false)
    {
        std::cout << "You lose!" << std::endl;
        for (const std::string line : hangman)
        {
            std::cout << line << std::endl;
        }
        std::cout << "It's ";
        printWord(word);
        std::cout << std::endl;
        std::cout << "============================================" << std::endl;
    }
}

