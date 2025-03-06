void SortInsert(unsigned int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && M[j - 1] > M[j]; j--) 
			swap(M[j - 1], M[j]);
}


