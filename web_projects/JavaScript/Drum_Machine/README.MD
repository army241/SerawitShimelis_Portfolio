# 🥁 Drum Machine

A simple interactive **Drum Machine web application** that allows users to play drum sounds by clicking buttons or pressing keyboard keys. Each drum pad triggers a unique sound and displays the name of the sound currently being played.

This project was built as part of the **FreeCodeCamp Frontend Development curriculum**.

---

## 🚀 Features

- 9 interactive drum pads
- Each pad plays a unique drum sound
- Sounds can be triggered by:
  - Clicking the drum pads
  - Pressing keyboard keys
- Displays the name of the sound being played
- Responsive grid layout
- Simple and clean interface

---

## 🎹 Drum Pad Keys

| Key | Sound |
|----|------|
| Q | Heater 1 |
| W | Heater 2 |
| E | Heater 3 |
| A | Heater 4 |
| S | Clap |
| D | Open HH |
| Z | Kick n Hat |
| X | Kick |
| C | Closed HH |

---

## 🛠️ Technologies Used

- **HTML5** – Page structure
- **CSS3** – Layout and styling
- **JavaScript (ES6)** – Interactivity and sound control

---

### File Description

**index.html**
- Contains the structure of the drum machine
- Includes drum pads and audio elements

**style.css**
- Handles the layout and visual styling
- Uses CSS Grid to organize the drum pads

**script.js**
- Controls the functionality
- Handles button clicks and keyboard inputs
- Plays audio clips
- Updates the display text

---

## ⚙️ How It Works

1. Each drum pad contains an **audio element** with a unique ID.
2. When a user clicks a drum pad or presses the corresponding key:
   - JavaScript identifies the correct audio element.
3. The audio clip is played.
4. The display updates to show the name of the sound.

Example flow:

