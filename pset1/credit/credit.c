#include <cs50.h>
#include <stdio.h>

void luhnsCheck(long cardNumber, string cardCompany);

int main(void)
{
    long cardNumber, temp;
    int digits = 0;
    
    // Prompt a card number and check its validity
    do
    {
        cardNumber = get_long("Number: ");
        temp = cardNumber;
    }
    while (cardNumber < 1 || cardNumber > 9999999999999999);
    
    // Count the digits of the card number
    while (temp >= 1)
    {
        temp = temp / 10;
        digits++;
    }
    
    // Check the validity of the card and its company
    // AMEX?
    if (digits == 15)
    {
        if (cardNumber / 10000000000000 == 34 || cardNumber / 10000000000000 == 37)
        {
            luhnsCheck(cardNumber, "AMEX");
        } 
        else
        {
            printf("INVALID\n");
        }
    }
    // VISA[13 digits]?
    else if (digits == 13)
    {
        if (cardNumber / 1000000000000 == 4)
        {
            luhnsCheck(cardNumber, "VISA");
        } 
        else
        {
            printf("INVALID\n");
        }
    }
    // VISA[16 digits] or MASTERCARD?
    else if (digits == 16)
    {
        // VISA[16 digits]?
        if (cardNumber / 1000000000000000 == 4)
        {
            luhnsCheck(cardNumber, "VISA");
        } 
        // MASTERCARD?
        else if (cardNumber / 100000000000000 >= 51 && cardNumber / 100000000000000 <= 55)
        {
            luhnsCheck(cardNumber, "MASTERCARD");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Luhn’s Algorithm check
void luhnsCheck(long cardNumber, string cardCompany) 
{
    int luhnsTotal = 0;
    int i = 1;
    
    // Luhn's Algorithm Addition
    while (cardNumber > 1)
    {
        // Add the even-numberth-digits(from-last)
        if (i % 2 == 0)
        {
            // when its twice-value is less than 10
            if (cardNumber % 10 * 2 < 10)
            {
                luhnsTotal += cardNumber % 10 * 2;
            }
            // when its twice-value is greater than or equal to 10
            else
            {
                luhnsTotal += 1 + (cardNumber % 10 * 2) % 10;
            }
        }
        // Add the odd-numberth-digits(from-last)
        else
        {
            luhnsTotal += cardNumber % 10;
        }
        
        // Prepare for the next digit
        cardNumber /= 10;
        
        // Increment digit position from the last
        i++;
    }
    
    // Tell Luhn’s Algorithm check result
    if (luhnsTotal % 10 == 0)
    {
        printf("%s\n", cardCompany);
    }
    else
    {
        printf("INVALID\n");
    }
}