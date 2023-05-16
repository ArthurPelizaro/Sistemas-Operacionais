import sys
import threading

def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True

def print_primes(n):
    primes = [str(num) for num in range(1, n+1) if is_prime(num)]
    print(' '.join(primes))

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Uso: python primos.py <numero>')
        sys.exit(1)

    try:
        num = int(sys.argv[1])
        if num < 1:
            print('O número deve ser maior ou igual a 1.')
            sys.exit(1)
    except ValueError:
        print('O número fornecido não é válido.')
        sys.exit(1)

    t = threading.Thread(target=print_primes, args=(num,))
    t.start()
    t.join()