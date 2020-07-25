def primes_upto(limit):
    prime = [True] * limit
    for n in range(2, limit):
        if prime[n]:
            yield n # n is a prime
            for c in range(n*n, limit, n):
                prime[c] = False # mark composites

letters = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
ps = {}
primes = list(primes_upto(542))
for i in range(1, len(letters)):
    ps[letters[i]] = i
ps["a"] = 27

def givesentence(s):
    yeet = 1
    for i in range(len(s)):
        yeet = yeet*primes[ps[s[i]]]
    return(yeet)

print(givesentence("greg"))