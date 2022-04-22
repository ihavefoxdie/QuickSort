#include <string>
#include <iostream>

bool check(std::string number)
{
	std::string nums = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-' };
	bool match = false;
	for (int i = 0; i < number.length(); i++)
	{
		for (int j = 0; j < 11; j++) {
			if (number[i] == nums[j]) {
				match = true;
				break;
			}
			match = false;
		}
		if (!match)
			throw number;
	}
	return 1;
}

void output(int* arr, int size)
{
	if (size != 0) {
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}
	else
		std::cout << "Empty\n";
}

int* input(int& size)													//code below is simply making sure user input consists of numbers only. it's rather primitive and work in progress
{
	int* arr = new int[1];	std::string input;
	int pos = 0;

	while (true) {
		std::cout << "To stop, type \"C\" character or simply press enter.\nInput: ";
		getline(std::cin, input);
		if (input[0] == 'c' || input[0] == 'C' || input[0] == NULL || (input[0] == '-' && input.length() == 1)) {
			if (size == 0)
			{
				std::cout << "The array is empty. Deleting.\n";
				delete[] arr;
				return NULL;
			}
			break;
		}
		try
		{
			check(input);
		}
		catch (std::string number)
		{
			system("cls");
			std::cout << "Not a number!\n";
			continue;
		}
		size++;
		int* arr1 = new int[size];
		if (pos != 0)
			for (int i = 0; i < size - 1; i++)
				arr1[i] = arr[i];
		arr1[size - 1] = std::stoi(input);
		delete[] arr;
		arr = arr1;
		pos++;
		system("cls");
	}
	return arr;
}

void quickSort(int* arr, int high, int low = 0)
{
	int marker = low;
	bool once = false;
	if (low < high)														//this line of code makes sure algorithm doesn't loop forever and/or doesn't try accessing uninitialized memory
	{
		for (int i = low; i < high; i++)
		{
			if (arr[i] > arr[high] && !once)							//determining the first replacement point in the array
			{
				marker = i;
				once = true;
			}
			if (arr[i] <= arr[high])									//if an element is lesser than the pivot, then it's being swapped with the element at the replacement point, that is incremented by 1 later
			{
				int temp = arr[marker];
				arr[marker] = arr[i];
				arr[i] = temp;
				marker++;
				//output(arr, 8); test for an array with 8 elements
			}
		}
		int temp = arr[marker];											//finilizing partitioning by placing the pivot to the right of the sorted elements
		arr[marker] = arr[high];
		arr[high] = temp;
		//output(arr, 8); test for an array with 8 elements

		quickSort(arr, marker - 1);										//sorting the left side from the older pivot
		quickSort(arr, high, marker + 1);								//sorting the right side from the older pivot
	}
}

int main()
{
	int size = 0;

	std::cout << "Fill the array.\n";									
	int* arr = input(size);
	output(arr, size);

	quickSort(arr, size - 1);											//the first pivot is the very last array element
	output(arr, size);

	return 0;
}

