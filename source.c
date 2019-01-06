// Function to check if all subsets are filled or not
bool checkSum(int sumLeft[], int k)
{
	int r = true;
	for (int i = 0; i < k; i++)
	{
		if (sumLeft[i] != 0)
			r = false;
	}

	return r;
}

// Helper function for solving k partition problem
// It return true if there exists k subsets with given sum
bool subsetSum(int S[], int n, int sumLeft[], int A[], int k)
{
	// return true if subset is found
	if (checkSum(sumLeft, k))
		return true;

	// base case: no items left
	if (n < 0)
		return false;

	bool res = false;

	// consider current item S[n] and explore all possibilities
	// using backtracking
	for (int i = 0; i < k; i++)
	{
		if (!res && (sumLeft[i] - S[n]) >= 0)
		{
			// mark current element subset
			A[n] = i + 1;

			// add current item to i'th subset
			sumLeft[i] = sumLeft[i] - S[n];
			
			// recurse for remaining items
			res = subsetSum(S, n - 1, sumLeft, A, k);
			
			// backtrack - remove current item from i'th subset
			sumLeft[i] = sumLeft[i] + S[n];
		}
	}

	// return true if we get solution
	return res;
}

// Function for solving k-partition problem. It prints the subsets if
// set S[0..n-1] can be divided into k subsets with equal sum
void partition(int S[], int n, int k)
{
	// base case
	if (n < k)
	{
		std::cout << "k-Partition of set S is not Possible";
		return;
	}

	// get sum of all elements in the set
	int sum = std::accumulate(S, S + n, 0);

 	int A[n], sumLeft[k];
 
 	// create an array of size k for each subset and initialize it 
 	// by their expected sum i.e. sum/k
	for (int i = 0; i < k; i++)
		sumLeft[i] = sum/k;
	
	// return true if sum is divisible by k and the set S can
	// be divided into k subsets with equal sum
	bool res = !(sum % k) && subsetSum(S, n - 1, sumLeft, A, k);

	if (!res)
	{
		std::cout << "k-Partition of set S is not Possible";
		return;
	}

	// print all k-partitions
	for (int i = 0; i < k; i++)
	{
		std::cout << "Partition " << i << " is: ";
	   	for (int j = 0; j < n; j++)
	 		if (A[j] == i + 1)
	 			std::cout << S[j] << " ";
	 	std::cout << std::endl;
	}
}

// main function for k-partition problem
int main()
{
	// Input: set of integers
	int S[] = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 };

	// number of items in S
	int n = sizeof(S) / sizeof(S[0]);
	int k = 5;

	partition(S, n, k);

	return 0;
}
