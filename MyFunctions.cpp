/*
Faizan Virani
Coding Time at the Inventory
4/5/22
Extra: FILES (I regret this)
*/
#include "MyFunctions.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstring>

bool accounts() {
  ifstream students;
  students.open("Names.txt");

  string c = "";
  getline(students, c);
  if (c.length() > 0) {
    students.close();
    return true;
  }
  return false;
}

void getInformation() {
  bool foundAccount= false;
  
  string itemName = "";
  string color = "";
  string answerHolder;
  string lines;
  string donor;
  
  int stock;
  int model;
  int shelf;
  int randomNumber;
  
  double price;

  vector<string> copyFile = {};

  cout << "\nEnter item name (Case sensitive! This is how it will be entered into the database.): ";
  getline(cin, itemName);

  cout << "\nWas " << itemName << " donated (y/n)? ";
  getline(cin, answerHolder);
  if(answerHolder[0] == 'y' || answerHolder[0] == 'Y') {
    cout << "\nEnter donor name: ";
    getline(cin, donor);
  } else {
    cout << "\nDonor set as 'none'";
    donor = "none";
  }

  do {
    cout << "\nEnter the stock of  '" << itemName << "' (Integer greater than 0!): ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) < 1) {
      cout << "\nInvalid stock amount.";
      answerHolder = "a";
      }
    }
  } while(!validInt(answerHolder));
  stock = stoi(answerHolder);

  do {
    cout << "\nEnter model (year) of '" << itemName << "': ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) > 2023) {
      cout << "\nInvalid model.";
      answerHolder = "a";
      }
    }
  } while(!validInt(answerHolder));
  model = stoi(answerHolder);

  cout << "\nEnter the color of '" << itemName << "': ";
  getline(cin, color);

  do {
    cout << "\nEnter the price of '" << itemName << "': $";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) < 1) {
      cout << "\nInvalid price.";
      answerHolder = "a";
      }
    }
  } while(!validDouble(answerHolder));
  price = stod(answerHolder);

  do {
    cout << "\nEnter the shelf number of  '" << itemName << "' (Integer greater than 0!): ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) < 1) {
      cout << "\nInvalid shelf number.";
      answerHolder = "a";
      }
    }
  } while(!validInt(answerHolder));
  shelf = stoi(answerHolder);
  
  // Write to file
  string thisfilename = itemName + ".txt";
  
  std::ofstream ofs;
  ofs.open(thisfilename, std::ofstream::out | std::ofstream::trunc);
  ofs.close();

  randomNumber = randomize();
    
  fstream student;
  student.open (thisfilename);
  student << "ID: " << randomNumber << endl;
  student << "Item Name: " << itemName << endl;
  student << "Stock: " << stock << endl;
  student << "Color: " << color << endl;
  student << "Price: $" << price << endl;
  student << "Shelf Number: " << shelf << endl;
  student << "Donor: " << donor << endl;
  student.close();

  ifstream copier("Names.txt");
    if (copier.is_open()) {
      while (getline(copier, lines)) {
        copyFile.push_back(lines);
      }
      copier.close();
  }
  
  for (int i = 0; i < copyFile.size(); i++) {
    if (copyFile[i] == itemName) {
      foundAccount = true;
      break;
    } else {
      foundAccount = false;
    }
  }

  if (!foundAccount) {
    student.open("Names.txt", ios::app);
    student << itemName << endl;
    student.close();
  }
}

bool validInt(string a) {
  for (int i = 0; i < a.length(); i++) {
    if (!isdigit(a[i])) {
      return false;
      break;
    }
  }
  return true;
}

bool validDouble(string a) {
  for (int i = 0; i < a.length(); i++) {
    if (!isdigit(a[i]) && to_string(a[i]) != "46") {
      return false;
      break;
    }
  }
  return true;
}

void sortInformation() {
  int choice;
  int temp;
  
  string lines;
  string answerHolder;
  string stringTemp;
  
  vector<string> namesList = {};
  vector<int> stock = {};
  vector<string> donators = {};
  vector<string> itemName = {};
  vector<int> ids = {};

  ifstream copier("Names.txt");
    if (copier.is_open()) {
      while (getline(copier, lines)) {
        namesList.push_back(lines);
      }
      copier.close();
  }
  
  //STOCK
  fstream thing("Names.txt");
  for(int i = 0; i < namesList.size(); i++) {
    getline(thing, lines);
    string blob = lines.append(".txt");

    fstream lol(blob);

    while(getline(lol, lines)) {
      if (lines.find("Stock:") != std::string::npos) {
        break;
      }
    }

    stock.push_back(stoi(lines.substr(lines.find(": ") + 2, lines.length() - 1)));
  }
  thing.close();

  //DONATOR
  fstream thing2("Names.txt");
  for(int i = 0; i < namesList.size(); i++) {
    getline(thing2, lines);
    string blob = lines.append(".txt");

    fstream lol(blob);

    while(getline(lol, lines)) {
      if (lines.find("Donor:") != std::string::npos) {
        break;
      }
    }

    donators.push_back(lines.substr(lines.find(": ") + 2, lines.length() - 1));
  }
  thing2.close();

  //ITEM NAMES
  fstream thing3("Names.txt");
  for(int i = 0; i < namesList.size(); i++) {
    getline(thing3, lines);
    string blob = lines.append(".txt");

    fstream lol(blob);

    while(getline(lol, lines)) {
      if (lines.find("Item Name:") != std::string::npos) {
        break;
      }
    }

    itemName.push_back(lines.substr(lines.find(": ") + 2, lines.length() - 1));
  }
  thing3.close();

  //IDS
  fstream thing4("Names.txt");
  for(int i = 0; i < namesList.size(); i++) {
    getline(thing4, lines);
    string blob = lines.append(".txt");

    fstream lol(blob);

    while(getline(lol, lines)) {
      if (lines.find("ID:") != std::string::npos) {
        break;
      }
    }

    ids.push_back(stoi(lines.substr(lines.find(": ") + 2, lines.length() - 1)));
  }
  thing4.close();

  //GET SORT TYPE
  do {
    cout << "\n[1] Item Name\n[2] Donator \n[3] ID (Greatest to least)\n[4] Stock (Greatest to least)\nEnter the number associated with the option you would like to sort by: ";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) < 1 || stoi(answerHolder) > 4) {
      cout << "\nInvalid choice.";
      answerHolder = "a";
      }
    }
  } while(!validInt(answerHolder));
  choice = stoi(answerHolder);

  //SORT
  switch(choice) {
    //THESE USE SHELL SORTS
    case 1: {
      int flag = 1;
      int d = itemName.size();
      while(flag || (d > 1)) {
        flag = 0;
        d = (d+1) / 2;
        for (int i = 0; i < (itemName.size() - d); i++) {
          if (itemName[i + d] < itemName[i]) {
            stringTemp = itemName[i + d];
            itemName[i + d] = itemName[i];
            itemName[i] = stringTemp;

            stringTemp = namesList[i + d];
            namesList[i + d] = namesList[i];
            namesList[i] = stringTemp;
            flag = 1;

            cout << "\nSwap performed!\n";
          }
        }
      }
      cout << endl << "Sorted!";
      break;
    }
    case 2: {
      int flag = 1;
      int d = donators.size();
      while(flag || (d > 1)) {
        flag = 0;
        d = (d+1) / 2;
        for (int i = 0; i < (donators.size() - d); i++) {
          if (donators[i + d] < donators[i]) {
            stringTemp = donators[i + d];
            donators[i + d] = donators[i];
            donators[i] = stringTemp;

            stringTemp = namesList[i + d];
            namesList[i + d] = namesList[i];
            namesList[i] = stringTemp;
            flag = 1;
          }
        }
      }
      cout << endl << "Sorted!";
      break;
    }
    //THESE USE EXCHANGE SORTS
    case 3: {

      for (int i = 0; i < (ids.size() -1); i++) {
        for(int j = (i + 1); j < ids.size(); j++) {
        if (ids[i] < ids[j]) {
          temp = ids[i];
          ids[i] = ids[j];
          ids[j] = temp;

          stringTemp = namesList[i];
          namesList[i] = namesList[j];
          namesList[j] = stringTemp;
          }
        }
      }
      cout << endl << "Sorted!";
      break;
    }
    case 4: {
      
      for (int i = 0; i < (stock.size() -1); i++) {
        for(int j = (i + 1); j < stock.size(); j++) {
        if (stock[i] < stock[j]) {
          temp = stock[i];
          stock[i] = stock[j];
          stock[j] = temp;

          stringTemp = namesList[i];
          namesList[i] = namesList[j];
          namesList[j] = stringTemp;
          }
        }
      }
      cout << endl << "Sorted!";
    }
    break;
  }

  ofstream wipe("Names.txt");
  wipe.close();
  
  fstream rewrite("Names.txt", std::ios::app);
  if (rewrite.is_open()) {
    for (int i = 0; i < namesList.size(); i++) {
      rewrite << namesList[i] << endl;
    }
    rewrite.close();
  }
  
  for(int i = 0; i < namesList.size(); i++) {
    cout << endl << namesList[i];
  }
}

void viewInformation() {
  bool runAgain = false;
  string answerHolder = "";
  string lines = "";
  int count = 0;
  int person = 0;
  
  do {
    count = 1;
    fstream file("Names.txt");
    if (file.is_open()) {
      while (getline(file, lines)) {
        cout << endl << "[" << count << "] "<< lines;
        count++;
      }
    file.close();
  }
    
    do {
      cout << "\nPlease enter the number corresponding with the item you would like to view using the list above: ";
      getline(cin, answerHolder);
      if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) > count-1 || stoi(answerHolder) < 1) {
      cout << "\nInvalid selection.";
      answerHolder = "a";
      }
      }
    } while(!validInt(answerHolder));

      person = stoi(answerHolder);
      count = 0;
      
    fstream file2("Names.txt");
    if (file2.is_open()) {
      while (getline(file2, lines)) {
        count++;
        if(count == person) {
          break;
        }
      }
    file2.close();
  }
    string blob = lines.append(".txt");
      
    fstream file3(blob);
    if (file3.is_open()) {
      while (getline(file3, lines)) {
        cout << endl << lines;
      }
    file3.close();
  }

    do {
    cout << "\nWould you like to view another item? \n1) Yes\n2) No\n";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) > 2 || stoi(answerHolder) < 1) {
      cout << "\nInvalid entry.";
      answerHolder = "a";
      }
    }
  } while(!validInt(answerHolder));
  if(answerHolder == "1") {
    runAgain = true;
  } else {
    runAgain = false;
  }
    
  } while(runAgain);
}

int randomize()
{
  srand(time(0));
  return rand();
}

void removeItem() {
  bool runAgain = false;
  string answerHolder = "";
  string lines = "";
  int count = 0;
  int person = 0;
  vector<string> namesList = {};
  vector<int> ids = {};
  
  do {
    count = 1;
    fstream file("Names.txt");
    if (file.is_open()) {
      while (getline(file, lines)) {
        namesList.push_back(lines);
      }
    file.close();
  }

  //IDS
  fstream thing4("Names.txt");
  for(int i = 0; i < namesList.size(); i++) {
    getline(thing4, lines);
    string blob = lines.append(".txt");

    fstream lol(blob);

    while(getline(lol, lines)) {
      if (lines.find("ID:") != std::string::npos) {
        break;
      }
    }

    ids.push_back(stoi(lines.substr(lines.find(": ") + 2, lines.length() - 1)));
  }
  thing4.close();

    for(int i = 0; i < namesList.size(); i++) {
      cout << endl << "[" << count << "] " << namesList[i] << " :: " << ids[i];
      count ++;
    }
    
    do {
      cout << "\nPlease enter the number corresponding with the item you would like to remove using the list above: ";
      getline(cin, answerHolder);
      if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) > count-1 || stoi(answerHolder) < 1) {
      cout << "\nInvalid selection.";
      answerHolder = "a";
      }
      }
    } while(!validInt(answerHolder));

    person = stoi(answerHolder);
    count = 0;

    person--;
    namesList.erase(namesList.begin()+person);

    ofstream wipe("Names.txt");
    wipe.close();
    
    fstream rewrite("Names.txt", std::ios::app);
    if (rewrite.is_open()) {
      for (int i = 0; i < namesList.size(); i++) {
        rewrite << namesList[i] << endl;
      }
      rewrite.close();
    }

    //DELETES FILE
    string blob = namesList[person - 1] + ".txt";
    char char_array[blob.length() + 1];
    strcpy(char_array, blob.c_str());
    
    int a = remove(char_array);
    cout << "\nItem successfully deleted from database.";
    do {
    cout << "\nWould you like to remove another item? \n1) Yes\n2) No\n";
    getline(cin, answerHolder);
    if (answerHolder.length() == 0) {
            answerHolder = "a";
    }
    if (validInt(answerHolder)) {
      if (stoi(answerHolder) > 2 || stoi(answerHolder) < 1) {
      cout << "\nInvalid entry.";
      answerHolder = "a";
      }
    }
  } while(!validInt(answerHolder));
  if(answerHolder == "1") {
    runAgain = true;
  } else {
    runAgain = false;
  }
    
  } while(runAgain);
}
