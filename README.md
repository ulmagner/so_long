# 🎮 so_long

> A simple 2D game built in C using MiniLibX.

---

## 📌 Description

**so_long** is a small 2D game developed as part of the 42 curriculum.
The goal is to collect all collectibles on the map and reach the exit using the shortest path possible.
Collectibles are slimes trapped inside pots, break them they will help you find the exit!

---

## 🕹️ Gameplay

* Move the player across the map
* Collect all slimes 🟢
* Teleport with you slimes to pass obstacle cntrl + click
* Avoid walls 🧱
* Avoid fire 🔥
* kill enemies 👾
* Reach the exit 🚪 to win

---

## 🛠️ Technologies

* C
* MiniLibX
* Makefile

---

## 📂 Project Structure

```
so_long/
├── srcs/
├── includes/
├── cartes/
├── textures/
├── Makefile
```

---

## ⚙️ Installation & Usage

### 1. Clone the repository

```bash
git clone https://github.com/ulmagner/so_long.git
cd so_long
```

### 2. Compile

```bash
make
```

### 3. Run the game

```bash
./so_long cartes/map.ber ... cartes/last_map_level.ber path_to_texteures/texture_file
```

---

## 🎨 Features

* Map parsing (.ber)
* Player movement
* Collision system
* slime system
* Exit condition
* Basic rendering with MiniLibX
* enemies
* stamina bar for defending and attacking
* teleport using slimes
* multiple map levels

---

## 🧠 Learning Outcomes

* Window management with MiniLibX
* Event handling (keyboard input)
* File parsing and validation
* Memory management in C
* Game loop fundamentals

---

## 📸 Preview

![Project Demo](so_long-ezgif.gif)

---

## 👨‍💻 Author

* ulmagner / Game Dev

---

## 📄 License

This project is for educational purposes (42 school).
