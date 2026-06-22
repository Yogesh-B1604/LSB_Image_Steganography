# 🖼️ Image Steganography in C (LSB Technique)

## 📌 Overview

This project implements **Image Steganography using the Least Significant Bit (LSB) technique** in C. It allows hiding a secret text file inside a BMP image and later extracting it without noticeable changes to the image.

The system supports both:
- 🔐 Encoding (hiding data inside image)
- 🔍 Decoding (retrieving hidden data)

---

## ⚙️ How It Works

### 🔐 Encoding Process
1. Read the source BMP image
2. Copy the BMP header (first 54 bytes)
3. Encode the following into image pixels:
   - Magic string (`#*`)
   - File extension
   - File size
   - Secret file data
4. Modify the Least Significant Bits (LSB) of image bytes
5. Write the modified data into a new **stego image**

---

### 🔍 Decoding Process
1. Read the stego image
2. Skip BMP header
3. Extract:
   - Magic string (for validation)
   - File extension
   - File size
   - Hidden data
4. Reconstruct the original secret file (`output.txt`)

---

## 🧠 Key Concepts Used

- Bitwise operations (`&`, `|`, `<<`, `>>`)
- File handling (`fread`, `fwrite`)
- Data encoding & decoding
- Structures in C
- Command-line argument parsing
- BMP image format handling

---

## 📁 Project Structure

```text
|-- encode.c
|-- decode.c
|-- main.c
|-- encode.h
|-- decode.h
|-- types.h
|-- common.h
|-- secret.txt
|-- beautiful.bmp
|-- stego.bmp
|-- output.txt
```

## ▶️ Usage

### 🔐 Encoding
./a.out -e beautiful.bmp secret.txt [stego.bmp]

If output file is not provided, default will be:
default.bmp

### 🔍 Decoding
./a.out -d stego.bmp [output.txt]

Default output:
output.txt

## 📥 Example

Input:
Secret File: secret.txt
Content: My password is SECRET ;)

Output:
Stego Image: stego.bmp
Decoded File: output.txt

## 🎯 Features

- Supports BMP image format
- Lossless data hiding (image visually unchanged)
- Magic string validation for integrity
- Dynamic file size handling
- Modular design (separate encode/decode modules)

## ⚠️ Limitations

- Supports only .bmp images
- Supports only .txt files
- No encryption (only hiding data)

## 🚀 Future Improvements

- Add encryption before encoding
- Support multiple file formats
- GUI-based interface
- Improve data capacity handling

## 💡 Learning Outcomes

This project demonstrates:
- Real-world application of bit manipulation
- Understanding of file systems and memory
- Implementation of data hiding techniques
- Strong grasp of low-level programming in C

## 📸 Demo

### Original Image 
![Original](beautiful.bmp)

### Stego Image
![Stego](stego.bmp)


