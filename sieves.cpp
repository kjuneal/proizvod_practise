#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Эратосфен
vector<int> sieve(int n) {
	bool* prime = new bool[n + 1];
	memset(prime, true, sizeof(prime));
	for (int p = 2; p * p <= n; p++) {
		if (prime[p]) {
			for (int i = p * p; i <= n; i += p)
				prime[i] = false;
		}
	}
	std::vector<int> primes;
	for (int p = 2; p <= n; p++)
		if (prime[p])
			primes.push_back(p);
	return primes;
}
// Сундарам
vector<int> Sundaram(int n) {
	vector<int> numbers(n+1), primeNumbers;
	for (int i = 1; i < n+1; i++) {
		numbers[i] = i;
	}
	for (int i = 1; i <= (sqrt(2*n+1)-1)/2; i++) {
		for (int j = i; j <= (n-i)/(2*i+1); j++) {
			numbers[i + j + 2 * i * j] = 0;
		}
	}
	for (int i = 1; i < n+1; i++) {
		if (numbers[i] != 0)
			primeNumbers.push_back(numbers[i]*2+1);
	}
	return primeNumbers;
}
