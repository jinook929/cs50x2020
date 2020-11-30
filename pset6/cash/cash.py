# Import get_float function
from cs50 import get_float

# Set variables
cash = 0
count = 0

# Prompt float
while True:
    f = get_float("Change owed: ")
    if isinstance(f, float) and f >= 0:
        cash = format(f, '.2f')
        cash = float(cash)
        break

# Count number of coins
count += (int)(cash / .25)
cash = round(cash % .25, 2)
count += (int)(cash / .1)
cash = round(cash % .1, 2)
count += (int)(cash / .05)
cash = round(cash % .05, 2)
count += (int)(cash / .01)
cash = round(cash / .01, 2)

# Print number of coins
print(count)
