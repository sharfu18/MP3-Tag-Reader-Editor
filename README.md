# MP3 Tag Reader and Editor

**MP3 Tag Reader and Editor** is a C-based application that reads and modifies MP3 file metadata using the **ID3v2.3 tagging format**.

The project supports both viewing and editing MP3 metadata, including song title, artist name, album, year, genre, and composer.

The application processes ID3 frames from MP3 files using **file handling, structures, pointers, string manipulation, and command-line arguments**.

It follows a modular programming approach, where viewing and editing operations are implemented in separate C source files.

## Features

- Reads MP3 metadata using the ID3v2.3 format.
- Displays song title.
- Displays artist name.
- Displays album information.
- Displays release year.
- Displays genre.
- Displays composer information.
- Edits existing MP3 metadata.
- Supports modification of individual ID3 frames.
- Validates command-line arguments.
- Identifies supported operations using command-line options.
- Uses modular C source files for better code organization.

## How It Works

The application supports two major operations: **Viewing and Editing**.

### Viewing Process

The viewing operation reads the ID3 header and extracts metadata from the MP3 file.

```text
          MP3 File
              |
              |
       Validate Arguments
              |
              |
        Open MP3 File
              |
              |
        Read ID3 Header
              |
              |
       Validate ID3 Tag
              |
              |
       Check ID3 Version
              |
              |
        Read Tag Size
              |
              |
        Read ID3 Frames
              |
              |
       Identify Frame IDs
              |
       +------+------+------+
       |      |      |      |
      TIT2   TPE1   TALB   TYER
       |      |      |      |
     Title  Artist Album   Year
              |
       +------+------+
       |             |
      TCON          TCOM
       |             |
     Genre        Composer
              |
              |
       Display Metadata
              |
              |
          Close File
```

The application reads the 10-byte ID3 header, validates the tag signature and version, and then processes individual metadata frames.

Each frame contains a frame identifier, frame size, flags, and frame data.

### Editing Process

The editing operation modifies the selected metadata frame in the MP3 file.

```text
          MP3 File
              |
              |
       Validate Arguments
              |
              |
        Select Edit Option
              |
              |
        Open MP3 File
              |
              |
        Read ID3 Header
              |
              |
       Validate ID3 Tag
              |
              |
        Read ID3 Frames
              |
              |
       Identify Target Frame
              |
              |
       Find Required Frame
              |
              |
       Validate New Value
              |
              |
       Replace Existing Data
              |
              |
       Preserve Remaining Space
              |
              |
       Save Updated Metadata
              |
              |
          Close File
```

The application identifies the required frame using its corresponding ID and replaces the existing metadata with the new value.

## ID3v2.3 Tag Structure

The project works with the **ID3v2.3 metadata format**.

An ID3v2.3 tag contains a 10-byte header followed by individual metadata frames.

The header contains:

- Identifier: `ID3`
- Major version
- Revision version
- Flags
- Tag size

Each metadata frame contains:

- Frame ID
- Frame size
- Frame flags
- Frame data

### Supported Frame IDs

| Frame ID | Metadata |
|---|---|
| `TIT2` | Song Title |
| `TPE1` | Artist |
| `TALB` | Album |
| `TYER` | Year |
| `TCON` | Genre |
| `TCOM` | Composer |

The application identifies these frame IDs to display or modify the corresponding metadata.

## Project Structure

```text
MP3-Tag-Reader-Editor/
│
├── 001_main.c
│
├── 002_view.c
│
├── 003_edit.c
│
├── edit.h
│
├── view.h
│
├── types.h
│
├── sample.mp3
│
└── README.md
```

### File Description

| File | Purpose |
|---|---|
| `001_main.c` | Main function, argument validation, and operation selection |
| `002_view.c` | Reads and displays MP3 metadata |
| `003_edit.c` | Modifies selected MP3 metadata frames |
| `edit.h` | Contains edit function declarations |
| `view.h` | Contains view function declarations |
| `types.h` | Defines status and operation enumerations |
| `sample.mp3` | Sample MP3 file used for testing |

The repository follows a modular design where viewing, editing, operation selection, and common type definitions are maintained in separate files.

## Requirements

- GCC Compiler
- Linux / Unix-like environment
- Basic C development environment
- MP3 file containing ID3v2.3 metadata

## Compilation

Clone the repository:

```bash
git clone https://github.com/sharfu18/MP3-Tag-Reader-Editor.git
```

Move into the project directory:

```bash
cd MP3-Tag-Reader-Editor
```

Compile the project using GCC:

```bash
gcc *.c -o mp3_tag_reader
```

The GCC compiler compiles all C source files and links them to generate the `mp3_tag_reader` executable.

## Usage

The application supports two main operations:

### 1. View MP3 Metadata

Command:

```bash
./mp3_tag_reader -v sample.mp3
```

The `-v` option displays the metadata stored in the MP3 file.

### 2. Edit MP3 Metadata

The `-e` option allows users to modify individual metadata fields.

**Edit Song Title:**

```bash
./mp3_tag_reader -e -t "New Title" sample.mp3
```

**Edit Artist Name:**

```bash
./mp3_tag_reader -e -a "New Artist" sample.mp3
```

**Edit Album:**

```bash
./mp3_tag_reader -e -A "New Album" sample.mp3
```

**Edit Release Year:**

```bash
./mp3_tag_reader -e -y "2026" sample.mp3
```

**Edit Genre:**

```bash
./mp3_tag_reader -e -g "Rock" sample.mp3
```

**Edit Composer:**

```bash
./mp3_tag_reader -e -c "New Composer" sample.mp3
```

The application searches for the corresponding ID3 frame and replaces its existing value.

**Important:** The new metadata value must fit within the existing frame size. The current implementation does not resize ID3 frames.

## Example

### Input

Sample MP3 file: `sample.mp3`

### View Command

```bash
./mp3_tag_reader -v sample.mp3
```

### Sample Output

```text
You Have Selected View Menu
MP3 File Opened Successfully
ID3 TAG FOUND
ID3 Version : 2.3

========================================
          MP3 TAG INFORMATION
========================================
TITLE    : Bahubali
Artist   : Keeravani
Album    : C Programming Album
YEAR     : 2022
Genre    : Test Genre
Composer : Test Composer
========================================
```

### Edit Command

```bash
./mp3_tag_reader -e -t "New Title" sample.mp3
```

After successful execution, the title metadata is updated in the MP3 file.

Running the view operation again allows users to verify the modified metadata.

## Concepts Learned

This project helped in understanding and applying:

- C Programming
- File Handling
- Binary File Processing
- Structures and Enumerations
- Pointers
- Dynamic Memory Allocation
- String Manipulation
- Command-Line Arguments
- ID3v2.3 Metadata Format
- File Positioning using `fseek()`
- Reading and Writing using `fread()` and `fwrite()`
- Modular Programming
- Data Parsing
- Error Handling
- Multi-file C Projects

## Future Improvements

Possible enhancements include:

- Supporting ID3v2.4 metadata.
- Adding support for album artwork.
- Supporting additional metadata frames.
- Improving validation of MP3 file formats.
- Supporting longer metadata values by resizing frames.
- Adding support for batch metadata editing.
- Improving error handling for corrupted MP3 files.
- Providing a more user-friendly interface.

## Author

**Shaik Sharfuddin**

---

⭐ If you find this project useful, feel free to explore the repository and provide feedback.