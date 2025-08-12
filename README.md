# WhatsApp Console Application (C++)

A simple C++ console-based WhatsApp-like chat simulation.  
Supports private chats, group chats, message editing, forwarding, searching, and more.

---

## 📜 Overview

This project is a text-based simulation of WhatsApp built entirely in **C++** using object-oriented programming principles.  
It demonstrates concepts like class inheritance, encapsulation, file handling, and dynamic memory management.

You can:
- Create accounts (Sign Up)
- Log in/out
- Start private chats
- Create group chats
- Send, delete, reply, edit, and forward messages
- Search messages
- Export chat history to a `.txt` file

---

## ✨ Features

### **User Management**
- Create new accounts with username, password, and phone number.
- Login/logout functionality.
- Online/Offline status tracking with **last seen** timestamp.
- Save/load user data from `users.txt`.

### **Chats**
- **Private Chats** between two users.
- **Group Chats** with multiple participants.
- Mute/unmute chats per user.
- Show participants in a chat.
- Group-specific features:
  - Add/remove participants (admin only).
  - Set a group description.
  - Join request simulation.

### **Messages**
- Send messages.
- Delete your own messages.
- Reply to a specific message (with sender and snippet shown).
- Edit your own messages (with “edited” tag).
- Forward messages to another chat.
- Search messages by keyword.
- Add emojis to messages.
- Status updates: `sent`, `delivered`, `deleted`.

### **Export**
- Export chat history to a `.txt` file.

---

## 🗂 File Structure

