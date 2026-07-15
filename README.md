# Contact Manager

A console-based contact management application written in ANSI C.

## Overview

This academic project replaces paper notes and basic spreadsheets with a simple application for organizing customer, supplier, and partner contacts. Data is kept in memory while the program runs and persisted to `contatos.txt`.

## Features

- Add, list, search, update, and delete contacts
- Search by full or partial name
- Sort contacts alphabetically
- Store name, phone number, email address, and city
- Save and load contacts from a local text file
- Run on Windows, Linux, and macOS terminals

## Tech Stack

- ANSI C
- C standard library
- `string.h` for text operations
- `windows.h` for cursor positioning on Windows
- ANSI escape sequences on Unix-like systems

## Getting Started

### Prerequisites

- GCC or another ANSI C-compatible compiler

### Build

```bash
gcc -ansi -Wall -Wextra -pedantic agenda_contatos.c -o agenda_contatos
```

### Run

Linux and macOS:

```bash
./agenda_contatos
```

Windows:

```powershell
.\agenda_contatos.exe
```

The application creates `contatos.txt` in the current directory to persist contact data.

## Project Structure

```text
.
├── agenda_contatos.c                    # Application source code
├── agenda_contatos.cbp                  # Code::Blocks project file
├── documento_entrega.txt                # Academic project documentation
└── TRABALHO FINAL - AGENDA DE CONTATOS.pdf
```
