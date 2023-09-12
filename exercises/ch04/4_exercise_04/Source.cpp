#include "..\std_lib_facilities.h"

int main()
{
	int start = 1;
	int end = 100;

	
	while (start != end) {
		int mid = (start + end) / 2 + 1;
		cout << "Is the number you are thinking of less than " << mid << " (y/n)\n";
		string input;
		cin >> input;

		if (input == "y") {
			end = mid - 1;
		}
		else if (input == "n") {
			start = mid;
		}
		else
			cout << "Invalid input\n";
	}
	cout << "Result: " << start << "\n";
}

//int main()
//{
//	int start = 1;
//	int end = 100;
//	int mid = (start + end) / 2;
//
//	while (start != end) {
//		cout << "Is the number you are thinking of less than " << mid << " (y/n)\n";
//		string input;
//		cin >> input;
//
//		if (input == "y") {
//			end = mid - 1;
//			if (end - start < 2)
//				mid -= 1;
//			else
//				mid = (start + end) / 2;
//		}
//		else if (input == "n") {
//			start = mid;
//			if (end - start < 2)
//				mid += 1;
//			else
//				mid = (start + end) / 2;
//		}
//		else
//			cout << "Invalid input\n";
//	}
//	cout << "Result: " << start << "\n";
//}