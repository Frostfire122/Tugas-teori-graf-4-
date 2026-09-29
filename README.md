# Tugas-teori-graf-4-

*Random Room and Tunnel Generator Algorithm*

Here, the dungeon uses a randomly generated graph in every run. It begins by seeding the random number generator with the system's nanosecond clock, ensuring no two runs produce the same result even when executed one after another. The number of rooms is then chosen randomly between 5 and 10. Since it's fully generated, you can get rooms with no connections at all, disconnected clusters of rooms that can't reach each other, or graphs where the tunnel layout doesn't allow visiting every room exactly once.

```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ROOMS 10
#define MAX_TUNNELS 20

int main() {
    //makes it so random generator differently every run
    srand(time(NULL));

    //randomly decide how many rooms to generate
    int numRooms = 5 + rand() % (MAX_ROOMS - 5 + 1);

    //randomly decide how many tunnels to generate,, between numRooms and MAX_TUNNELS
    int maxPossibleTunnels = numRooms * (numRooms - 1) / 2;  //max edges in a simple graph
    int numTunnels = numRooms + rand() % (maxPossibleTunnels - numRooms + 1);
    if (numTunnels > MAX_TUNNELS) numTunnels = MAX_TUNNELS;

    printf("Generated %d rooms (0 to %d)\n\n", numRooms, numRooms - 1);

    //adjacency matrix to avoid generating duplicate tunnels
    //and to build the per-room listing afterward
    bool tunnelExists[MAX_ROOMS][MAX_ROOMS] = { false };

    int src[MAX_TUNNELS], dest[MAX_TUNNELS];
    int tunnelsMade = 0;
    int attempts = 0;
    int maxAttempts = numTunnels * 20;  //safety limit to avoid infinite loop

    while (tunnelsMade < numTunnels && attempts < maxAttempts) {
        int a = rand() % numRooms;
        int b = rand() % numRooms;

        attempts++;

        //skip if same room, or tunnel already exists (in either direction)
        if (a == b) continue;
        if (tunnelExists[a][b] || tunnelExists[b][a]) continue;

        //record the tunnel
        tunnelExists[a][b] = true;
        tunnelExists[b][a] = true;
        src[tunnelsMade] = a;
        dest[tunnelsMade] = b;
        tunnelsMade++;
    }

    printf("Tunnels: %d total\n\n", tunnelsMade);

    //print each room's connections using the adjacency matrix
    for (int room = 0; room < numRooms; room++) {
        printf("Room %d - ", room);

        bool first = true;
        for (int other = 0; other < numRooms; other++) {
            if (tunnelExists[room][other]) {
                if (!first) printf(", ");
                printf("%d", other);
                first = false;
            }
        }

        if (first) {
            printf("(no connections)");
        }

        printf("\n");
    }

    return 0;
}
```

Examples:

Here you can see that when run after 3 times, it generates new ones every time
<img width="691" height="431" alt="image" src="https://github.com/user-attachments/assets/3c592616-4f9b-4335-9245-8e53d9414a80" />
<img width="693" height="386" alt="image" src="https://github.com/user-attachments/assets/5d363147-8150-449f-87a8-1dc8b71217c9" />
<img width="681" height="336" alt="image" src="https://github.com/user-attachments/assets/c93a7d26-b98c-4cba-af9e-e070f00b79cf" />



