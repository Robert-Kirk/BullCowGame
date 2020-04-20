// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to my version of the \"Bull Cow Game\"! In this game you will be given an isogram to guess.\nWhen you guess, you will be informed about how close your guess was.\nThe number of Bulls is how many correct letters and positions you have.\nCows tell you if you have the correct letter, but not position.\nPlease enter your elected player name:"));
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    DecideStatement(Input);
}
void UBullCowCartridge::DecideStatement(const FString Input)
{

    //GameOver Play again or not.
    if (GameOver)
        HandleGameOver(Input);

    //IF the game is initially starting
    if (InitialStart)
    {
        //Print Insturction
        PlayerName = Input;
        InitialStart = false;
    }
    //If a new word is required
    //Cases: User has Guessed the word correctly or a new game round has started.
    if (BeginningNewWord)
    {
        /*Generate new word and set values and display*/
        
        int32 IndexOfWord = FMath::RandRange(0, ListOfHiddenWords.Num()-1);
        HiddenWord = ListOfHiddenWords[IndexOfWord];
        //ListOfHiddenWords.Remove(HiddenWord);
        Lives = (HiddenWord.Len() + 2);
        BeginningNewWord = false;
        ReportLives(Lives);
    }
    else if (!GameOver) //If a new word is not required and it is not game over
    {

        bool Correct = JudgeAnswer(Input);
        /*react to guesss*/
        if (Correct) //If a guess is correct
        {
            PrintLine(TEXT("VICTORY"));
            GameOver = true;
        }
        else //If a guess is not correct
        {
            ResolveIncorrectGuess(Input);
        }
    }
    if (GameOver)
    {
        PrintLine(TEXT("Please type \"yes\" to continue or \"no\" to exit the game."));
    }
    else
    {
        FString Message = PlayerName;
        Message.Append(TEXT(", the isogram is "))
            .Append(FString::FromInt(HiddenWord.Len()))
            .Append(TEXT(" characters long."));
        PrintLine(Message);
    }
}
//Declars if the answer is correct, ignoring case.
bool UBullCowCartridge::JudgeAnswer(const FString Input)
{
    return HiddenWord.Equals(Input, ESearchCase::IgnoreCase);
}
/*
User Input on what they want to do if they get a game over, regardless of victory or defeat.
submitting 'yes' will continue the game
submitting 'no' will 'exit' the game.
*/
void UBullCowCartridge::HandleGameOver(const FString Input)
{
    if (Input.Equals(TEXT("yes"), ESearchCase::IgnoreCase))
    {
        BeginningNewWord = true;
        GameOver = false;
        GuessedWords.Empty();
    }
    else if (Input.Equals(TEXT("no"), ESearchCase::IgnoreCase))
    {
        //write code to exit game
    }
}
void UBullCowCartridge::ReportLives(int32 Lives)
{
    FString Message = TEXT("You have: ");
    Message.Append(FString::FromInt(Lives));
    PrintLine(Message);
}
void UBullCowCartridge::ResolveIncorrectGuess(const FString Input)
{
    if (IsAnswerCompliant(Input))
    {
        ++NumberOfGuessesMade;

        
        if ((Lives - NumberOfGuessesMade) > 0)
        {
            PrintBullsAndCowsStatement(Input.ToLower());
        }
        else
        {
            PrintLine(TEXT("You lose. Want to start over?"));
            GameOver = true;
            NumberOfGuessesMade = 0;
        }
    }
    else
    {
        PrintLine(TEXT("Your answer either was not an isogram, did not have the right number of characters, or it was a duplicate word"));
    }
    ReportLives(Lives - NumberOfGuessesMade);
}
bool UBullCowCartridge::IsAnswerCompliant(const FString Input)
{
    return (IsIsogram(Input) && HiddenWord.Len() == Input.Len() && IsNotDuplicate(Input));
}
bool UBullCowCartridge::IsIsogram(const FString Input)
{

    TSet<TCHAR> SetOfInputChars;
    for (int32 i = 0; i < Input.Len(); i++)
    {
        TCHAR CurrentChar = Input[i];
        if (SetOfInputChars.Contains(CurrentChar))
        {
            return false;
        }
        else
        {
            SetOfInputChars.Add(CurrentChar);
        }
    }

    return true;
}
bool UBullCowCartridge::IsNotDuplicate(const FString Input)
{
    if (!GuessedWords.Contains(Input.ToLower()))
    {
        GuessedWords.Add(Input.ToLower());
        return true;
    }
    else
    {
        return false;
    }
}

void UBullCowCartridge::PrintBullsAndCowsStatement(const FString Input)
{
    int32 Bulls = 0;
    int32 Cows = 0;
    FString LocalizedHiddenWord = HiddenWord.ToLower();
    TArray<TCHAR> HiddenWordCharArray = LocalizedHiddenWord.GetCharArray();
    for (int32 i = 0; i < HiddenWord.Len(); i++)
    {
        //TCHAR* CurrentChar = new TCHAR(Input[i]);
        //TCHAR* HWCurrentChar = new TCHAR(HiddenWord[i]);
        if (LocalizedHiddenWord[i] == Input[i])
        {
            ++Bulls;
        }
        else if(HiddenWordCharArray.Contains(Input[i]))
        {
            ++Cows;
        }
        
    }

    FString Message = TEXT("Bulls: ");
    Message.Append(FString::FromInt(Bulls))
    .Append(" \nCows: ")
    .Append(FString::FromInt(Cows));
    PrintLine(Message);

    
    
}