# Tugas-teori-graf-4-Group_4

## Question 1
*Random Room and Tunnel Generator Algorithm*

Here, the dungeon uses a randomly generated graph in every run. It begins by seeding the random number generator with the system's nanosecond clock, ensuring no two runs produce the same result even when executed one after another. The number of rooms is then chosen randomly between 5 and 10. Since it's fully generated, you can get rooms with no connections at all, disconnected clusters of rooms that can't reach each other, or graphs where the tunnel layout doesn't allow visiting every room exactly once.

Examples:

Here you can see that when run after 3 times, it generates new ones every time
<img width="691" height="431" alt="image" src="https://github.com/user-attachments/assets/3c592616-4f9b-4335-9245-8e53d9414a80" />
<img width="693" height="386" alt="image" src="https://github.com/user-attachments/assets/5d363147-8150-449f-87a8-1dc8b71217c9" />
<img width="681" height="336" alt="image" src="https://github.com/user-attachments/assets/c93a7d26-b98c-4cba-af9e-e070f00b79cf" />

## Question 2
*Dungeon Layout Validation and Pathfinding Algorithm*

To determine whether a generated dungeon is traversable, the system evaluates the layout for a Hamiltonian Path by first running Dirac's and Ore's Theorems as sufficient degree-based pre-checks, and then falling back on a recursive Depth-First Search (DFS) with backtracking to exhaustively search for complete routes through every room, flagging the dungeon as INVALID if isolated components or bottlenecks prevent full traversal or presenting distinct sample routes if successful.

Examples:

<img width="723" height="333" alt="image" src="https://github.com/user-attachments/assets/4e1e5c2f-04a5-43c4-8956-6141040668ca" />
<img width="838" height="374" alt="image" src="https://github.com/user-attachments/assets/8ae3941a-50bd-4f2a-a862-87869559d401" />
<img width="715" height="244" alt="image" src="https://github.com/user-attachments/assets/0e1118ed-9d64-4d36-90c9-3ecfe9ce7473" />

## Question 3

*Sample Cases*

The algorithm handles both valid and invalid layout configurations cleanly based on graph connectivity:

* **Valid Case:** In a connected 5-room layout where room 0 connects to rooms 1, 2, and 3, and room 4 connects to 1, 2, and 3, the validator identifies a valid dungeon with multiple non-similar routes such as `1 -> 0 -> 2 -> 4 -> 3`.
* **Invalid Case:** In a disconnected 5-room layout split into two isolated clusters (e.g., rooms {0, 1, 2} interconnected and rooms {3, 4} interconnected), the search finds zero valid paths. The program outputs a clear validation failure stating: `"Statement: No valid path exists in this dungeon layout."`

## Ai Usage:

- Question 1: https://claude.ai/share/6ca69834-0ce3-4beb-b3e5-3a9a2dee0408
- Question 2: https://share.gemini.google/prveSVH6qH0r
- Question 3: https://share.gemini.google/NtpixcohJSoU
