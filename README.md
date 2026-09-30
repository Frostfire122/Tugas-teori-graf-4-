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

To verify whether the generated dungeon is playable, the program checks for the existence of a Hamiltonian Path using Depth-First Search (DFS) with backtracking. The algorithm explores all possible paths starting from every room $0$ to $n-1$, ensuring each room is visited exactly once without revisiting any node. Furthermore, it checks sufficient conditions like Dirac's and Ore's Theorems to evaluate graph connectivity, though validation ultimately relies on the exact path traversal. To keep gameplay interesting, valid routes undergo a similarity check based on edge overlap to filter out paths that are too similar to one another. 

Examples:

<img width="556" height="225" alt="image" src="https://github.com/user-attachments/assets/01b5c79b-1411-4f7d-aa29-05ddd7c22ac6" />
<img width="551" height="200" alt="image" src="https://github.com/user-attachments/assets/5f1be0c9-42e9-4a57-b6c7-02f2b25c0bb3" />


## Question 3

*Sample Cases*

The algorithm handles both valid and invalid layout configurations cleanly based on graph connectivity:

* **Valid Case:** In a connected 5-room layout where room 0 connects to rooms 1, 2, and 3, and room 4 connects to 1, 2, and 3, the validator identifies a valid dungeon with multiple non-similar routes such as `1 -> 0 -> 2 -> 4 -> 3`.
* **Invalid Case:** In a disconnected 5-room layout split into two isolated clusters (e.g., rooms {0, 1, 2} interconnected and rooms {3, 4} interconnected), the search finds zero valid paths. The program outputs a clear validation failure stating: `"Statement: No valid path exists in this dungeon layout."`

## Ai Usage:

- Question 1: https://claude.ai/share/6ca69834-0ce3-4beb-b3e5-3a9a2dee0408
- Question 2: https://share.gemini.google/prveSVH6qH0r
- Question 3: https://share.gemini.google/NtpixcohJSoU
