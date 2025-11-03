# README

## Project: SocialNet Simulator

This project implements a simplified, in-memory **social networking system** inspired by real-world platforms.  
The goal was to design and integrate **custom data structures** (graphs, sets, AVL trees, queues, heaps) into a cohesive system that supports:
- user creation and friendship linking,  
- post management with automatic ordering,  
- friend suggestion through mutual connections,  
- and shortest path (degree of separation) computation.

---

## How It Works

### 1.) Graph System (`Graph` class)
-> Manages all users and friendships.  
-> Each user is represented as a node; friendships are undirected edges.  
-> Supports commands like:  
   **ADD USER, ADD FRIEND, LIST FRIENDS, SUGGEST FRIENDS, DEGREE(S) OF SEPARATION, ADD POST, OUTPUT POSTS.**

---

### 2.) User Structure (`User` class)
-> Represents an individual user.  
-> Maintains:  
   - `unordered_set` of friends for O(1) lookup.  
   - `AVLtree` of posts for efficient insertion and retrieval.  
-> Provides:
   - `addPost()` → inserts a post into the AVL tree.  
   - `outputPosts(n)` → displays the most recent *n* posts.

---

### 3.) Post Management (`AVLtree` class)
-> Implements a self-balancing AVL Tree to store user posts.  
-> Each post is a node in the tree (chronologically inserted to the right).  
-> Supports:
   - `insert(content)` → adds new post.
   - `outputN(n)` → prints last *n* posts (reverse in-order traversal).
-> Only **right-heavy balancing** (single left rotation) is required since new posts are always chronologically newer.

---

### 4.) Data Handling
-> **Friendship**: Bidirectional (if Alice adds Bob, Bob automatically becomes Alice’s friend).  
-> **Case Insensitivity**: All usernames and posts are converted to lowercase for consistency.  
-> **Error Checks**:  
   - Duplicate users or friendships detected.  
   - Incorrect syntax rejected with error messages.  
   - Non-existent users properly handled.

---

## Functions & Responsibilities

### `Graph`:
-> `addUser(username)` → creates a new user.  
-> `addFriend(user1, user2)` → establishes a friendship.  
-> `listFriend(username)` → displays all friends alphabetically.  
-> `suggestFriends(username, N)` → recommends up to N users with most mutual friends.  
-> `degreeOfSeparation(user1, user2)` → finds the shortest path (in edges) using BFS.  
-> `addPost(username, content)` → adds a post to the user’s feed.  
-> `outputPosts(username, N)` → shows the latest N posts.  

---

### `User`:
-> `addPost(s)` → calls internal AVL insert.  
-> `outputPosts(n)` → prints N most recent posts.  

---

### `AVLtree`:
-> `insert(s)` → inserts new post to the right.  
-> `outputN(n)` → prints last N posts in reverse chronological order.  
-> Balancing uses only **left rotation** (insertion-only tree).  

---

## Design Choices

### 1. AVL Tree for Post Storage
-> Guarantees logarithmic insertion and retrieval.  
-> Since posts are added chronologically, only right-side balancing (single rotation) is necessary.  
-> Each node contains a string post and height metadata.

### 2. Unordered Containers
-> Users and friends are stored in `unordered_map` and `unordered_set`.  
-> Provides O(1) average access for lookup and membership checking.

### 3. BFS for Degrees of Separation
-> Computes the minimal number of “friend hops” between two users.  
-> Returns -1 if there is no path.

### 4. Mutual Friend Suggestion
-> Calculates mutual friends using temporary hashmaps and a priority queue.  
-> Sorted primarily by mutual friend count (descending), then by username (ascending).

### 5. Case-Insensitive Input
-> Every username and post content is converted to lowercase internally.  
-> Prevents duplicate profiles like “Alice” and “alice”.

---

## Memory Management

-> Every user and AVL node is dynamically allocated.  
-> The `Graph` destructor deallocates all user instances.  
-> AVL trees recursively delete their nodes in post-order traversal.  
-> The program cleans up automatically when it exits.

---

## Terminal Guide

1. Open Terminal
Navigate to the folder containing your project files (main.cpp and any headers like FileSystem.hpp).
->cd /path/to/your/project
2. Run the script
->chmod +x run.sh
3. Compile and run the program
->./run.sh (to run in interactive mode)
->./run.sh socialnet_test.txt(to run with text input file)

---

## CLI Commands

| Command                           | Description                                | Example                             |
| --------------------------------- | ------------------------------------------ | ----------------------------------- |
| `ADD USER <username>`             | Create a new user.                         | `ADD USER Alice`                    |
| `ADD FRIEND <u1> <u2>`            | Add friendship between users.              | `ADD FRIEND Alice Bob`              |
| `LIST FRIENDS <username>`         | Show friend list.                          | `LIST FRIENDS Alice`                |
| `SUGGEST FRIENDS <username> <N>`  | Recommend top N users with mutual friends. | `SUGGEST FRIENDS Alice 5`           |
| `DEGREES OF SEPARATION <u1> <u2>` | Find shortest connection path.             | `DEGREES OF SEPARATION Alice David` |
| `ADD POST <username> "<post>"`    | Add a new post (use quotes).               | `ADD POST Alice "Hello World"`      |
| `OUTPUT POSTS <username> <N>`     | Show last N posts (`-1` = all).            | `OUTPUT POSTS Alice 3`              |
| `EXIT`                            | Quit the program.                          | `EXIT`                              |

---

## Notes

-All usernames are case-insensitive.
-Post content must be wrapped in double quotes.
-Each command supports single-word usernames (no spaces).
-Friendship is bidirectional by default.
-Syntax validation prevents incomplete or incorrect commands.
