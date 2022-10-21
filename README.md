# Corner-Grocer-Inventory-Management
An exercise in combining C++ and Python to create a system for viewing and visualizing a store's inventory

This focus of this project was to create a program that combines the functionality of C++ and Python. It reads in a store's inventory data from a text file and allows the user to view, search, and create a histogram of the information. 

I successfully created functions in both C++ and Python to read in files, add the information to containers, evaluate the data, and display it to the user. Input validation is included to verify all user actions. It utilizes a simple command prompt, using color and other formatting options to create a clean and easily understood interface. The program counts instances of a sold item and stores that information. The user is then able to view the detailed list or search for specific inventory items. Also provided is the ability to generate a histogram of the inventory for a more visual presentation of the data.

The code could be enhanced by creating an option for the user to select a specific text file to read in. Currently the user can do this by simply altering the "filename" variable at the top of the Python file, but it would be more intuitive if it were done directly in the console window. I would also like to add additional ways to visualize the data beyond the histogram.

Integrating two languages was a challenge. The program runs from the C++ file, but calls Python functions to read in and analyze the data from the text file. The actual logic involved is not overly complicated, but setting up a system to work together did provide a challenge. Luckily I had access to materials that helped me complete the task. This project helped me develop an understanding of the benefits to utilizing more than one language, and the hands-on experience to replicate it in the future. I intend to further explore the possibilities.

I used function calls to handle most of the logic so main{} is simple and easy to read. All functions have provided comments to describe the functionality provided within. Naming conventions are descriptive and follow industry best standards.
