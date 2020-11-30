from cs50 import get_string

text = get_string("Text: ")

lCount = 0
wCount = 1
sCount = 0

for letter in text:
    if (ord(letter) >= 65 and ord(letter) <= 90) or (ord(letter) >= 97 and ord(letter) <= 122):
        lCount += 1
    if ord(letter) == 32:
        wCount += 1
    if ord(letter) == 33 or ord(letter) == 46 or ord(letter) == 63:
        sCount += 1

# print(lCount)
# print(wCount)
# print(sCount)


def colemanLiauIndex(l, w, s):
    return 0.0588 * (l * 100 / w) - 0.296 * (s * 100 / w) - 15.8


index = round(colemanLiauIndex(lCount, wCount, sCount))
# print(index)


if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade %i" % index)