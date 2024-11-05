# ATM simulator
This is a project I and four other students made for a course at Oulu University of Applied Sciences in Fall 2023.
---
## Project description
This project uses an electronic card reader, and multiple cards with different IDs coded in them.
### Card reader
Each card has a unique id number, that the card reader can read and identify. In the project, card id numbers are stored in a database, and each number can be assigned with a hashed password and bank account details.
### Backend
In the backend we define http requests that can access the database. To get access to any sensitive account information, the user has to be logged in to the correct account, which is implemented with authentication tokens.

## Project file structure
- **DLLPinCode** - DLL for verifying pin codes
- **DLLRestApi** - DLL for making REST commands through backend to database
- **DLLSerialPort** - DLL for identifying and verifying card reader (This demo has a virtual card for demonstration)

- **frontend** - All graphical user interface elements.

- **backend** - Node.js backend as an interface between frontend and the database. 

- **pankkidb_v2_blacklist.sql** - Dump file for the database. Needs to be hosted, and .env file must be created to use. .env file must include SQL_SERVER, PORT, and MY_TOKEN constants

- **other .sql files** - procedures for manipulating the database

## Database

<img src="ER_diagrammi_v4.png">

The database was hosted using [Uniform Server](http://www.uniformserver.com/) to host it locally.

## Contributions
The project was made with a tight group, and often there were multiple people solving a single problem. We also intentionally divided the work so that each person could get their hands on each part of the application for learning purposes. This resulted in a less clear indication of 
I (Santeri) was the main contributor to account money transfer functions. This included SQL queries, backend html queries and frontend UI.
