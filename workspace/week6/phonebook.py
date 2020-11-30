import sys

people = {
    "JINOOK": "347-506-0000",
    "SUNMI": "347-506-1111",
    "SUA": "347-828-2222",
    "JUA": "347-828-3333"
}

if "JINOOK" in people:
    print(f"Found {people['JINOOK']}")
    sys.exit(0)
print("Not found")
sys.exit(1)