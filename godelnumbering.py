def primes_upto(dd):
    prime = [True] * dd
    for n in range(2, dd):
        if prime[n]:
            yield n
            for c in range(n*n, dd, n):
                prime[c] = False

letters = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
ps = {}
primes = list(primes_upto(542))
for i in range(1, len(letters)):
    ps[letters[i]] = i
ps["a"] = 27

def givesentence(s):
    ddd = 1
    for i in range(len(s)):
        yeet = yeet*primes[ps[s[i]]]
    return(ddd)

    