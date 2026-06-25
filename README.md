# Inverted Search Using Hash Tables

A high-performance **Inverted Search Engine** implemented in **C** that indexes multiple text files using a **Hash Table** for efficient word lookup.

The application creates an inverted index by storing each unique word along with the files in which it appears and the number of occurrences in each file. This significantly reduces search time compared to scanning every file individually.

---

## Overview

Searching for a word across multiple text files becomes inefficient as the number of files grows.

This project addresses that problem by building an **Inverted Index**, allowing the program to locate a word in nearly constant time after indexing.

The project demonstrates the use of

- Hash Tables
- Linked Lists
- Dynamic Memory Allocation
- File Handling
- Command Line Arguments
- Modular Programming
- Data Structures in C

---

## Features

- Build database from multiple text files
- Fast word lookup using hashing
- Store occurrence count for every file
- Display complete inverted index
- Save database to backup file
- Restore database from backup
- Handle duplicate input files
- Ignore invalid or empty files
- Menu-driven terminal interface

---

## Project Architecture

```
                    Input Text Files
                           │
                           ▼
                Input Validation Module
                           │
                           ▼
                 Word Extraction Module
                           │
                           ▼
                  Hash Function (27 Buckets)
                           │
        ┌──────────────────┴──────────────────┐
        ▼                                     ▼
 Main Node (Unique Word)             Main Node (Unique Word)
        │                                     │
        ▼                                     ▼
  Linked List of Files               Linked List of Files
(File Name + Word Count)          (File Name + Word Count)
```

---

## Data Structure

Each hash table bucket contains a linked list of words.

```
Hash Table

Index
 │
 ▼
+-----------------------------+
| Word                        |
| Number of Files             |
| Pointer to File List        |
+-----------------------------+
              │
              ▼
+-----------------------------+
| File Name                   |
| Word Count                  |
+-----------------------------+
              │
              ▼
            NULL
```

---

## Hash Function

```
Index = (tolower(first_character) - 'a') % 26
```

Special characters are stored in the **26th bucket**.

---

## Project Structure

```
Inverted-Search/
│
├── include/
│   └── hash.h
│
├── src/
│   ├── main.c
│   ├── create_db.c
│   ├── display_db.c
│   ├── inputvalidation.c
│   ├── save_db.c
│   ├── search_db.c
│   └── update_db.c
│
├── sample_input/
│
├── screenshots/
│
├── README.md
└── LICENSE
```

---

## Build

Using GCC

```bash
gcc src/*.c -Iinclude -o inverted_search
```

Run

```bash
./inverted_search file1.txt file2.txt file3.txt
```

---

## Menu

```
1. Create Database

2. Display Database

3. Update Database

4. Search Word

5. Save Database

6. Exit
```

---

## Sample Output

```
DATABASE created successfully!

Enter word:
embedded

embedded is present in 2 file(s)

File : file1.txt
Occurrences : 5

File : file3.txt
Occurrences : 2
```

---

## Time Complexity

| Operation | Complexity |
|------------|------------|
| Insert | O(1) Average |
| Search | O(1) Average |
| Display | O(n) |
| Save | O(n) |
| Update | O(n) |

---

## Memory Design

Each unique word is stored only once.

For every word, a linked list maintains

- File name
- Number of occurrences

This minimizes duplication while providing efficient retrieval.

---

## Key Concepts Demonstrated

- Hash Tables
- Collision Handling
- Linked Lists
- Dynamic Memory Allocation
- File Parsing
- String Manipulation
- Data Structures
- File I/O
- Modular Design
- Command Line Programming

---

## Future Improvements

- Remove punctuation before indexing
- Case-insensitive search
- Phrase search
- Wildcard search
- Recursive directory indexing
- Stop-word filtering
- TF-IDF ranking
- Multi-threaded indexing

---

## Technologies Used

- C
- GCC
- Linux
- Standard C Library

---

## Author

**Fahed Akil Shaikh**

Bachelor of Engineering (Electronics & Telecommunication)

Embedded Systems | Firmware Development | Linux Programming | Data Structures
