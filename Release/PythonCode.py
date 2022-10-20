# File to be read in. Can be changed to read any file with the correct format
filename = 'items.txt'

# Opens the text file and reads in the data
def readFile(filename):
    
    lines = None
    
    with open(filename, 'r') as file:
        lines = file.readlines()
        return lines

# Reads text file data into a dictionary
def getInventory():

    inventory = {}
    items = readFile(filename) 
    
    # Loops through the list of items, strips newline characters, and calculates inventory
    for item in items:
        item = item.strip() 
        if item in inventory:
            inventory[item] += 1
        else:
            inventory[item] = 1      
    return inventory

# Reads in inventory and loops through entries to output to console
def determineInventory():
    
    inventory = getInventory()
    
    for key, value in inventory.items():
        print(key, value)
  
# Searches dictionary for userInput and returns number of times item was purchased
def determineFrequency(userInput):
    
    inventory = getInventory()
    frequency = None
    
    # Returns number of times userInput has sold or returns 0 for no results
    for key in inventory:
        if key in userInput.capitalize(): # Accounts for capitalization
            frequency = inventory[key]
            break
        else:
            frequency = 0
    return frequency

# Loops through inventory dictionary and copies data to frequency.dat
def output():
    
    inventory = getInventory()
 
    with open("frequency.dat", 'w') as f:
        # Writes each entry to new file in the correct format, converting the frequency to a string value 
        for key, value in inventory.items(): 
            f.write(key)
            f.write(" ")
            f.write(str(value))
            f.write("\n")



