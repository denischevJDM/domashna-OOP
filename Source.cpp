#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

class Student {
private:
	string name;
	list<int> ratings;
	string FN;

public:
	Student()
	{

	}

	Student(string name, string FN)
	{
		this->name = name;
		this->FN = FN;
	}

	Student(string name, string FN, const Student& obj)
	{
		this->name = obj.name;
		this->FN = obj.FN;
	}

	string getName() const
	{
		return name;
	}

	int getGrade() const
	{
		int sum = 0;
		for (int rating : ratings)
		{
			sum += rating;
		}
		return sum / ratings.size();
	}

	string getFN() const
	{
		return FN;
	}

	list<int> getRatings() const
	{
		return ratings;
	}

	void addScore(int score)
	{
		ratings.push_back(score);
	}
};

class Course {
private:
	string name;
	list<Student> students;

public:
	Course(string filename)
	{
		ifstream file(filename);
		getline(file, name);
		string line;
		while (getline(file, line))
		{
			string FN;
			string name;
			list<int> ratings;
			stringstream stream(line);
			getline(stream, FN, ',');
			getline(stream, name, ',');
			int rating;
			while (stream >> rating)
			{
				ratings.push_back(rating);
				if (stream.peek() == ',')
				{
					stream.ignore();
				}
			}
			addScores(FN, name, ratings);
		}
	}

	string getName() const
	{
		return name;
	}

	void addScore(string FN, int score)
	{
		for (Student& student : students)
		{
			if (student.getFN() == FN)
			{
				student.addScore(score);
			}
		}
	}

	void addScores(string FN, string name, list<int> ratings)
	{
		students.push_back(Student(name, FN));
		for (int rating : ratings) {
			addScore(FN, rating);
		}
	}

	void displayScores() const
	{
		cout << "Course: " << name << endl;
		for (const Student& student : students) {
			cout << "  Faculty number: " << student.getFN() << endl;
			cout << "  Name: " << student.getName() << endl;
			cout << "  Ratings: ";
			for (int rating : student.getRatings()) {
				cout << rating << " ";
			}
			cout << endl;
			cout << "  Average: " << student.getGrade() << endl;
		}
	}

	double finalAverage() const
	{
		int sum = 0;
		int count = 0;
		for (const Student& student : students) {
			sum += student.getGrade();
			count++;
		}
		return (double)sum / count;
	}
};

int main()
{
	Course c1("Math");
	Course c2("Physics");
	Course c3("Chemistry");
	Course c4("Biology");
}