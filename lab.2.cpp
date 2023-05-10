#include <iostream>
#include "ParticipantOfTheCompetition.hpp"
#include "sortMethods.hpp"
#include <chrono>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>


ParticipantsOfTheCompetition::ParticipantsOfTheCompetition(const std::string& lastName, const std::string& firstName, const std::string& category, const std::string& country, const Date& birthYear, const unsigned short& idParticipant)
    :last_name(lastName), first_name(firstName), _category(category), _country(country), birth_year(birthYear), id_Participant(idParticipant)
{
}

ParticipantsOfTheCompetition::ParticipantsOfTheCompetition(const ParticipantsOfTheCompetition& participant) : last_name(participant.last_name), first_name(participant.first_name), _category(participant._category), _country(participant._country), birth_year(participant.birth_year), id_Participant(participant.id_Participant)
{
}

Date::Date(const unsigned short& _day, const unsigned short& _month, const unsigned short& _year)
    :day(_day), month(_month), year(_year)
{
}

Date::Date(const Date& birthYear) : day(birthYear.day), month(birthYear.month), year(birthYear.year)
{
}

const ParticipantsOfTheCompetition& ParticipantsOfTheCompetition::operator=(const ParticipantsOfTheCompetition& Participant)
{
    first_name = Participant.first_name;
    last_name = Participant.last_name;
    _category = Participant._category;
    _country = Participant._country;
    birth_year = Participant.birth_year;
    id_Participant = Participant.id_Participant;

    return *this;
}

bool ParticipantsOfTheCompetition::operator==(const ParticipantsOfTheCompetition& Participant)
{
    return first_name == Participant.first_name && last_name == Participant.last_name && _category == Participant._category && _country == Participant._country && birth_year == Participant.birth_year && id_Participant == Participant.id_Participant;
}

bool Date::operator==(const Date& birthYear)
{
    return day == birthYear.day && month == birthYear.month && year == birthYear.year;
}

const Date& Date::operator=(const Date& birthYear)
{
    day = birthYear.day;
    month = birthYear.month;
    year = birthYear.year;

    return *this;
}

std::string Date::toString() const
{
    return std::string();
}

unsigned short Date::Day() const
{
    return day;
}

unsigned short Date::Month() const
{
    return month;
}

unsigned short Date::Year() const
{
    return year;
}

std::string ParticipantsOfTheCompetition::FirstName() const
{
    return first_name;
}

std::string ParticipantsOfTheCompetition::LastName() const
{
    return last_name;
}

std::string ParticipantsOfTheCompetition::Country() const
{
    return _country;
}

std::string ParticipantsOfTheCompetition::Category() const
{
    return _category;
}

Date ParticipantsOfTheCompetition::BirthYear() const
{
    return birth_year;
}

unsigned short ParticipantsOfTheCompetition::IDParticipant() const
{
    return id_Participant;
}

std::istream& operator>>(std::istream& in, Date& birthYear)
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
    char delimeter;

    in >> month >> delimeter >> day >> delimeter >> year;

    birthYear = Date(day, month, year);

    return in;
}

std::istream& operator>>(std::istream& in, ParticipantsOfTheCompetition& Participant)
{
    std::string lastName;
    getline(in, lastName, ',');
    std::string firstName;
    getline(in, firstName, ',');
    std::string country;
    getline(in, country, ',');
    std::string category;
    getline(in, category, ',');
    Date birthYear;
    in >> birthYear;
    in.ignore();
    unsigned short idParticipants;
    in >> idParticipants;

    Participant = ParticipantsOfTheCompetition(lastName, firstName, category, country, birthYear, idParticipants);
    std::string end;
    getline(in, end);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Date& birthYear)
{
    out << birthYear.Month() << "/" << birthYear.Day() << "/" << birthYear.Year();

    return out;
}

std::ostream& operator<<(std::ostream& out, const ParticipantsOfTheCompetition& Participant)
{
    out << Participant.LastName() << "\t" << Participant.FirstName() << "\t" << Participant.Country() << "\t" << Participant.Category() << "\t" << Participant.BirthYear() << "\t" << Participant.IDParticipant() << std::endl;

    return out;
}

void printList(const std::vector<ParticipantsOfTheCompetition>& ListOfParticipants)
{
    for (size_t i = 0; i < ListOfParticipants.size(); i++)
    {
        std::cout << ListOfParticipants.at(i);
    }
}


void bubbleSort(std::vector<ParticipantsOfTheCompetition>& ListOfParticipants)
{
    auto start = std::chrono::high_resolution_clock::now();
    size_t comparisons = 0;
    size_t swaps = 0;

    for (size_t i = 0; i < ListOfParticipants.size(); i++)
    {
        bool isSorted = true;
        for (size_t j = 0; j < ListOfParticipants.size() - (i + 1); j++)
        {
            comparisons++;
            if (ListOfParticipants.at(j).LastName() > ListOfParticipants.at(j + 1).LastName())
            {
                isSorted = false;
                ParticipantsOfTheCompetition tmp = ListOfParticipants.at(j);
                ListOfParticipants.at(j) = ListOfParticipants.at(j + 1);
                ListOfParticipants.at(j + 1) = tmp;
                swaps++;
            }
        }
        if (isSorted)
        {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    printList(ListOfParticipants);
    std::cout << "\nNumber of comparisons: " << comparisons << std::endl;
    std::cout << "Number of permutations: " << swaps << std::endl;
    std::cout << "Lead time: " << duration.count() << " ms" << std::endl;

}

void insertionSort(std::vector<ParticipantsOfTheCompetition>& ListOfParticipants)
{
    auto start = std::chrono::high_resolution_clock::now();
    size_t swaps = 0;
    size_t comparisons = 0;
    for (size_t i = 1; i < ListOfParticipants.size(); i++)
    {
        for (size_t j = i; j > 0 && ListOfParticipants.at(j - 1).LastName() > ListOfParticipants.at(j).LastName(); j--)
        {
            std::swap(ListOfParticipants.at(j - 1), ListOfParticipants.at(j));
            swaps++;
            comparisons++;
        }
        comparisons++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    printList(ListOfParticipants);
    std::cout << "\nNumber of comparisons: " << comparisons << std::endl;
    std::cout << "Number of permutations: " << swaps << std::endl;
    std::cout << "Lead time: " << duration.count() << " ms" << std::endl;
}

void selectionSort(std::vector<ParticipantsOfTheCompetition>& ListOfParticipants)
{
    auto start = std::chrono::high_resolution_clock::now();
    size_t comparisons = 0;
    size_t swaps = 0;

    for (size_t i = 0; i < ListOfParticipants.size() - 1; i++)
    {
        for (size_t j = i + 1; j < ListOfParticipants.size(); j++)
        {
            if (ListOfParticipants.at(j).LastName() < ListOfParticipants.at(i).LastName())
            {
                std::swap(ListOfParticipants.at(i), ListOfParticipants.at(j));
                swaps++;
            }
            comparisons++;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    printList(ListOfParticipants);
    std::cout << "\nNumber of comparisons: " << comparisons << std::endl;
    std::cout << "Number of permutations: " << swaps << std::endl;
    std::cout << "Lead time: " << duration.count() << " ms" << std::endl;
}


int main()
{
    setlocale(LC_ALL, "Rus");

    std::string path = "D:/MyCoolProject1/MyCoolLab1/MOCK_DATA.csv";

    std::ifstream file(path);

    std::vector<ParticipantsOfTheCompetition> Participants;

    //Проверка на открытие файла
    if (!file.is_open())
    {
        std::cout << "File opening error!" << std::endl;
    }
    else
    {
        //Пока файл не дошёл до конца
        while (!file.eof())
        {
            //Создаём временную переменную
            ParticipantsOfTheCompetition tmp;

            //Считываем из файла значения во временную переменную
            file >> tmp;

            //Если достигнут конец файла, завершаем работу цикла
            if (file.eof())
            {
                break;
            }

            //Записываем участника в список
            Participants.push_back(tmp);
        }
    }
    file.close();

    unsigned short number;
    std::cout << "1) Bubble sort\n";
    std::cout << "2) Insertion sort\n";
    std::cout << "3) Selection sort\n";
    std::cout << "Choose any options: ";
    std::cin >> number;
    std::cout << "\n";
    switch (number)
    {
        case 1:
        {
            bubbleSort(Participants);
            break;
        }

        case 2:
        {
            insertionSort(Participants);
            break;
        }

        case 3:
        {
            selectionSort(Participants);
            break;
        }
    }

    system("pause>nul");
    return 0;
}