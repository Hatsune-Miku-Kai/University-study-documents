import re

number_digit = 3
guess_time = 10

number = 701
nomatch = True
times = 1

while times<=10:
    nomatch = True
    print('Guess #{}: '.format(times))
    guess_number = input('请输入数字\n')
    pattern = '^\d{3}$'
    while (not re.match(pattern,guess_number)):
            guess_number = input('请输入三位数字\n')

    times += 1
    if int(guess_number) == number:
        print('you win!\n')
        break
    else:
        for i in range(number_digit):
            for j in range(number_digit):
                if guess_number[i] ==(str(number))[j]:
                    nomatch = False
                    if i == j:
                        print('fermi ')
                    else:
                        print('pico ')
    
        if(nomatch):
            print('bagels')

