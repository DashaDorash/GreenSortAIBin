# GreenSortAIBin

A smart recycling bin that uses AI to identify waste and sort it correctly, reducing contamination and improving recycling efficiency.

## Table of Contents

- [Overview](#overview)
- [How It Works](#how-it-works)
- [Technologies Used](#technologies-used)
- [Hardware Components](#hardware-components)
- [Demo](#demo)
- [Contributors](#contributors)

---

## Overview

Recycling rules vary across locations, leading to confusion and improper waste disposal. Incorrect recycling can cause contamination, rendering materials non-recyclable and even leading to facility fires when hazardous items like lithium-ion batteries are misplaced.

**GreenSort AI Bin** aims to solve this by using AI-powered image recognition to detect waste types and automate sorting.

---

## How It Works

1. **User Interaction**: Press a button to activate the bin.
2. **Image Capture**: A camera takes a picture of the waste item.
3. **AI Classification**: The image is sent to an AI model via an API.
4. **Sorting Decision**: If the item is recyclable, the bin opens; otherwise, it remains closed to prevent contamination. 

---

## Technologies Used

### Software:
- **AI Model**: [YOLO Waste Detection](https://universe.roboflow.com/projectverba/yolo-waste-detection) (accessed via API)
- **Programming Languages**: Python, C++ (Arduino)
- **Computer Vision**: OpenCV for image handling
- **Microcontroller Communication**: Serial communication between Arduino & Python

### Hardware:
- **Arduino** – Controls the motorized bin lid
- **Camera (Webcam/Raspberry Pi Cam)** – Captures waste images
- **Stepper Motor** – Rotates the bin lid based on AI classification
- **PC** – Runs the AI classification and sends control signals

---
### Demo:

[Watch the video](https://vimeo.com/manage/videos/1063425646)

---
### Contributors:
- **Dasha Dorash** – https://github.com/DashaDorash
- **Saniya Mukhambetkaliyeva** – https://github.com/Saniya05m
