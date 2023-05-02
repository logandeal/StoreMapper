# StoreMapper

# ECE3220 Semester Project
- Logan Deal
- Ryan Milewski   
- Edison Briney

# Features
  - When run, the program will execute a text menu from which the user will be prompted to either add an item to their shopping list, remove an item from their shopping list, view their current shopping list, find the shortest path through the grocery store while getting every item on their list, and exit the program. 
  
  - If the user chooses to add an item to their shopping list, another text menu will be displayed, from which they will be given a list of items that are in the grocery store that they could choose from.
  
  - Removing an item from their shopping works identically to adding an item, but the items displayed will be the items currently in the shopping list.
  
  - Viewing the current shopping list prints out every item in the current shopping list
  
  - If the user chooses to find the shortest path through the grocery store, they will be given a choice of multiple different search algorithms that would search through the store. 
  
# Functionality
  - Singleton Design Pattern for GroceryStore graph

  - Strategy Design Pattern for choosing the search algorithm

  - Exception Handling in main

  - Unit tests for all major aspects of code

# Dependencies
  - GTest

  - Make

  
# How to run
  - To run the whole program, open up the StoreMapper folder, and run make. The executable will be created, then all that needs to be done is run ./<placeholdername>
  
  - To run the tests, you must first cd into the test folder, run make, then run ./<placeholdertest>
  
  - You can also pull a docker image with all dependencies pre-installed from https://hub.docker.com/r/rmilewski4/storemapper