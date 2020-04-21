// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;

	bool JudgeAnswer(const FString& Input);
	bool IsAnswerCompliant(const FString& Input);
	// bool IsIsogram(const FString Input);
	bool IsNotDuplicate(const FString& Input);

	void DecideStatement(const FString& Input);
	void HandleGameOver(const FString& Input);
	void ResolveIncorrectGuess(const FString& Input);
	void ReportLives(const int32& Lives);
	void PrintBullsAndCowsStatement(const FString& Input);

	static bool IsIsogram(const FString Input)
	{

		// TSet<TCHAR> SetOfInputChars;
		// for (int32 i = 0; i < Input.Len(); i++)
		// {
		// 	TCHAR CurrentChar = Input[i];
		// 	if (SetOfInputChars.Contains(CurrentChar))
		// 	{
		// 		return false;
		// 	}
		// 	else
		// 	{
		// 		SetOfInputChars.Add(CurrentChar);
		// 	}
		// }
		TSet<TCHAR> SetOfInputChars;
		for (TCHAR CurrentChar : Input)
		{
			// TCHAR CurrentChar = Input[i];
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

	// Your declarations go below!
private:
	TSet<FString> GuessedWords;

	FString PlayerName;
	FString HiddenWord;
	FString ReportStatement;

	int32 Lives = 0;
	int32 NumberOfGuessesMade = 0;

	bool InitialStart = true;
	bool BeginningNewWord = true;
	bool GameOver = false;
};
