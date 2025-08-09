# ServerFileShare

ServerFileShare is a lightweight C-based tool that allows you to host a file on your own server so others can directly connect and download it — no third parties, no cloud storage, just you and the recipient.  

This is ideal for situations where you want full control over who can access your files and avoid relying on external services.

---

## Features
- **Direct file sharing** — no middlemen or cloud providers.
- **Control access** — only people you share your IP and port with can connect.
- **Friend management** — add, remove, and search friends by IP/port.
- **Server configuration** — change port, session duration, and password.
- **Future goal** — add encryption for extra security.

---

## Getting Started

### Prerequisites
- GCC or any C compiler.
- Linux/macOS environment (Windows support may require modifications).

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/DressingPluto84/ServerFileShare.git
   cd ServerFileShare
   ```
2. Build the program:
   ```bash
   make
   ```

3. Run the program:
   ```bash
   ./main
   ```

---

## Commands

Inside the program, you can use the following commands:

| Command | Usage | Description |
|---------|-------|-------------|
| `setUpServer` | `setUpServer filename` | Hosts a server with the given file so others can download it. |
| `connect` | `connect ip port` | Connects to a server with the given IP and port. |
| `printFriends` | `printFriends` | Lists all friends in your friends list. |
| `addFriend` | `addFriend ip port` | Adds a friend with the given IP and port. |
| `removeFriend` | `removeFriend ip port` | Removes a friend from your list. |
| `searchFriend` | `searchFriend ip port` | Checks if a given friend is in your list. |
| `findIpPort` | `findIpPort ip` | Lists all ports in your friends list associated with the given IP. |
| `getServerTime` | `getServerTime` | Shows how many seconds the server will remain open. |
| `getCurrPort` | `getCurrPort` | Shows the current server port number. |
| `setServer` | `setServer` | Changes how long (in seconds) the server stays open. |
| `setPort` | `setPort` | Changes the port the server runs on. |
| `changePassword` | `changePassword newPassword` | Changes the password required for connections. |

---

## Example

To host a file called `example.txt`:
```bash
setUpServer example.txt
```

To connect to a server at IP `192.168.1.10` on port `8080`:
```bash
connect 192.168.1.10 8080
```

---

## Security
- Only people you share your IP and

