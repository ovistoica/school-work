import sys
import io
import json

# Coffee maker's resources - the values represent the fill percents
resources = {"water": 100, "coffee": 100, "milk": 100}

espresso = {}
americano = {}
cappuccino = {}
with open('/home/stoica/workspace/ASC/lab1/skel/recipes/espresso.txt', 'r') as f: 
    next(f)
    for line in  f: 
        line = line.split("=")
        espresso[line[0]] = int(line[1])

with open('./recipes/cappuccino.txt', 'r') as f: 
    next(f)
    for line in  f: 
        line = line.split("=")
        cappuccino[line[0]] = int(line[1])

with open('./recipes/americano.txt', 'r') as f: 
    next(f)
    for line in  f: 
        line = line.split("=")
        americano[line[0]] = int(line[1])

print espresso
print americano
print cappuccino

def list_recip(): 
    print "americano espresson cappuccino"

def status_ingrid():
    print "water:" + str(resources["water"]) + "%"
    print "coffee:" + str(resources["coffee"]) + "%"
    print "milk:" + str(resources["milk"]) + "%"

def make_coffee(coffee_type):
    if coffee_type == "espresso":
        diff1 = resources["water"] - espresso["water"]
        diff2 = resources["coffee"] - espresso["coffee"]
        if diff1 < 0 or diff2 < 0:
            print "Not enough resources"
        else:
            resources["water"] -= espresso["water"] 
            resources["coffee"] -= espresso["coffee"] 
            print "Here is your " + coffee_type

    if coffee_type == "americano":
        diff1 = resources["water"] - americano["water"]
        diff2 = resources["coffee"] - americano["coffee"]
        if diff1 < 0 or diff2 < 0:
            print "Not enough resources"
        else:
            resources["water"] -= americano["water"] 
            resources["coffee"] -= americano["coffee"] 
            print "Here is your " + coffee_type

    elif coffee_type == "cappuccino":
        diff1 = resources["water"] - cappuccino["water"]
        diff2 = resources["coffee"] - cappuccino["coffee"]
        diff3 = resources["milk"] - cappuccino["milk"]
        if diff1 < 0 or diff2 < 0 or diff3 < 0:
            print "Not enough resources"
        else:
            resources["water"] -= cappuccino["water"]
            resources["coffee"] -= cappuccino["coffee"]
            resources["milk"] -= cappuccino["milk"]
            print "Here is your " + coffee_type

def refill(refill_mode):
    if refill_mode == 'all':
        resources["water"] = 100
        resources["coffee"] = 100
        resources["milk"] = 100
    elif refill_mode == 'coffee':
        resources["coffee"] = 100
    elif refill_mode == 'water':
        resources["water"] = 100
    elif refill_mode == 'milk':
        resources["milk"] = 100


    

print "I'm a smart coffee maker"
while True: 
    print "Enter a command"
    user_command = sys.stdin.readline().strip()
    user_command = user_command.split(" ")
    if user_command[0] == "list": 
        list_recip()
    elif user_command[0] == "status":
        status_ingrid()
    elif user_command[0] == "make":
        make_coffee(user_command[1])
    elif user_command[0] == 'refill':
        if len(user_command) == 1: 
            print "Which resource? Type 'all' for refilling everything"
        else: 
            refill(user_command[1])
    elif user_command[0] == "exit":
        sys.exit()

""" 
Implement the coffee maker's commands. Interact with the user via stdin and print to stdout.

Requirements:
    - use functions
    - use __main__ code block
    - access and modify dicts and/or lists
    - use at least once some string formatting (e.g. functions such as strip(), lower(), 
    format()) and types of printing (e.g. "%s %s" % tuple(["a", "b"]) prints "a b"
    - BONUS: read the coffee recipes from a file, put the file-handling code in another module 
    and import it (see the recipes/ folder)
    
There's a section in the lab with syntax and examples for each requirement.

Feel free to define more commands, other coffee types, more resources if you'd like and have time.
"""

"""
Tips:
*  Start by showing a message to the user to enter a command, remove our initial messages
*  Keep types of available coffees in a data structure such as a list or dict
e.g. a dict with coffee name as a key and another dict with resource mappings (resource:percent) 
as value
"""

# Commands
EXIT = "exit"
LIST_COFFEES = "list"
MAKE_COFFEE = "make"  #!!! when making coffee you must first check that you have enough resources!
HELP = "help"
REFILL = "refill"
RESOURCE_STATUS = "status"
commands = [EXIT, LIST_COFFEES, MAKE_COFFEE, REFILL, RESOURCE_STATUS, HELP]

"""
Example result/interactions:

I'm a smart coffee maker
Enter command:	
list
americano, cappuccino, espresso
Enter command:	
status
water: 100%
coffee: 100%
milk: 100%
Enter command:	
make
Which coffee?
espresso
Here's your espresso!
Enter command:	
refill
Which resource? Type 'all' for refilling everything
water
water: 100%
coffee: 90%
milk: 100%
Enter command:	
exit
"""

# Coffee examples
ESPRESSO = "espresso"
AMERICANO = "americano"
CAPPUCCINO = "cappuccino"

# Resources examples
WATER = "water"
COFFEE = "coffee"
MILK = "milk"
