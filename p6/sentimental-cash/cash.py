while True:
    changeOwed = int(input("Change Owed: "))
    if changeOwed >= 0:
        break

changeOwedCents = round(changeOwed * 100)

coins = 0

while changeOwedCents > 0:
    if changeOwedCents >= 25:
        changeOwedCents -= 25
        coins += 1

    elif changeOwedCents >= 10:
        changeOwedCents -= 10
        coins += 1

    elif changeOwedCents >= 5:
        changeOwedCents -= 5
        coins += 1

    else:
        changeOwedCents -= 1
        coins += 1

print(coins)
