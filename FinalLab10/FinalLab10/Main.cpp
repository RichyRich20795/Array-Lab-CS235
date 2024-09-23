#include <iostream>
#include <fstream>
#include <sstream>
#include "QS.h"
using namespace std;

int main(int argc, char* argv[]) 
{
	//Opening input and output file to be read throughout the code
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	QS<int> quickArray;
	string line;
	int number;

	while (getline(in, line)) 
	{
		string newLine;

		try 
		{
			if (line.size() == 0) continue;

			istringstream ins(line);
			ins >> newLine;
			out << newLine << " ";

			if (newLine == "QuickSort") 
			{
				ins >> number;
				quickArray.setSize(number);
				out << number << " OK";
			}

			else if (newLine == "AddToArray") 
			{
				string quickLine;
				number = 0;
				while (ins >> number) 
				{
					if (!quickArray.addElement(number)) 
					{
						throw string("Invalid Input");
						break;
					}
					quickLine += to_string(number) + ",";
				}
				quickLine = quickLine.substr(0, quickLine.length() - 1);
				out << " " << quickLine << " OK";
			}

			else if (newLine == "Capacity") 
			{
				out << quickArray.capacity();
			}

			else if (newLine == "Clear") 
			{
				quickArray.clear();
				out << "OK";
			}

			else if (newLine == "Size") 
			{
				out << quickArray.size();
			}

			else if (newLine == "Sort") 
			{
				size_t left = 0;
				size_t right = 0;
				ins >> left >> right;

				if (quickArray.sort(left, right)) 
				{
					out << left << "," << right << " OK";
				}
				else { throw string("Invalid Input"); }
			}

			else if (newLine == "SortAll") 
			{
				if (quickArray.sortAll()) 
				{
					out << "OK";
				}
				else { throw string("Invalid Input"); }
			}

			else if (newLine == "MedianOfThree") 
			{
				int left = 0;
				int right = 0;
				ins >> left >> right;
				out << left << "," << right << " = ";
				if (!quickArray.checkNoPivot(left, right)) { out << "-1"; }
				else
				{
					out << quickArray.medianOfThree(left, right);
				}
			}

			else if (newLine == "Partition") 
			{
				int left = 0;
				int right = 0;
				int pivot = 0;
				ins >> left >> right >> pivot;
				out << left << "," << right << "," << pivot << " = ";
				if (!quickArray.checkWithPivot(left, right, pivot)) { out << "-1"; }
				else
				{
					out << quickArray.partition(left, right, pivot);
				}
			}

			else if (newLine == "PrintArray") 
			{
				if (quickArray.size() == 0) { out << "Empty"; }
				else { out << quickArray; }
			}

			else if (newLine == "Stats") 
			{
		
			}

			else 
			{
				throw string("Invalid Input");
			}

			out << endl;
		}
		catch (string errorString) 
		{
			out << errorString << endl;
		}
	}

	return 0;
}