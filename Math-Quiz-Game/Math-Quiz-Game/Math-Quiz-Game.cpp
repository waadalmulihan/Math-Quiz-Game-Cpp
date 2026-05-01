// Math-Quiz-Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>   
#include <cstdlib>    
#include <ctime> 

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

string GetQuestionLevelText(enQuestionsLevel QuestionsLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
    return arrQuestionLevelText[QuestionsLevel - 1];
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); // Green for correct answers.
    else
    {
        system("color 4F"); // Red for incorrect answers.
        cout << "\a"; // Plays an alert sound.
    }
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 0;
    do
    {
        cout << "How many Questions do you want to answer ? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions <= 1 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Enter Question Level [1]Easy,[2]Med,[3] Hard, [4]Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OpType = 0;
    do
    {
        cout << "Enter Question Level [1] Add,[2] Sub,[3] Mul, [4] Div,[5] Mix  ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType = enOperationType::Add;
    enQuestionsLevel QuestionLevel = enQuestionsLevel::EasyLevel;
    int CorrectAnswer = 0;
    float PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel = enQuestionsLevel::EasyLevel;
    enOperationType OpType = enOperationType::Add;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
    default:
        return Number1 + Number2;
    }
}

enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperationType();

    Question.OperationType = OpType;
    Question.QuestionLevel = QuestionLevel;
    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
    case enQuestionsLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
    }

    return Question;
}

void GenerateQuizzQuestion(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << endl;
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n_____________" << endl;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :-( \n";
        cout << "The right answer is: ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";

    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer :-) \n";
    }
    cout << endl;

    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quizz, QuestionNumber);

    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
    {
        system("color 2F");
        return "PASS :-)";
    }
    else
    {
        system("color 4F");
        return "Fail :-(";
    }
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "_____________________________________________\n\n";
    cout << "Final Results is " << GetFinalResultsText(Quizz.isPass);
    cout << "_____________________________________________\n\n";

    cout << "Number of Question:  " << (Quizz.NumberOfQuestions) << endl;
    cout << "Questions Level   : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType            :   " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers:  " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "________________________________\n";

}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();  // Set a fixed number of questions.
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestion(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);

}

static void ResetScreen()
{
    system("cls");
    system("color 0F");

}

static void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();

        cout << endl << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}