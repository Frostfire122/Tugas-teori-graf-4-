# Tugas-teori-graf-4-Group_6

## Question 1
*Random Room and Tunnel Generator Algorithm*

Here, the dungeon uses a randomly generated graph in every run. It begins by seeding the random number generator with the system's nanosecond clock, ensuring no two runs produce the same result even when executed one after another. The number of rooms is then chosen randomly between 5 and 10. Since it's fully generated, you can get rooms with no connections at all, disconnected clusters of rooms that can't reach each other, or graphs where the tunnel layout doesn't allow visiting every room exactly once.

Examples:

Here you can see that when run after 3 times, it generates new ones every time
<img width="691" height="431" alt="image" src="https://github.com/user-attachments/assets/3c592616-4f9b-4335-9245-8e53d9414a80" />
<img width="693" height="386" alt="image" src="https://github.com/user-attachments/assets/5d363147-8150-449f-87a8-1dc8b71217c9" />
<img width="681" height="336" alt="image" src="https://github.com/user-attachments/assets/c93a7d26-b98c-4cba-af9e-e070f00b79cf" />

## Question 2

To determine whether a generated dungeon layout is valid—meaning a player can visit every room exactly once without backtracking—the algorithm evaluates the graph using both theoretical rules and a step-by-step pathfinder. It first checks Dirac's and Ore's theorems, which act as fast mathematical shortcuts: if a dungeon has enough connections per room overall, these rules instantly guarantee that a complete path exists, though failing them doesn't automatically mean the layout is impossible. To get a definitive answer, the code runs a Depth-First Search (DFS) backtracker that simulates exploring from every room, keeping track of visited locations to avoid repeating any. If it successfully finds a path that covers every single room, it labels the dungeon as valid, reports how many complete routes exist, and prints a sample path; otherwise, it confirms that no valid route can traverse the entire layout.

Examples:
<img width="705" height="291" alt="image" src="https://github.com/user-attachments/assets/ae447ae6-b002-42a1-ab52-c0e2acfc46ad" />


